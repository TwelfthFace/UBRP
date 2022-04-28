#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

QString Dialog::get_line_admin_email(){
    return ui->line_admin_email->text();
}

QString Dialog::get_line_sql_url(){
    return ui->line_sql_url->text();
}

QString Dialog::get_line_sql_user(){
    return ui->line_sql_user->text();
}

QString Dialog::get_line_sql_pass(){
    return ui->line_sql_password->text();
}

void Dialog::set_line_admin_email(QString email){
    ui->line_admin_email->setText(email);
}

void Dialog::set_line_sql_url(QString url){
    ui->line_sql_url->setText(url);
}

void Dialog::set_line_sql_user(QString user){
    ui->line_sql_user->setText(user);
}

void Dialog::set_line_sql_pass(QString pass){
    ui->line_sql_password->setText(pass);
}


Dialog::~Dialog()
{
    //delete ui;
}

