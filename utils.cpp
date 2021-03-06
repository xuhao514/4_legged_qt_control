#include "utils.h"

//被Bezier()调用  绘制单方向的贝赛尔曲线
float decas(int degree,float coeff[],float t){
     int r,i;
     float point[15];   //最大14阶贝赛尔曲线
     for(i=0;i<degree;i++){
         point[i]=coeff[i];
     }
     for(r=1;r<degree;r++){
        for(i=0;i<degree-r;i++){
            point[i]=(1-t)*point[i]+t*point[i+1];
        }
     }
     return (point[0]);
}

//绘制n阶贝赛尔曲线   获得坐标(x,y);   mx[],my[] 控制点坐标数组;  n 数组长度
void Bezier(float *x,float *y,float mx[],float my[],int n,float t){
   *x=decas(n,mx,t);
   *y=decas(n,my,t);
}


//坐标旋转  (x0,y0)旋转中心;(x,y)旋转值   a 旋转弧度 逆时针为正
void Rotate(float*x,float *y,float x0,float y0,float a){
    float x1=*x;
    float y1=*y;
    *x=(x1-x0)*cos(a)-(y1-y0)*sin(a)+x0;
  *y=(y1-y0)*cos(a)+(x1-x0)*sin(a)+y0;
}

//平面围绕原点旋转
void Roat(float *x,float *y,float c){
    float mx=*x; float my=*y;
    *x=mx*cos(c)-my*sin(c);
    *y=mx*sin(c)+my*cos(c);
}

//线性插值  ；_start 起始值;  _end终值；  _t ：0-1 比例，大于1返回1
float Lerp(float _start,float _end,float _t)
{
      if(_t>1) _t=1;
      return (_end - _start)* _t + _start;
}

//线性改变值  val：目标变量； setval：设定值； k：单次变化值； _threshold：阈值
void LineToValue(float *val,float setval,float k,float _threshold)
{
     if(fabs(*val-setval)>_threshold)
           *val-=k * (*val-setval)/fabs(*val-setval);
     else *val=setval;
}
