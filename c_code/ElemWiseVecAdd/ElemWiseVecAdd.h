#ifndef _ELEMWISEVECADD_H
#define _ELEMWISEVECADD_H
#include "ap_fixed.h"

const int len = 100;

typedef float dataType;
//typedef ap_fixed<22,10,AP_RND_CONV,AP_SAT> int_fix;

void ElemWiseVecAdd(const dataType in1[], const dataType in2[], dataType out[]);
#endif
