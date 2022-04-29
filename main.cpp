#include <QApplication>
#include <unistd.h>
#include <sys/types.h>
#include "mainwindow.h"
#include "USBDevice.h"
#include "AuthRule.h"

int main(int argc, char *argv[])
{
    if(geteuid() == 0){
        if(argc >= 2){
            if(std::strcmp(argv[1], "-q") == 0){
                Device* dev = new Device;
                AuthRule* auth = new AuthRule(*dev);
                foreach (Device::workable_device device, dev->devices) {
                    if(!device.authorised){
                        device.mod_kernel_authentication(false);
                    }
                }
            }
        }else{
            QApplication a(argc, argv);
            MainWindow w;
            w.setWindowTitle("U.B.R.P");

            w.show();
            return a.exec();
        }
    }else{
        std::cout << "UBRP must be ran as root!" << std::endl;
        return 1;
    }
}
