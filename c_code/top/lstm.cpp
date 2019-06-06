#include <iostream>
#include <fstream>
#include <hls_math.h>
#include <vector>
#include <cassert>
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
	//Weights and biases offset
	int Wf_h_offset = input_offset;
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

	//calculating f_t
	mv_state(mem, Wf_h_offset, h_tmin1_offset, mul_wf_h_offset);
	mv_input(mem, Wf_x_offset, h_tmin1_offset, mul_wf_x_offset);
    ElemWiseVecAdd3(mem, mul_wf_h_offset, mul_wf_x_offset, bf_offset, sum_wfh_wfx_bf);
    ElemWiseSigmoid(mem, sum_wfh_wfx_bf, f_t_offset);

    //calculating it
	mv_state(mem, Wi_h_offset, h_tmin1_offset, mul_wi_h_offset);
	mv_input(mem, Wi_x_offset, h_tmin1_offset, mul_wi_x_offset);
    ElemWiseVecAdd3(mem, mul_wi_h_offset, mul_wi_x_offset, bi_offset, sum_wih_wix_bi);
    ElemWiseSigmoid(mem, sum_wih_wix_bi, i_t_offset);

    //calculating Ctilda
	mv_state(mem, Wc_h_offset, h_tmin1_offset, mul_wc_h_offset);
	mv_input(mem, Wc_x_offset, h_tmin1_offset, mul_wc_x_offset);
    ElemWiseVecAdd3(mem, mul_wc_h_offset, mul_wc_x_offset, bc_offset, sum_wch_wcx_bc);
    ElemWiseTanh(mem, sum_wch_wcx_bc, C_tilda_offset);

    //calculating Ot
	mv_state(mem, Wo_h_offset, h_tmin1_offset, mul_wo_h_offset);
	mv_input(mem, Wo_x_offset, h_tmin1_offset, mul_wo_x_offset);
    ElemWiseVecAdd3(mem, mul_wo_h_offset, mul_wo_x_offset, bo_offset, sum_woh_wox_bo);
    ElemWiseSigmoid(mem, sum_woh_wox_bo, O_t_offset);

    //calculating C_t
    ElemWiseVecMul(mem, f_t_offset, C_tmin1_offset, mul_ft_ctmin1_offset);
    ElemWiseVecMul(mem, i_t_offset, C_tilda_offset, mul_it_ctilda_offset);
    ElemWiseVecAdd(mem, mul_ft_ctmin1_offset, mul_it_ctilda_offset, C_t_offset);

    //calculating h_t
    ElemWiseTanh(mem, C_t_offset, tanh_ct_offset);
    ElemWiseVecMul(mem, O_t_offset, tanh_ct_offset, h_t_offset);

    //calculating output
    mv_output(mem, h_t_offset, bias_output_offset, output_offset);
}
