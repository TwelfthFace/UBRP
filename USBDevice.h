#pragma once
#include <libusb-1.0/libusb.h>
#include <string>
#include <vector>

class Device {
public:
    struct workable_device{
        public:
            std::string         product_id;
            std::string         vendor_id;
            u_char              manufacturer[100];
            u_char              product[100];
            std::string         sys_path;
            bool                authorised = false;
        public:
            std::string get_char_array(const u_char* arr) const {
                std::string outstring = "";

                for(int i = 0; i < 50; i++){
                    if (arr[i] != '\0'){
                        outstring += arr[i];
                    }else{
                        break;
                    }
                }
                return outstring;
            }
            std::string get_string() const {
                return vendor_id + ":" + product_id + " " + this->get_char_array(manufacturer) + ", " + get_char_array(product);
            }

            void mod_kernel_authentication(bool authorised){
                std::string authbit = (authorised) ? "1" : "0";
                std::system(std::string("echo ").append(std::string(authbit).append(" > ") + sys_path).c_str());
            }
    };
    std::vector<workable_device> devices;
    int device_count; // device_count - excluding hubs;
public:
    Device();
    void enumerate_devices();
    Device::workable_device* get_device(Device& dev, const std::string& vendor, const std::string& product);
    ~Device();
private:
    libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    libusb_device_handle *dev_handle; //a device handle
    libusb_context *ctx = nullptr; //a libusb session
    ssize_t cnt; //holding number of devices in list

};
