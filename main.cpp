#include "mainwindow.h"
#include "emailsmtp.h"
#include "sqldatabase.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("U.B.R.P");
    w.show();
    return a.exec();
}
