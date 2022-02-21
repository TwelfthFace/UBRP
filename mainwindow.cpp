#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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

