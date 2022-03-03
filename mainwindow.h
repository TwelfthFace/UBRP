#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <USBDevice.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void generate_device_items();
    ~MainWindow();

private slots:
    void on_pushButton_Add_pressed();
    void on_pushButton_Remove_pressed();

private:
    Ui::MainWindow *ui;
    Device *dev;
};
#endif // MAINWINDOW_H
