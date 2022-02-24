#include "USBDevice.h"
#include <iostream>

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
    Device::Devices.clear();
    Device::EnumDevices();
}

void Device::GetDeviceCount(){
    cout<<Device::DeviceCount<<" Devices in list."<<endl; //print total number of usb devices
}

void Device::EnumDevices(){

    struct libusb_device *dev;
    int i = 0;
    int devcount = 0;
    uint8_t path[8];
    Devices.resize(Device::cnt);

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
            libusb_get_string_descriptor_ascii(dev_handle, desc.iProduct, Devices.at(devcount).Product, 100);
            libusb_get_string_descriptor_ascii(dev_handle, desc.iManufacturer, Devices.at(devcount).Manufacturer, 100);
            libusb_get_port_numbers(dev, path, sizeof(path));

            Devices.at(devcount).VendorID = desc.idVendor;
            Devices.at(devcount).ProductID = desc.idProduct;
            Devices.at(devcount).SysPath += std::to_string(libusb_get_bus_number(dev)).append("-" + std::to_string(path[0]));

            devcount++;
        }
    }
    Device::DeviceCount = devcount;
}

void Device::CloseSession(){
    libusb_exit(ctx); //close the session
}

Device::~Device(){
    libusb_free_device_list(devs, 1);
    Device::CloseSession();
}
