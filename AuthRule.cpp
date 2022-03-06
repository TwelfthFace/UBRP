#include "AuthRule.h"
#include "string.h"

AuthRule::AuthRule(Device& dev) : dev(dev){
    AuthRule::enumerate_rules();
}

void AuthRule::create_rule(const std::string &product, const std::string &vendor, const std::string &syspath){
    std::ofstream output;

    output.open(AuthRule::rule_file, std::ios_base::app);

    const std::string templaterule = "ACTION==\"add\", SUBSYSTEM==\"usb\", ATTR{idVendor}==\"" + vendor +"\", ATTR{idProduct}==\"" + product + "\", RUN+=\"/bin/sh -c 'echo 1 > " + syspath + "'\"";

    if(dev.get_device(dev, vendor, product) != nullptr){
        output << templaterule + "\n";
        dev.get_device(dev, vendor, product)->authorised = true;
    }
    output.close();
}

void AuthRule::remove_rule(const std::string &product, const std::string &vendor){
    std::ifstream input(AuthRule::rule_file);
    std::ofstream output;

    std::string content((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

    input.open(AuthRule::rule_file);

    if(!input.is_open())
        exit(EXIT_FAILURE);

    input.close();

    output.open(AuthRule::rule_file);

    char* copy = strdup(content.c_str());
    char* point = strtok(copy, "\n");
    std::string rules = "";

    while (point != nullptr) {
        std::string rule = point;
        if(rule.find(product) == std::string::npos && rule.find(product) == std::string::npos){
            rules += rule + "\n";
        }
        point  = strtok(nullptr, "\n");
    }

    free(copy);

    output << rules;
    output.close();
    dev.get_device(dev, vendor, product)->authorised = false;

}

void AuthRule::enumerate_rules(){
    std::ifstream input;

    input.open(AuthRule::rule_file, std::ios_base::out & std::ios_base::in);

    if(input.is_open()){
        std::string line;
        while (getline(input, line)){
            std::string vendor;
            std::string product;
            AuthRule::get_attr("idVendor", line, vendor);
            AuthRule::get_attr("idProduct", line, product);
            dev.get_device(dev, vendor, product)->authorised = true;
        }
    }
    input.close();
}

void AuthRule::get_attr(const std::string &attr, const std::string &line, std::string &out){
   for(u_long c = attr.size() + 4; line[line.find(attr) + c] != 34; c++){
        out += line[line.find(attr) + c];
    }
}
