#include "mainwindow.h"
#include "USBDevice.h"

#include <QApplication>
#include <iostream>
#include <iomanip>
#include <libusb-1.0/libusb.h>

using namespace std;

int main(int argc, char *argv[])
{
    Device dev;

    dev.GetDeviceCount();

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("U.B.R.P");
    w.show();

    //delete dev;

    return a.exec();
}
