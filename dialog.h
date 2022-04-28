#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);

    QString get_line_admin_email();
    QString get_line_sql_url();
    QString get_line_sql_user();
    QString get_line_sql_pass();

    void set_line_admin_email(QString email);
    void set_line_sql_url(QString url);
    void set_line_sql_user(QString user);
    void set_line_sql_pass(QString pass);

    ~Dialog();
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
