#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "USBDevice.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dev = new Device();
    MainWindow::generate_device_items();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dev;
}

void MainWindow::generate_device_items(){
    QStringList list;

    for(int i = 0; i < dev->DeviceCount; i++){
        list.push_back(QString::fromStdString(dev->Devices.at(i).get_string()));
    }
    ui->comboBox_AvailableDevices->addItems(list);
    dev->Devices.clear();
}

void MainWindow::on_pushButton_Add_pressed()
{
    if(!(ui->listWidget_Whitelist->findItems(ui->comboBox_AvailableDevices->currentText(), Qt::MatchExactly).length() > 0)){
        ui->listWidget_Whitelist->addItem(ui->comboBox_AvailableDevices->currentText());
    }
}


void MainWindow::on_pushButton_Remove_pressed()
{
    QListWidgetItem *it = ui->listWidget_Whitelist->takeItem(ui->listWidget_Whitelist->currentRow());
    delete it;
}

