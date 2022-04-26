#include "emailsmtp.h"
#include <iostream>

EmailSMTP::EmailSMTP(const bool& action, const char* vendor_id, const char* product_id, const char* manufacturer, const char* product)
{
    client.setCredentials(EmailSMTP::creds);
    try
    {
        const char* action_word = (action == 1) ? "Autherised" : "Unautherised";

        char body[300] = {'\0'};

        sprintf(body, "<html><h1>UBRP</h1>"
                      "<h2>%s</h2>"
                      "<ul><li>Vendor ID: %s</li>"
                      "<li>Product ID: %s</li><li>Manufacturer: %s</li><li>Product: %s</li></ul></html>", action_word, vendor_id,
                product_id, manufacturer, product);

        HTMLMessage msg(MessageAddress(server_email, "UBRP"),
            MessageAddress(admin_email),
            "UBRP", body);

        int err_no = client.sendMail(msg);
        if (err_no != 0) {
            std::cout << client.getCommunicationLog() << '\n';
            std::unique_ptr<char> errorMessage(client.getErrorMessage(err_no));
            std::cerr << "An error occurred: " << errorMessage.get()
                 << " (error no: " << err_no << ")" << '\n';
            std::cerr << "Error: Email Sending Failure... Check Terminal.";
        }
        std::cout << "Operation completed!" << std::endl;
    }
    catch (std::invalid_argument &err)
    {
        std::cerr << err.what() << std::endl;
    }

}

