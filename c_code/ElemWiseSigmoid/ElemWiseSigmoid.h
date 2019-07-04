#ifndef _ELEMWISESIGMOID_H
#define _ELEMWISESIGMOID_H
#include "ap_fixed.h"



typedef float dataType;
//typedef ap_fixed<22,10,AP_RND_CONV,AP_SAT> int_fix;

void ElemWiseSigmoid(float * , int , int);
void ElemWiseSigmoid_single(float * , int , int);
#endif
