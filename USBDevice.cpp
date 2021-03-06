#include <iostream>
#include <fmt/format.h>
#include "USBDevice.h"


using namespace std;

Device::Device(){
    int r = libusb_init(&ctx); //initialize a library session
    if(r < 0) {
        cout<<"Init Error "<<r<<endl; //there was an error
        exit(1);
    }
    cnt = libusb_get_device_list(ctx, &devs); //get the list of devices
    if(cnt < 0) {
        cout<<"Get Device Error"<<endl; //there was an error
        exit(1);
    }

    Device::enumerate_devices();
}

void Device::enumerate_devices(){
    struct libusb_device *dev;
    int i = 0;
    int devcount = 0;
    uint8_t path[8];

    while ((dev = devs[i++]) != nullptr) {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor");
            exit(EXIT_FAILURE);
        }
        if (desc.bDeviceClass != libusb_class_code::LIBUSB_CLASS_HUB){
            r = libusb_open(dev, &dev_handle);

            if(r < 0){
                fprintf(stderr, "failed to get device");
                exit(EXIT_FAILURE);
            }

            Device::workable_device device;

            libusb_get_string_descriptor_ascii(dev_handle, desc.iProduct, device.product, 100);
            libusb_get_string_descriptor_ascii(dev_handle, desc.iManufacturer, device.manufacturer, 100);
            libusb_get_port_numbers(dev, path, sizeof(path));

            device.product_id = fmt::format("{:04x}", desc.idProduct);
            device.vendor_id = fmt::format("{:04x}", desc.idVendor);
            device.sys_path = "/sys/bus/usb/devices/" + std::to_string(libusb_get_bus_number(dev)) + "-" + std::to_string(path[0]) + "/authorized";

            devices.push_back(device);

            devcount++;
        }
    }
    devices.resize(devcount);
    Device::device_count = devices.size();
}

Device::workable_device* Device::get_device(Device& dev, const std::string& vendor, const std::string& product){
    for(int i = 0; i < dev.device_count; i++){
        if(dev.devices.at(i).vendor_id.compare(vendor) == 0 && dev.devices.at(i).product_id.compare(product) == 0){
            Device::workable_device* device = &(dev.devices.at(i));
            return device;
        }
    }
    return nullptr;
}

Device::~Device(){
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
}
