#include "walk.h"

void WalkClass::walkInit(LegClass &_legfr,LegClass &_legfl,LegClass &_legbr,LegClass &_legbl,float *_yaw_value)
{
    car_wid = 120;
    vacc=0.001f,wacc=0.001f;    //加速度
    t_floor_set=2000;            //设定周期
    l_set = 50;
    h_set = 20;
    //l_set=v_now*t_floor_set;
    v_now=l_set/t_floor_set ;   //设定速度  m/s
    V_Max_F=0.1,V_Max_B=-0.1, W_Max=0.2;
    yaw_value =  _yaw_value;
    setYaw = *yaw_value;
    prep_long=1000;

    pidYaw.PidInit(1,0.5f,0.05,0.0f,2.f,1.f);

    walkFr.init(_legfr,11,85,l_set,h_set,t_floor_set,1, 3./4, 1.0,1);
    walkFl.init(_legfl,11,85,l_set,h_set,t_floor_set,1, 3./4, 0  ,1);
    walkBr.init(_legbr,11,85,l_set,h_set,t_floor_set,1, 3./4, 0  ,1);
    walkBl.init(_legbl,11,85,l_set,h_set,t_floor_set,1, 3./4, 1.0,1);

//    walkFr.init(_legfr,11,85,l_set,h_set,t_floor_set,1./3, 3./4, 0,1);
//    walkFl.init(_legfl,11,85,l_set,h_set,t_floor_set,1./3, 3./4, 1./3  ,1);
//    walkBr.init(_legbr,11,85,l_set,h_set,t_floor_set,1./3, 3./4, 2./3  ,1);
//    walkBl.init(_legbl,11,85,l_set,h_set,t_floor_set,1./3, 3./4, 1.0,1);


    w_now=0; vr=vl=0;
    v_set=v_now,w_set=w_now;

     T_F_Min=500;       //最小着地相时长
     T_F_Max=4000;      //最大着地相时长
     MaxLToCalSpeed=0.200;  //m
     te_factor=0.5;   //0~1
     isSetSpeedFinished=false;
}

//准备阶段
void  WalkClass:: prepWalk()
{
    walkFr.move2InitPos(prep_long);
    walkFl.move2InitPos(prep_long);
    walkBr.move2InitPos(prep_long);
    walkBl.move2InitPos(prep_long);
}
//dt:ms
void WalkClass::update(float _dt)
{
    speedChange(_dt);

    walkFr.walkUpdate(_dt);
    walkFl.walkUpdate(_dt);
    walkBr.walkUpdate(_dt);
    walkBl.walkUpdate(_dt);
}

void WalkClass::startAct(bool _start)
{
    walkFr.startAct(_start);
    walkFl.startAct(_start);
    walkBr.startAct(_start);
    walkBl.startAct(_start);
}

void WalkClass::reset()  //有问题 没找到
{
    walkFr.reStart();
    walkFl.reStart();
    walkBr.reStart();
    walkBl.reStart();
}

void WalkClass::speedChange(float _dt)

{
    isSpeedChange();
    if(isSetSpeedFinished)  return;

    bool finished_V=false,finished_W=false;
    if(v_set>V_Max_F) v_set=V_Max_F;
    if(v_set<V_Max_B) v_set=V_Max_B;

    if(abs(v_set-v_now)>0.0001f)
    {
        if(v_set-v_now>0)
          v_now+= vacc*_dt;
        else
          v_now-= vacc*_dt;
        finished_V=false;
    }
    else finished_V=true;

    if(abs(w_set-w_now)>0.0001f)
    {
        if(w_set-w_now>0)
          w_now+= wacc*_dt;
        else
            w_now-= wacc*_dt;
      finished_W=false;
    }
    else finished_W=true;

     vr=(2*v_now + w_now*car_wid/1000)/2;       //等效双轮差速
     vl=2*v_now-vr;

     //只变步长  周期不变
    vl_rea=walkFl.setLegSpeed(vl,t_floor_set);
    walkBl.setLegSpeed(vl,t_floor_set);

    vr_rea=walkBr.setLegSpeed(vr,t_floor_set);
    walkFr.setLegSpeed(vr,t_floor_set);

    v_rea=(vl_rea+vr_rea)/2;
    w_rea=(vr_rea-vl_rea)/(car_wid/1000);

    isSetSpeedFinished=finished_V&&finished_W;
}

void WalkClass::isSpeedChange()
{
    if(abs(v_set-v_now)>0.0001f||abs(w_set-w_now)>0.0001f)
        isSetSpeedFinished=false;
}

void WalkClass::setSpeed(float _v,float _w)
{
    v_set = _v;
    w_set = _w;
}

void WalkClass::setTFloor(float _t)
{
    t_floor_set = _t;
    if(t_floor_set > T_F_Max) t_floor_set = T_F_Max;
    if(t_floor_set < T_F_Min) t_floor_set = T_F_Min;
    walkFr.set_t_floor(t_floor_set);
    walkFl.set_t_floor(t_floor_set);
    walkBr.set_t_floor(t_floor_set);
    walkBl.set_t_floor(t_floor_set);
}

//方向角调节
void WalkClass::balanceYaw()
{
    yawIncrease=pidYaw.pidIncUpdate(setYaw,*yaw_value);

//    //¸Ä±ä²½³¤ //Ö»ÔÚ×ÅµØÏàµ÷½Ú²½³¤
//	if(walkFl.phaFlag==inEffect) walkFl.L-=yawIncrease;  	  //×¢ÒâÕý¸ººÅ£¬ÓëÍÓÂÝÒÇ°²×°ÓÐ¹Ø
//	if(walkBl.phaFlag==inEffect) walkBl.L-=yawIncrease;
//	if(walkBr.phaFlag==inEffect) walkBr.L+=yawIncrease;
//	if(walkFr.phaFlag==inEffect) walkFr.L+=yawIncrease;

//	if(yawIncrease==0)  //Èç¹û½Ç¶ÈÆ«²îÐ¡ÓÚãÐÖµ
//	{
//	 if(walkFl.phaFlag==inAir)  //ÔÚÌ§ÍÈÏàÈÃÍÈ³¤·µ»ØÉè¶¨Öµ
//		 LineToValue(&walkFl.L,walkFl.Lst,2,3);

//	 if(walkBr.phaFlag==inAir)
//		 LineToValue(&walkBr.L,walkBr.Lst,2,3);

//	 if(walkFr.phaFlag==inAir)
//		 LineToValue(&walkFr.L,walkFr.Lst,2,3);

//	 if(walkBl.phaFlag==inAir)
//		 LineToValue(&walkBl.L,walkBl.Lst,2,3);
//	}
//	walkFl.SetBezier(walkFl.x0,walkFl.y0,walkFl.L,walkFl.H0,walkFl.bezierLen,walkFl.forward);
//	walkFr.SetBezier(walkFr.x0,walkFr.y0,walkFr.L,walkFr.H0,walkFr.bezierLen,walkFr.forward);
//	walkBl.SetBezier(walkBl.x0,walkBl.y0,walkBl.L,walkBl.H0,walkBl.bezierLen,walkBl.forward);
//	walkBr.SetBezier(walkBr.x0,walkBr.y0,walkBr.L,walkBr.H0,walkBr.bezierLen,walkBr.forward);
}
