#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <hls_math.h>
#include <vector>
#include <cassert>
#include <float.h>
#include <string.h>
#include "ap_int.h"
#include "ap_fixed.h"
#include "../matrix_vector_mult/matrix_vector.h"
#include "../ElemWiseSigmoid/ElemWiseSigmoid.h"
#include "../ElemWiseTanh/ElemWiseTanh.h"
#include "../ElemWiseVecAdd/ElemWiseVecAdd.h"
#include "../ElemWiseVecMul/ElemWiseVecMul.h"

typedef float dataType;

#define in 61440

void lstm(dataType * mem,            // global memory pointer
		int input_offset,       // offset of inputs
		int output_offset      // offset of outputs
){

	// Global memory interface
#pragma HLS INTERFACE m_axi port=mem depth=2147483648
	// Bind all control ports to a single bundle
#pragma HLS INTERFACE s_axilite port=input_offset
#pragma HLS INTERFACE s_axilite port=output_offset
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS


	//local variables
	dataType inputBRAM[110];
	//#pragma HLS ARRAY_PARTITION variable=inputBRAM complete dim=1
	dataType WhfBRAM[64*64];
	//#pragma HLS ARRAY_PARTITION variable=WhfBRAM complete dim=1
	dataType WxfBRAM[64*110];
	//#pragma HLS ARRAY_PARTITION variable=WxfBRAM complete dim=1
	dataType bfBRAM[64];
	//#pragma HLS ARRAY_PARTITION variable=bfBRAM complete dim=1

	dataType WhiBRAM[64*64];
	//#pragma HLS ARRAY_PARTITION variable=WhiBRAM complete dim=1
	dataType WxiBRAM[64*110];
	//#pragma HLS ARRAY_PARTITION variable=WxiBRAM complete dim=1
	dataType biBRAM[64];
	//#pragma HLS ARRAY_PARTITION variable=biBRAM complete dim=1
	dataType WhcBRAM[64*64];
	//#pragma HLS ARRAY_PARTITION variable=WhcBRAM complete dim=1
	dataType WxcBRAM[64*110];
	//#pragma HLS ARRAY_PARTITION variable=WxcBRAM complete dim=1
	dataType bcBRAM[64];
	//#pragma HLS ARRAY_PARTITION variable=bcBRAM complete dim=1
	dataType WhoBRAM[64*64];
	//#pragma HLS ARRAY_PARTITION variable=WhoBRAM complete dim=1
	dataType WxoBRAM[64*110];
	//#pragma HLS ARRAY_PARTITION variable=WxoBRAM complete dim=1
	dataType boBRAM[64];
	//#pragma HLS ARRAY_PARTITION variable=boBRAM complete dim=1


	dataType h_tmin1[64]={0};
	//for(int i =0; i<64; i++)
		//h_tmin1[i] =0;
	//#pragma HLS ARRAY_PARTITION variable=h_tmin1 complete dim=1

	dataType C_tmin1[64]={0};
	//for(int i =0; i<64; i++)
	//	C_tmin1[i] =0;

	//#pragma HLS ARRAY_PARTITION variable=C_tmin1 complete dim=1
	dataType mul_w_h[64];
	//#pragma HLS ARRAY_PARTITION variable=mul_w_h complete dim=1
	dataType mul_w_x[64];
	//#pragma HLS ARRAY_PARTITION variable=mul_w_x complete dim=1
	dataType sum_wh_wx_b[64];
	//#pragma HLS ARRAY_PARTITION variable=sum_wh_wx_b complete dim=1
	dataType ftBRAM[64];
	//#pragma HLS ARRAY_PARTITION variable=ftBRAM complete dim=1
	dataType itBRAM[64];
	//#pragma HLS ARRAY_PARTITION variable=itBRAM complete dim=1
	dataType CtildaBRAM[64];
	//#pragma HLS ARRAY_PARTITION variable=CtildaBRAM complete dim=1
	dataType OtBRAM[64];
	//#pragma HLS ARRAY_PARTITION variable=OtBRAM complete dim=1

	dataType mul_ft_ctmin1[64];
	//#pragma HLS ARRAY_PARTITION variable=mul_ft_ctmin1 complete dim=1
	dataType mul_it_ctilda[64];
	//#pragma HLS ARRAY_PARTITION variable=mul_it_ctilda complete dim=1
	dataType CtBRAM[64];
	//#pragma HLS ARRAY_PARTITION variable=CtBRAM complete dim=1
	dataType tanh_ct[64];
	//#pragma HLS ARRAY_PARTITION variable=tanh_ct complete dim=1
	dataType htBRAM[64];
	//#pragma HLS ARRAY_PARTITION variable=htBRAM complete dim=1
	dataType wgt_output[64];
	//#pragma HLS ARRAY_PARTITION variable=wgt_output complete dim=1
	dataType bias_output;

	dataType outputBRAM,sig_out;

	int temp = input_offset/sizeof(dataType);
	int temp_offset = temp + in*110;
	//int temp_offset = mem + temp_elem;

	//Copy data for forget gate
	memcpy(WhfBRAM, (const dataType*)(mem+temp_offset), 4096*sizeof(dataType));
	memcpy(WxfBRAM, (const dataType*)(mem+temp_offset+4096), 7040*sizeof(dataType));
	memcpy(bfBRAM, (const dataType*)(mem+temp_offset+11136), 64*sizeof(dataType));

	//cpy data for it gate
	memcpy(WhiBRAM, (const dataType*)(mem+temp_offset+11200), 4096*sizeof(dataType));
	memcpy(WxiBRAM, (const dataType*)(mem+temp_offset+15296), 7040*sizeof(dataType));
	memcpy(biBRAM, (const dataType*)(mem+temp_offset+22336), 64*sizeof(dataType));

	//cpy data for Ctilda gate
	memcpy(WhcBRAM, (const dataType*)(mem+temp_offset+22400), 4096*sizeof(dataType));
	memcpy(WxcBRAM, (const dataType*)(mem+temp_offset+26496), 7040*sizeof(dataType));
	memcpy(bcBRAM, (const dataType*)(mem+temp_offset+33536), 64*sizeof(dataType));

	//cpy data for Ot gate
	memcpy(WhoBRAM, (const dataType*)(mem+temp_offset+33600), 4096*sizeof(dataType));
	memcpy(WxoBRAM, (const dataType*)(mem+temp_offset+37696), 7040*sizeof(dataType));
	memcpy(boBRAM, (const dataType*)(mem+temp_offset+44736), 64*sizeof(dataType));

	memcpy(wgt_output, (const dataType*)(mem+temp_offset + 44800), 64*sizeof(dataType));
	bias_output = mem[temp_offset + 44864];


	for(int i =0; i < in;i++){
		//copy the input values to local BRAMs
		memcpy(inputBRAM, (const dataType*) (mem+input_offset/sizeof(dataType))+ i*110, 110*sizeof(dataType));

		//calculating f_t
		mv_state(WhfBRAM, h_tmin1, mul_w_h);
		mv_input(WxfBRAM, inputBRAM, mul_w_x);
		ElemWiseVecAdd3(mul_w_h, mul_w_x, bfBRAM, sum_wh_wx_b);
		ElemWiseSigmoid(sum_wh_wx_b, ftBRAM);

		//calculating it
		mv_state(WhiBRAM, h_tmin1, mul_w_h);
		mv_input(WxiBRAM, inputBRAM, mul_w_x);
		ElemWiseVecAdd3(mul_w_h, mul_w_x, biBRAM, sum_wh_wx_b);
		ElemWiseSigmoid(sum_wh_wx_b, itBRAM);

		//calculating Ctilda
		mv_state(WhcBRAM, h_tmin1, mul_w_h);
		mv_input(WxcBRAM, inputBRAM, mul_w_x);
		ElemWiseVecAdd3(mul_w_h, mul_w_x, bcBRAM, sum_wh_wx_b);
		ElemWiseTanh(sum_wh_wx_b, CtildaBRAM);



		//calculating Ot
		mv_state(WhoBRAM, h_tmin1, mul_w_h);
		mv_input(WxoBRAM, inputBRAM, mul_w_x);
		ElemWiseVecAdd3(mul_w_h, mul_w_x, boBRAM, sum_wh_wx_b);
		ElemWiseSigmoid(sum_wh_wx_b, OtBRAM);

		//calculating C_t
		ElemWiseVecMul(ftBRAM, C_tmin1, mul_ft_ctmin1);
		ElemWiseVecMul(itBRAM, CtildaBRAM, mul_it_ctilda);
		ElemWiseVecAdd(mul_ft_ctmin1, mul_it_ctilda, CtBRAM);

		//calculating h_t
		ElemWiseTanh(CtBRAM, tanh_ct);
		ElemWiseVecMul(OtBRAM, tanh_ct, htBRAM);

		//calculating output
		mv_output(htBRAM, wgt_output, outputBRAM);
		outputBRAM = outputBRAM + bias_output;
		sigmoidSingle(outputBRAM, sig_out);
		mem[output_offset/sizeof(dataType)+ i] = sig_out;

		for(int j=0; j<64; j++){
			//#pragma HLS UNROLL
			h_tmin1[j] = htBRAM[j];
			C_tmin1[j] = CtBRAM[j];
		}
	}

}
