#pragma once
#include <iostream>
#include <fstream>

class AuthRule {
private:
    void enumerate_rules();
    void get_attr(const std::string &attr, const std::string &line, std::string &out);
public:
    AuthRule();
    void create_rule();
    void remove_rule();
};
