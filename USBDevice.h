#pragma once
#include <libusb-1.0/libusb.h>
#include <string>
#include <vector>

class Device {
public:
    struct WorkableDevices{
    public:
        u_int16_t       ProductID;
        u_int16_t       VendorID;
        u_char          Manufacturer[100];
        u_char          Product[100];
        std::string     SysPath = "/sys/bus/usb/devices/";
    public:
        std::string get_char_array(const u_char* arr) const {
            std::string outstring = "";
            for(int i = 0; i < 100; i++){
                if (arr[i] != '\0'){
                    outstring += arr[i];
                }else{
                    break;
                }
            }
            return outstring;
        }
        std::string get_string() {
            return std::to_string(VendorID).append(":" + std::to_string(ProductID).append(" " + this->get_char_array(Manufacturer)).append(", " + get_char_array(Product)));
        }
    };
    std::vector<WorkableDevices> Devices;
    int DeviceCount; // DeviceCount - excluding hubs;
public:
    Device();
    void GetDeviceCount();
    void EnumDevices();
    void CloseSession();
    ~Device();
private:
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_device_handle *dev_handle; //a device handle
    libusb_context *ctx = nullptr; //a libusb session
    ssize_t cnt; //holding number of devices in list

};
