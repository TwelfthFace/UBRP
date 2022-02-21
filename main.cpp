#include "mainwindow.h"

#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //cout << "HELLO" << endl;
    return a.exec();
}
