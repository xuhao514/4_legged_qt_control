#ifndef RUNTHREAD_H
#define RUNTHREAD_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTime>
#include <QCoreApplication>

#include "walk.h"
#include "data_processing.h"
#include "bluetoothproxy.h"

//运动线程
class RunThread : public QThread
{
    Q_OBJECT
signals:
   void imgDequeue(QImage _img);  //图像出队

public:
    explicit RunThread(QObject *parent = nullptr);
    void run();
    BluetoothProxy *blue_window;
    WalkClass walk;
private:
     LegClass leg_fl,leg_fr,leg_bl,leg_br;
     WalkLegClass walk_leg_fl,walk_leg_bl;

     DataProcess data_process;
     struct SteerAngle
     {
       float c1[4];
       float c4[4];
     };
     SteerAngle steer_ang;

     struct YPR{
       float y,p,r;
     };
     YPR ypr_data;

     struct ArduinoState
     {
       float update_dt;
       float rec_msg_dt;
      // bool imu_connected;
     };
     ArduinoState arduino_state;

     void sendConMsg();
     void getMsg();
};


#endif // RUNTHREAD_H
