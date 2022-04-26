#ifndef EMAILSMTP_H
#define EMAILSMTP_H

#include "SMTP/opportunisticsecuresmtpclient.h"
#include <memory>
#include <stdexcept>

using namespace jed_utils;

class EmailSMTP
{
private:
    OpportunisticSecureSMTPClient client = OpportunisticSecureSMTPClient("smtp.gmail.com", 587);
    const char* server_email = "ubrpnotifications@gmail.com";
    Credential creds = Credential(server_email, "nugbteabjsjjklcd");
    const char* admin_email = "alcomeho@gmail.com";
public:
    EmailSMTP(const bool& action, const char* vendor_id, const char* product_id, const char* manufacturer, const char* product);
};

#endif // EMAILSMTP_H
