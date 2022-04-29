#include "emailsmtp.h"
#include <iostream>

EmailSMTP::EmailSMTP()
{
    client.setCredentials(EmailSMTP::creds);
}

int EmailSMTP::send_mail(const bool& action, const char* vendor_id, const char* product_id, const char* manufacturer, const char* product){
    try
    {
        const char* action_word = (action == 1) ? "AUTHORISED" : "UNAUTHORISED";
        char hostname[HOST_NAME_MAX+1];

        gethostname(hostname, HOST_NAME_MAX+1);

        char body[300] = {'\0'};

        sprintf(body, "<html>"
                      "<h2>A Device has been %s</h2>"
                      "<ul><li>Host: %s</li>"
                      "<li>Vendor ID: %s</li>"
                      "<li>Product ID: %s</li>"
                      "<li>Manufacturer: %s</li>"
                      "<li>Product: %s</li></ul>"
                      "</html>", action_word, hostname,vendor_id,
                        product_id, manufacturer, product);
        std::string subject = "Device ";
            subject += action_word;
            subject += " from host: ";
            subject += std::string(hostname);

        HTMLMessage msg(MessageAddress(server_email, "UBRP"),
            MessageAddress(admin_email.c_str()),
            subject.c_str(), body);

        int err_no = client.sendMail(msg);

        if (err_no != 0) {
            std::cout << client.getCommunicationLog() << '\n';
            std::unique_ptr<char> errorMessage(client.getErrorMessage(err_no));
            std::cerr << "An error occurred: " << errorMessage.get()
                 << " (error no: " << err_no << ")" << '\n';
        }
        return err_no;
    }
    catch (std::invalid_argument &err)
    {
        std::cerr << err.what() << std::endl;
        return 1;
    }
}

std::string EmailSMTP::get_admin_email(){
    return EmailSMTP::admin_email;
}

void EmailSMTP::set_admin_email(std::string email){
    EmailSMTP::admin_email = email;
}
