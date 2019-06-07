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

void lstm(dataType * mem,            // global memory pointer
		int input_offset,       // offset of inputs
        int output_offset      // offset of outputs
		){

	// Global memory interface
	#pragma HLS INTERFACE m_axi port=mem depth=2147483648
	// Bind all control ports to a single bundle
	#pragma HLS INTERFACE s_axilite port=input_offset
	#pragma HLS INTERFACE s_axilite port=output_offset


	//Weights and biases offset
	int Wf_h_offset = input_offset + 64*1*sizeof(dataType);
	int Wf_x_offset = Wf_h_offset + 64*64*sizeof(dataType);
	int bf_offset = Wf_x_offset + 64*110*sizeof(dataType);

	int Wi_h_offset = bf_offset + 64*1*sizeof(dataType);
	int Wi_x_offset = Wi_h_offset + 64*64*sizeof(dataType);
	int bi_offset =  Wi_x_offset + 64*110*sizeof(dataType);

	int Wc_h_offset = bi_offset + 64*1*sizeof(dataType);
	int Wc_x_offset = Wc_h_offset + 64*64*sizeof(dataType);
	int bc_offset =  Wc_x_offset + 64*110*sizeof(dataType);

	int Wo_h_offset = bc_offset + 64*1*sizeof(dataType);
	int Wo_x_offset = Wo_h_offset + 64*64*sizeof(dataType);
	int bo_offset =  Wo_x_offset + 64*110*sizeof(dataType);

	int bias_output_offset = bo_offset + 64*1*sizeof(bo_offset);

	//Intermediate values' offset
	int C_tmin1_offset = bias_output_offset + 64*1*sizeof(dataType);
	int h_tmin1_offset = C_tmin1_offset + 64*1*sizeof(dataType);
	int f_t_offset = h_tmin1_offset + 64*1*sizeof(dataType);
	int i_t_offset = f_t_offset + 64*1*sizeof(dataType);
	int C_tilda_offset = i_t_offset + 64*1*sizeof(dataType);
	int C_t_offset = C_tilda_offset + 64*1*sizeof(dataType);
	int O_t_offset = C_t_offset + 64*1*sizeof(dataType);
	int h_t_offset = O_t_offset + 64*1*sizeof(dataType);

	//Calculated values
	int mul_wf_h_offset = h_t_offset + 64*1*sizeof(dataType);
	int mul_wf_x_offset = mul_wf_h_offset + 64*1*sizeof(dataType);
	int sum_wfh_wfx_bf = mul_wf_x_offset + 64*1*sizeof(dataType);

	int mul_wi_h_offset = h_t_offset + 64*1*sizeof(dataType);
	int mul_wi_x_offset = mul_wi_h_offset + 64*1*sizeof(dataType);
	int sum_wih_wix_bi = mul_wi_x_offset + 64*1*sizeof(dataType);

	int mul_wc_h_offset = h_t_offset + 64*1*sizeof(dataType);
	int mul_wc_x_offset = mul_wc_h_offset + 64*1*sizeof(dataType);
	int sum_wch_wcx_bc = mul_wc_x_offset + 64*1*sizeof(dataType);

	int mul_wo_h_offset = h_t_offset + 64*1*sizeof(dataType);
	int mul_wo_x_offset = mul_wo_h_offset + 64*1*sizeof(dataType);
	int sum_woh_wox_bo = mul_wo_x_offset + 64*1*sizeof(dataType);

	int mul_ft_ctmin1_offset = sum_woh_wox_bo + 64*1*sizeof(dataType);
	int mul_it_ctilda_offset = mul_ft_ctmin1_offset + 64*1*sizeof(dataType);
	int tanh_ct_offset = mul_it_ctilda_offset + 64*1*sizeof(dataType);


	//local variables
	dataType inputBRAM[64];
	dataType WhBRAM[64*64];
	dataType WxBRAM[64*110];
	dataType bBRAM[64];

	dataType h_tmin1[64] = {0};
	dataType C_tmin1[64] = {0};
	dataType mul_w_h[64];
	dataType mul_w_x[64];
	dataType sum_wh_wx_b[64];
	dataType ftBRAM[64];
	dataType itBRAM[64];
	dataType CtildaBRAM[64];
	dataType OtBRAM[64];

	dataType mul_ft_ctmin1[64];
	dataType mul_it_ctilda[64];
	dataType CtBRAM[64];
	dataType tanh_ct[64];
	dataType htBRAM[64];
	dataType bias_output[64];
	dataType outputBRAM;

	//copy the input values to local BRAMs
	memcpy(inputBRAM, (const dataType*) mem, 64*sizeof(dataType));

	//cpy data for forget gate
	memcpy(WhBRAM, (const dataType*)(mem+64), 64*64*sizeof(dataType));
	memcpy(WxBRAM, (const dataType*)(mem+64+64*64), 64*110*sizeof(dataType));
	memcpy(bBRAM, (const dataType*)(mem+64+64*64+64*110), 64*1*sizeof(dataType));

	//calculating f_t
	mv_state(WhBRAM, h_tmin1, mul_w_h);
	mv_input(WxBRAM, inputBRAM, mul_w_x);
    ElemWiseVecAdd3(mul_w_h, mul_w_x, bBRAM, sum_wh_wx_b);
    ElemWiseSigmoid(sum_wh_wx_b, ftBRAM);

	//cpy data for it gate
	memcpy(WhBRAM, (const dataType*)(mem+11200+64), 64*64*sizeof(dataType));
	memcpy(WxBRAM, (const dataType*)(mem+11200+64+64*64), 64*110*sizeof(dataType));
	memcpy(bBRAM, (const dataType*)(mem+11200+64+64*64+64*110), 64*1*sizeof(dataType));


    //calculating it
	mv_state(WhBRAM, h_tmin1, mul_w_h);
	mv_input(WxBRAM, inputBRAM, mul_w_x);
    ElemWiseVecAdd3(mul_w_h, mul_w_x, bBRAM, sum_wh_wx_b);
    ElemWiseSigmoid(sum_wh_wx_b, itBRAM);

	//cpy data for Ctilda gate
	memcpy(WhBRAM, (const dataType*)(mem+22400+64), 64*64*sizeof(dataType));
	memcpy(WxBRAM, (const dataType*)(mem+22400+64+64*64), 64*110*sizeof(dataType));
	memcpy(bBRAM, (const dataType*)(mem+22400+64+64*64+64*110), 64*1*sizeof(dataType));

    //calculating Ctilda
	mv_state(WhBRAM, h_tmin1, mul_w_h);
	mv_input(WxBRAM, inputBRAM, mul_w_x);
    ElemWiseVecAdd3(mul_w_h, mul_w_x, bBRAM, sum_wh_wx_b);
    ElemWiseTanh(sum_wh_wx_b, CtildaBRAM);

	//cpy data for Ctilda gate
	memcpy(WhBRAM, (const dataType*)(mem+33600+64), 64*64*sizeof(dataType));
	memcpy(WxBRAM, (const dataType*)(mem+33600+64+64*64), 64*110*sizeof(dataType));
	memcpy(bBRAM, (const dataType*)(mem+33600+64+64*64+64*110), 64*1*sizeof(dataType));

    //calculating Ot
	mv_state(WhBRAM, h_tmin1, mul_w_h);
	mv_input(WxBRAM, inputBRAM, mul_w_x);
    ElemWiseVecAdd3(mul_w_h, mul_w_x, bBRAM, sum_wh_wx_b);
    ElemWiseSigmoid(sum_wh_wx_b, OtBRAM);

    //calculating C_t
    ElemWiseVecMul(ftBRAM, C_tmin1, mul_ft_ctmin1);
    ElemWiseVecMul(itBRAM, CtildaBRAM, mul_it_ctilda);
    ElemWiseVecAdd(mul_ft_ctmin1, mul_it_ctilda, CtBRAM);

    //calculating h_t
    ElemWiseTanh(CtBRAM, tanh_ct);
    ElemWiseVecMul(OtBRAM, tanh_ct, htBRAM);

    memcpy(bias_output, (const dataType*)(mem+44800+64), 64*1*sizeof(dataType));

    //calculating output
    mv_output(htBRAM, bias_output, outputBRAM);
    mem[output_offset] = outputBRAM;

    for(int i=0; i<64; i++){
        h_tmin1[i] = htBRAM[i];
        C_tmin1[i] = CtBRAM[i];
    }

}
