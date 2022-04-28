#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    messageBox.setFixedSize(500,200);
    dev = new Device();
    auth = new AuthRule(*dev);
    db = new SQLDatabase();
    dev->enumerate_devices();

    MainWindow::generate_device_items();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dev;
    delete auth;
    delete db;
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

    statusBar()->showMessage("Email Sent!", 2000);
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

        statusBar()->showMessage("Email Sent!", 2000);
        MainWindow::generate_device_items();
    }
}

void MainWindow::on_pushRefresh_pressed()
{
    delete dev;
    delete auth;

    dev = new Device();
    auth = new AuthRule(*dev);

    statusBar()->showMessage("Refreshed!", 2000);
    MainWindow::generate_device_items();
}

void MainWindow::on_button_Request_pressed()
{
    std::ifstream json_file("history.json", std::ifstream::binary);
    if(json_file.good()){
        Json::Value device_history;
        ParseDeviceHistory get_history(json_file, device_history);

        for(Json::ArrayIndex i=0; i < device_history.size(); i++){
            int sqlInsert = db->SQLInsert(device_history[i]["conn"].asString().c_str(), device_history[i]["host"].asString().c_str(),
                    device_history[i]["vid"].asString().c_str(), device_history[i]["pid"].asString().c_str(),
                    device_history[i]["prod"].asString().c_str(), device_history[i]["manufact"].asString().c_str(),
                    device_history[i]["serial"].asString().c_str(), device_history[i]["port"].asString().c_str(),
                    device_history[i]["disconn"].asString().c_str());
            if(sqlInsert){
                messageBox.critical(0, "Insertion Failed" , "Check console for more details.");
                break;
            }
        }

        messageBox.setText("Records Retrieved...");
        messageBox.setInformativeText("See all records below!");
        messageBox.setDetailedText(db->SQLSelect());
        messageBox.setStandardButtons(QMessageBox::Ok);
        messageBox.setDefaultButton(QMessageBox::Ok);
        messageBox.setStyleSheet("QLabel{min-width: 600px;}");
        messageBox.exec();

        json_file.close();
    }else{
        messageBox.critical(0, "Missing JSON file.", "File missing './history.json' use USBRIP to generate the history file and place it in the same directory as UBRP.");
    }
}

