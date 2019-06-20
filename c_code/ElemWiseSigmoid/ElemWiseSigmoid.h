#ifndef _ELEMWISESIGMOID_H
#define _ELEMWISESIGMOID_H
#include "ap_fixed.h"



typedef float dataType;
//typedef ap_fixed<22,10,AP_RND_CONV,AP_SAT> int_fix;

void ElemWiseSigmoid(dataType [], dataType []);
void sigmoidSingle(dataType, dataType &);
#endif
