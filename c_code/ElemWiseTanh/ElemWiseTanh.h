#ifndef _ELEMWISETANH_H
#define _ELEMWISETANH_H
#include "ap_fixed.h"

const int len = 100;

typedef float dataType;
//typedef ap_fixed<22,10,AP_RND_CONV,AP_SAT> int_fix;

void ElemWiseTanh(const dataType in[], dataType out[]);
#endif
