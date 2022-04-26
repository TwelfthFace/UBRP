#include "mainwindow.h"
#include "emailsmtp.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    //EmailSMTP test("Authorised","08cd","9cfe","Logitech","Reciever");

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("U.B.R.P");
    w.show();

    return a.exec();

}
