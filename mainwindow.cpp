#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dev = new Device();
    auth = new AuthRule(*dev);
    dev->enumerate_devices();
    MainWindow::generate_device_items();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dev;
    delete auth;
}

void MainWindow::generate_device_items(){
    ui->comboBox_AvailableDevices->clear();
    ui->listWidget_Whitelist->clear();

    for(int i = 0; i < dev->device_count; i++){
        if(dev->devices.at(i).authorised == true){
            ui->listWidget_Whitelist->addItem(QString::fromStdString(dev->devices.at(i).get_string()));
        }else{
            ui->comboBox_AvailableDevices->addItem(QString::fromStdString(dev->devices.at(i).get_string()));
        }
    }
}

void MainWindow::on_pushButton_Add_pressed()
{    
    const std::string vendor = ui->comboBox_AvailableDevices->currentText().mid(0,4).toStdString();
    const std::string product = ui->comboBox_AvailableDevices->currentText().mid(5,4).toStdString();
    Device::workable_device* device_selection = dev->get_device(*dev, vendor, product);

    ui->listWidget_Whitelist->addItem(ui->comboBox_AvailableDevices->currentText());

    if(device_selection != nullptr){
        auth->create_rule(device_selection->product_id, device_selection->vendor_id, device_selection->sys_path);
    }

    EmailSMTP email(device_selection->authorised, device_selection->vendor_id.c_str(),
                   device_selection->product_id.c_str(),
                   device_selection->get_char_array(device_selection->manufacturer).c_str(),
                   device_selection->get_char_array(device_selection->product).c_str());

    statusBar()->showMessage("Email Sent!", 1000);
    MainWindow::generate_device_items();
}


void MainWindow::on_pushButton_Remove_pressed()
{
    if(ui->listWidget_Whitelist->currentItem()){
        const std::string vendor = ui->listWidget_Whitelist->currentItem()->text().mid(0,4).toStdString();
        const std::string product = ui->listWidget_Whitelist->currentItem()->text().mid(5,4).toStdString();
        Device::workable_device* device_selection = dev->get_device(*dev, vendor, product);

        auth->remove_rule(vendor, product);
        ui->listWidget_Whitelist->takeItem(ui->listWidget_Whitelist->currentRow());

        EmailSMTP email(device_selection->authorised, device_selection->vendor_id.c_str(),
                       device_selection->product_id.c_str(),
                       device_selection->get_char_array(device_selection->manufacturer).c_str(),
                       device_selection->get_char_array(device_selection->product).c_str());

        statusBar()->showMessage("Email Sent!", 1000);
        MainWindow::generate_device_items();
    }
}

void MainWindow::on_pushRefresh_pressed()
{
    delete dev;
    delete auth;

    dev = new Device();
    auth = new AuthRule(*dev);

    statusBar()->showMessage("Refreshed!", 1000);
    MainWindow::generate_device_items();
}
