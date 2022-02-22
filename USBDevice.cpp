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
}

void Device::GetDeviceCount(){
    cout<<cnt<<" Devices in list."<<endl; //print total number of usb devices
}

void Device::PrintDevices(){

    libusb_device *dev;
    int i = 0, j = 0;
    uint8_t path[8];

    while ((dev = devs[i++]) != NULL) {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor");
            return;
        }

        printf("%04x:%04x (bus %d, device %d)",
            desc.idVendor, desc.idProduct,
            libusb_get_bus_number(dev), libusb_get_device_address(dev));

        r = libusb_get_port_numbers(dev, path, sizeof(path));
        if (r > 0) {
            printf(" /sys/bus/usb/devices/%d-%d", libusb_get_bus_number(dev),path[0]);
            for (j = 1; j < r; j++)
                printf("path:::::%d", path[j]);
        }
        printf("\n");

    }
}

void Device::CloseSession(){
    libusb_exit(ctx); //close the session
}
