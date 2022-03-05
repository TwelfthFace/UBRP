#pragma once
#include <iostream>
#include <fstream>
#include "USBDevice.h"

class AuthRule {
private:
    //std::string rule_file = "/etc/udev/rules.d/99-usb_auth.rules";
    std::string rule_file = "/home/danta/99-usb_auth.rules";
private:
    void enumerate_rules();
    void get_attr(const std::string &attr, const std::string &line, std::string &out);
    Device& dev;
public:
    AuthRule(Device& dev);
    void create_rule(const std::string &product, const std::string &vendor, const std::string &syspath);
    void remove_rule(const std::string &product, const std::string &vendor);
};
