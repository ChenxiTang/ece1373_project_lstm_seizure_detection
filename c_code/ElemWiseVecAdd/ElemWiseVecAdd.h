#ifndef _ELEMWISEVECADD_H
#define _ELEMWISEVECADD_H
#include "ap_fixed.h"


typedef float dataType;
//typedef ap_fixed<22,10,AP_RND_CONV,AP_SAT> int_fix;

void ElemWiseVecAdd(dataType *, int, int , int);
void ElemWiseVecAdd3(dataType *, int, int ,  int , int);
#endif
