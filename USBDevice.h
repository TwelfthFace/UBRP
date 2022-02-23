#pragma once
#include <libusb-1.0/libusb.h>

class Device {
public:
    Device();
    void GetDeviceCount();
    void PrintDevices();
    void CloseSession();
private:
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_device_handle *dev_handle; //a device handle
    libusb_context *ctx = nullptr; //a libusb session
    ssize_t cnt; //holding number of devices in list
    int DeviceCount; // DeviceCounts - excluding hubs;
};
