#ifndef _ELEMWISEVECMUL_H
#define _ELEMWISEVECMUL_H
#include "ap_fixed.h"

//typedef float dataType;
typedef ap_fixed<8,2,AP_RND_CONV,AP_SAT> dataType;

void ElemWiseVecMul(dataType[], dataType[], dataType[]);
#endif
