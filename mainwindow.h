#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bluetoothproxy.h"
#include "runthread.h"
#include <qdebug.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(BluetoothProxy *_blue_window,QWidget *parent = nullptr);
    ~MainWindow();
    BluetoothProxy *blue_window;
private slots:
    void on_pushButton_blue_clicked();

    void on_pushButton_l_5_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_restart_clicked();

    void on_pushButton_f_clicked();

    void on_pushButton_b_clicked();

    void on_pushButton_l_clicked();

    void on_pushButton_r_clicked();

    void on_pushButton_t_add_clicked();

    void on_pushButton_t_re_clicked();

private:
    Ui::MainWindow *ui;
    RunThread* run_thread;

    void showTwist();
};
#endif // MAINWINDOW_H
