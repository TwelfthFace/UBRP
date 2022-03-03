#include "mainwindow.h"
#include "AuthRule.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //debug
    AuthRule rules;

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("U.B.R.P");
    w.show();

    return a.exec();
}
