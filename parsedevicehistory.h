#ifndef PARSEDEVICEHISTORY_H
#define PARSEDEVICEHISTORY_H
#include <jsoncpp/json/json.h>
#include <iostream>
#include <fstream>

class ParseDeviceHistory
{
private:
    std::ifstream* history_file;
public:
    ParseDeviceHistory(std::ifstream& history_file, Json::Value& device_history);
    ~ParseDeviceHistory();
};

#endif // PARSEDEVICEHISTORY_H
