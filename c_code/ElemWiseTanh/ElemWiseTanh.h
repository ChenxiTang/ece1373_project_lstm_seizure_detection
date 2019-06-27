#ifndef _ELEMWISETANH_H
#define _ELEMWISETANH_H
#include "ap_fixed.h"


//typedef float dataType;
typedef ap_fixed<10,3,AP_RND_CONV,AP_SAT> dataType;

void ElemWiseTanh(dataType[], dataType []);

#endif
