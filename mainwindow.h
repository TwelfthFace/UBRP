#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "dialog.h"
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
    void on_actionConfigure_triggered();
    void on_actionEnable_Whitelist_triggered();

    void on_actionDisable_Whitelist_triggered();

private:
    void setup_dialog();
    void load_config();
    void triggerUDEVRules();
private:
    Ui::MainWindow *ui;
    Dialog* configwindow;
    Device *dev;
    AuthRule *auth;
    EmailSMTP *mail;
    SQLDatabase *db;
};
#endif // MAINWINDOW_H
