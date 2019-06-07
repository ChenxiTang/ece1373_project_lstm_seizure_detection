#ifndef _ELEMWISEVECMUL_H
#define _ELEMWISEVECMUL_H
#include "ap_fixed.h"

typedef float dataType;
//typedef ap_fixed<22,10,AP_RND_CONV,AP_SAT> int_fix;

void ElemWiseVecMul(dataType[], dataType[], dataType[]);
#endif
