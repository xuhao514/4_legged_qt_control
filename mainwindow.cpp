#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(BluetoothProxy *_blue_window,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    blue_window = _blue_window;
    run_thread = new RunThread();
    run_thread->blue_window = blue_window;
    run_thread->start();
    showTwist();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTwist()
{
    QString _vx = QString("vx   : %1").arg(run_thread->walk.get_v());
    QString _vw = QString("vw   : %1").arg(run_thread->walk.get_w());
    QString _l = QString("l   : %1").arg(run_thread->walk.get_l());
    QString _t_floor = QString("t_floor   : %1").arg(run_thread->walk.get_t_floor());
   // QString _fb_a = QString("ang    : %1").arg(con_mess.f_ang);
    ui->textBrowser->setText(_vx + "\n" + _vw + "\n" +_t_floor);
}

void MainWindow::on_pushButton_blue_clicked()
{
    blue_window->showFullScreen();
}

void MainWindow::on_pushButton_l_5_clicked()
{
    run_thread->walk.startAct(true);
}

void MainWindow::on_pushButton_pause_clicked()
{
    run_thread->walk.startAct(false);
}

void MainWindow::on_pushButton_restart_clicked()
{
   run_thread->walk.reset();
}

void MainWindow::on_pushButton_f_clicked()
{
    run_thread->walk.setSpeed(run_thread->walk.get_v()+0.002,run_thread->walk.get_w());
    showTwist();
}

void MainWindow::on_pushButton_b_clicked()
{
    run_thread->walk.setSpeed(run_thread->walk.get_v()-0.002,run_thread->walk.get_w());
    showTwist();
}

void MainWindow::on_pushButton_l_clicked()
{
    run_thread->walk.setSpeed(run_thread->walk.get_v(),run_thread->walk.get_w()+0.05);
    showTwist();
}

void MainWindow::on_pushButton_r_clicked()
{
    run_thread->walk.setSpeed(run_thread->walk.get_v(),run_thread->walk.get_w()-0.05);
    showTwist();
}

void MainWindow::on_pushButton_t_add_clicked()
{
    run_thread->walk.setTFloor(run_thread->walk.get_t_floor() + 100);
    showTwist();
}

void MainWindow::on_pushButton_t_re_clicked()
{
    run_thread->walk.setTFloor(run_thread->walk.get_t_floor() - 100);
    showTwist();
}
