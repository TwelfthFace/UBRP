#include "parsedevicehistory.h"

ParseDeviceHistory::ParseDeviceHistory(std::ifstream& history_file, Json::Value& device_history) : history_file(&history_file)
{
    history_file >> device_history;
}

ParseDeviceHistory::~ParseDeviceHistory(){
    history_file->close();
}
