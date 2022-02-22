#include "mainwindow.h"
#include "USBDevice.h"

#include <QApplication>
#include <iostream>
#include <libusb-1.0/libusb.h>

using namespace std;

int main(int argc, char *argv[])
{
    Device dev;

    dev.GetDeviceCount();
    dev.PrintDevices();

    //QApplication a(argc, argv);
    //MainWindow w;
    //w.setWindowTitle("U.B.R.P");
    //w.show();

    dev.CloseSession();

    //return a.exec();
}
