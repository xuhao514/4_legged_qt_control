#include "runthread.h"
void Delay(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

RunThread::RunThread(QObject *parent):QThread(parent)
{
    leg_fl.legInit(); leg_fr.legInit(); leg_bl.legInit(); leg_br.legInit();
    walk.walkInit(leg_fr,leg_fl,leg_br,leg_bl,&ypr_data.y);

}

void RunThread::run()
{
    walk.prepWalk();
    qDebug() << walk.get_t_floor();
    while (true) {
        if(blue_window->connected())
        {
            // walk_leg_fl.walkUpdate(update_dt);
            // walk_leg_bl.walkUpdate(update_dt);
            walk.update(10);
            sendConMsg();
            getMsg();
        }
        Delay(10);
    }
}

void RunThread::sendConMsg()
{
    if(!blue_window->connected())
    {
        return;
    }

    char* _arr; int _len;
    char _id = 1 ;
    steer_ang.c1[0] = leg_fr.get_c1();steer_ang.c1[1] = leg_fl.get_c1();
    steer_ang.c1[2] = leg_br.get_c1();steer_ang.c1[3] = leg_bl.get_c1();
    steer_ang.c4[0] = leg_fr.get_c4();steer_ang.c4[1] = leg_fl.get_c4();
    steer_ang.c4[2] = leg_br.get_c4();steer_ang.c4[3] = leg_bl.get_c4();
    _arr=data_process.dataEncode<SteerAngle>(&steer_ang,_id,&_len);
    blue_window->sendData(_arr,_len);
}

void RunThread::getMsg()
{
 QByteArray _rec_arr = blue_window->readData();
 for(int i=0; i<_rec_arr.size() ; i++ )
 {
      char _data = _rec_arr.data()[i];
      if(data_process.getHeadMsg(_data))
      {
        // printf("get_head\n");
        if(data_process.headId() == 11)
        {
          if(data_process.dataDecode<YPR>(_data,&ypr_data) )
          {
           // printf("yaw:%f\n",ypr_data.y);
          }
        }
        else if(data_process.headId() == 12)
        {
          if(data_process.dataDecode<ArduinoState>(_data,&arduino_state) )
          {
           // printf("arduino_update_dt :  %f\n",arduino_state.update_dt);
           // printf("arduino_rec_msg_dt: %f\n",arduino_state.rec_msg_dt);
            //qDebug()<< arduino_state.rec_msg_dt <<"\n";
          }
        }
        else
        {
          data_process.clearFlag();
        }

      }
 }
}
