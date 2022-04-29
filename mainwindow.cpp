#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <sys/stat.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    configwindow = new Dialog(this);
    dev = new Device();
    auth = new AuthRule(*dev);
    mail = new EmailSMTP();
    db = new SQLDatabase();
    dev->enumerate_devices();

    struct stat buffer;
    if(stat("/var/tmp/UBRP_enabled", &buffer) == 0){
        whitelist_enabled = true;
        ui->lbl_whitelist_status->setText("Whitelist Enabled");
    }else{
        whitelist_enabled = false;
        ui->lbl_whitelist_status->setText("Whitelist Disabled");
    }

    MainWindow::generate_device_items();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dev;
    delete auth;
    delete configwindow;
    delete mail;
    delete db;
}

void MainWindow::setup_dialog(){

    configwindow->set_line_admin_email(QString(mail->get_admin_email().c_str()));
    configwindow->set_line_sql_user(QString(db->get_sql_user().c_str()));
    configwindow->set_line_sql_pass(QString(db->get_sql_pass().c_str()));
    configwindow->set_line_sql_url(QString(db->get_url().c_str()));

    int returnval = configwindow->exec();
    if(returnval == 1){
        load_config();
    }
}

void MainWindow::load_config(){
    mail->set_admin_email(configwindow->get_line_admin_email().toStdString().c_str());
    db->set_sql_user(configwindow->get_line_sql_user().toStdString().c_str());
    db->set_sql_pass(configwindow->get_line_sql_pass().toStdString().c_str());
    db->set_url(configwindow->get_line_sql_url().toStdString().c_str());
    db->set_properties(configwindow->get_line_sql_user().toStdString().c_str(), configwindow->get_line_sql_pass().toStdString().c_str());

    db->try_connect(configwindow->get_line_sql_url().toStdString().c_str());
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
    if(ui->comboBox_AvailableDevices->currentIndex() >= 0){
        const std::string vendor = ui->comboBox_AvailableDevices->currentText().mid(0,4).toStdString();
        const std::string product = ui->comboBox_AvailableDevices->currentText().mid(5,4).toStdString();
        Device::workable_device* device_selection = dev->get_device(*dev, vendor, product);

        ui->listWidget_Whitelist->addItem(ui->comboBox_AvailableDevices->currentText());

        if(device_selection != nullptr){
            auth->create_rule(device_selection->product_id, device_selection->vendor_id, device_selection->sys_path);
            MainWindow::triggerUDEVRules();
            if(whitelist_enabled){
                device_selection->mod_kernel_authentication(true);

                int mailr = mail->send_mail(device_selection->authorised, device_selection->vendor_id.c_str(),
                                           device_selection->product_id.c_str(),
                                           device_selection->get_char_array(device_selection->manufacturer).c_str(),
                                           device_selection->get_char_array(device_selection->product).c_str());

                if(mailr == 0)
                {
                    statusBar()->showMessage("Email Sent!", 2000);
                }else {
                    statusBar()->showMessage("Email Send Failure!", 2000);
                }
            }
            MainWindow::generate_device_items();
        }
    }
}

void MainWindow::on_pushButton_Remove_pressed()
{
    if(ui->listWidget_Whitelist->currentItem()){
        const std::string vendor = ui->listWidget_Whitelist->currentItem()->text().mid(0,4).toStdString();
        const std::string product = ui->listWidget_Whitelist->currentItem()->text().mid(5,4).toStdString();
        Device::workable_device* device_selection = dev->get_device(*dev, vendor, product);

        ui->listWidget_Whitelist->takeItem(ui->listWidget_Whitelist->currentRow());

        if(device_selection != nullptr){
            auth->remove_rule(vendor, product);
            MainWindow::triggerUDEVRules();
            if(whitelist_enabled){
                device_selection->mod_kernel_authentication(false);
                int mailr = mail->send_mail(device_selection->authorised, device_selection->vendor_id.c_str(),
                                           device_selection->product_id.c_str(),
                                           device_selection->get_char_array(device_selection->manufacturer).c_str(),
                                           device_selection->get_char_array(device_selection->product).c_str());

                if(mailr == 0)
                {
                    statusBar()->showMessage("Email Sent!", 2000);
                }else {
                    statusBar()->showMessage("Email Send Failure!", 2000);
                }
            }
        }
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
    std::ifstream json_file("/etc/UBRP/history.json", std::ifstream::binary);
    if(db->SQLIsConnected()){
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
            messageBox.critical(0, "Missing JSON file.", "File missing '/etc/UBRP/history.json' use USBRIP to generate the history file and place it in the same directory as UBRP.");
        }
    }else{
        messageBox.critical(0, "Unable to connect to database", "Unable to connect to the database, check console for details.");
    }
}


void MainWindow::on_actionConfigure_triggered()
{
    MainWindow::setup_dialog();
}

void MainWindow::triggerUDEVRules(){
    std::system("udevadm control --reload");
}

void MainWindow::on_actionEnable_Whitelist_triggered()
{
    int msgans = messageBox.question(0, "Enable Whitelist?", "Are you sure you want to enable the whitelist? BE SURE that you have at least one keyboard/mouse whitelisted BEFORE CLICKING YES!"
                                                " This action could potentially lock you out of your computer, permanently. YOU HAVE BEEN WARNED. Once enabled any device from then on will be, by default,"
                                                          " unautherised.", QMessageBox::Yes|QMessageBox::No);

    if(msgans == QMessageBox::Yes && whitelist_enabled == false){
        whitelist_enabled = true;
        ui->lbl_whitelist_status->setText("Whitelist Enabled");

        std::system("touch /var/tmp/UBRP_enabled");
        std::system("find /sys/bus/usb/devices/usb*/ -name 'authorized_default' -exec sh -c 'echo 0 > {}' \\;");
        std::system("systemctl enable deauth_usb_inter.service");
        std::system("systemctl enable ubrp_persistence.service");

        foreach (Device::workable_device device, dev->devices) {
            if(!device.authorised){
                device.mod_kernel_authentication(false);
            }
        }

        MainWindow::triggerUDEVRules();
    }
}

void MainWindow::on_actionDisable_Whitelist_triggered()
{
    int msgans = messageBox.question(0, "Disable Whitelist?", "Are you sure you want to disable the whitelist? "
                                                              "Devices added from then on will be "
                                                              "autherised by default.", QMessageBox::Yes|QMessageBox::No);

    if(msgans == QMessageBox::Yes && whitelist_enabled == true){
        whitelist_enabled = false;
        ui->lbl_whitelist_status->setText("Whitelist Disabled");

        std::system("rm /var/tmp/UBRP_enabled");
        std::system("find /sys/bus/usb/devices/usb*/ -name 'authorized_default' -exec sh -c 'echo 1 > {}' \\;");
        std::system("systemctl disable deauth_usb_inter.service");
        std::system("systemctl disable ubrp_persistence.service");

        foreach (Device::workable_device device, dev->devices) {
            device.authorised = false;
            auth->remove_rule(device.vendor_id, device.product_id);
            device.mod_kernel_authentication(true);
        }

        MainWindow::on_pushRefresh_pressed();
        MainWindow::triggerUDEVRules();
    }
}

