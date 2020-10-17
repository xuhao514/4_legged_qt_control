#ifndef __UTILS_H
#define __UTILS_H
#include "math.h"


void Bezier(float *x,float *y,float mx[],float my[],int n,float t);
void Rotate(float*x,float *y,float x0,float y0,float a);
void Roat(float *x,float *y,float c);
float Lerp(float _start,float _end,float _t);
void LineToValue(float *val,float setval,float k,float _threshold);

#endif
