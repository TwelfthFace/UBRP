#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "USBDevice.h"
#include "AuthRule.h"
#include "emailsmtp.h"
#include "parsedevicehistory.h"
#include "sqldatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QMessageBox messageBox;
    void generate_device_items();
    ~MainWindow();

private slots:
    void on_pushButton_Add_pressed();
    void on_pushButton_Remove_pressed();
    void on_pushRefresh_pressed();

    void on_button_Request_pressed();

private:
    Ui::MainWindow *ui;
    Device *dev;
    AuthRule *auth;
    SQLDatabase *db;
};
#endif // MAINWINDOW_H
