#include "AuthRule.h"

AuthRule::AuthRule(){
    AuthRule::enumerate_rules();
}

void AuthRule::enumerate_rules(){
    std::string file_name = "99-usb_auth.rules";
    std::ifstream input;

    input.open("/home/danta/" + file_name);

    if(input.is_open()){
        std::string line;
        while (getline(input, line)){
            std::string vendor;
            std::string product;

            AuthRule::get_attr("idVendor", line, vendor);
            AuthRule::get_attr("idProduct", line, product);
            std::cout << vendor << " " << product << std::endl;
        }
    }else{
        exit(EXIT_FAILURE);
    }
}

void AuthRule::get_attr(const std::string &attr, const std::string &line, std::string &out){
   for(u_long c = attr.size() + 4; line[line.find(attr) + c] != 34; c++){
        out += line[line.find(attr) + c];
    }
}
