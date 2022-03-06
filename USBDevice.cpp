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
    Device::devices.clear();
    Device::enumerate_devices();
}

void Device::get_device_count(){
    cout<<Device::device_count<<" Devices in list."<<endl; //print total number of usb devices
}

void Device::enumerate_devices(){

    struct libusb_device *dev;
    int i = 0;
    int devcount = 0;
    uint8_t path[8];
    devices.resize(Device::cnt);

    while ((dev = devs[i++]) != NULL) {
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
            libusb_get_string_descriptor_ascii(dev_handle, desc.iProduct, devices.at(devcount).product, 100);
            libusb_get_string_descriptor_ascii(dev_handle, desc.iManufacturer, devices.at(devcount).manufacturer, 100);
            libusb_get_port_numbers(dev, path, sizeof(path));

            devices.at(devcount).vendor_id = fmt::format("{:04x}", desc.idVendor);
            devices.at(devcount).product_id = fmt::format("{:04x}", desc.idProduct);
            devices.at(devcount).sys_path = "/sys/bus/usb/devices/" + std::to_string(libusb_get_bus_number(dev)) + "-" + std::to_string(path[0]) + "/authorized";
            devcount++;
        }
    }
    Device::device_count = devcount;
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

void Device::close_session(){
    libusb_exit(ctx); //close the session
}

Device::~Device(){
    libusb_free_device_list(devs, 1);
    Device::close_session();
}
