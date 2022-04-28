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
    std::string admin_email = "alcomeho@gmail.com";
public:
    EmailSMTP();
    int send_mail(const bool& action, const char* vendor_id, const char* product_id, const char* manufacturer, const char* product);
public:
    std::string get_admin_email();
public:
    void set_admin_email(std::string email);
};

#endif // EMAILSMTP_H
