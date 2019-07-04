/*
 *   Last modified on: 13 June 2019
 *             Author: Chenxi Tang
 *
 *  This application was created for the final course project of ECE1373 Digital Design for System-on-Chip
 *
 *  This is a RNN for seizure detection
 */


/*  h2c_transfer_flag: if data transfer from host to chip is done, the flag is 1
 *  c2h_transfer_flag: if data transfer from chip to host is done, the flag is 1,
 *  				   and PCIe driver starts to transfer data to host memory
 */


#include "xparameters.h"
#include "xil_io.h"
#include "add.h"
#include "microblaze_sleep.h"
#include "xlstm.h"
#include "PCIE_Status.h"
#include "xfir_top.h"


#define N 256
#define SIG_LENGTH 61440
#define n_bands 5
#define n_channel 22

typedef float dataType;

XFir_top FIR;
XFir_top_Config* FIR_Config;

XLstm LSTM;
XLstm_Config* LSTM_Config;




int main(){
	    int d = 110; //number of features
	    int n = 61440; // number of samples


	    int Wf_h = 64*64;
	    int Wf_x = 64*110;
	    int bf = 64;
	    int Wi_h = 64*64;
	    int Wi_x = 64*110;
	    int bi = 64;
	    int Wc_h = 64*64;
	    int Wc_x = 64*110;
	    int bc = 64;
	    int Wo_h = 64*64;
	    int Wo_x = 64*110;
	    int bo = 64;
	    int W_output = 64;
	    int b_output = 1;
	    int C_tmin1 = 64;
	    int h_tmin1 = 64;
	    int f_t = 64;
	    int i_t = 64;
	    int C_tilda = 64;
	    int C_t = 64;
	    int O_t = 64;
	    int h_t = 64;
	    int mul_wf_h = 64;
	    int mul_wf_x = 64;
	    int sum_wfh_wfx_bf = 64;
	    int mul_wi_h = 64;
	    int mul_wi_x = 64;
	    int sum_wih_wix_bi = 64;
	    int mul_wc_h = 64;
	    int mul_wc_x = 64;
	    int sum_wch_wcx_bc = 64;
	    int mul_wo_h = 64;
	    int mul_wo_x = 64;
	    int sum_woh_wox_bo = 64;
	    int mul_ft_ctmin1 = 64;
	    int mul_it_ctilda = 64;
	    int tanh_ct = 64;
	    int mul_W_ht = 64;
	    int sum_Wht_bias = 64;
	int x = n*d;
	 int output = n;

	 int size = N*n_bands+SIG_LENGTH*n_channel+x+Wf_h+Wf_x+bf+Wi_h+Wi_x+bi+Wc_h+Wc_x+bc+Wo_h+Wo_x+bo+W_output+b_output+C_tmin1+h_tmin1+f_t+i_t+C_tilda+C_t+O_t+h_t+mul_wf_h+mul_wf_x+sum_wfh_wfx_bf+mul_wi_h+mul_wi_x+sum_wih_wix_bi+mul_wc_h+mul_wc_x+sum_wch_wcx_bc+mul_wo_h+mul_wo_x+sum_woh_wox_bo+mul_ft_ctmin1+mul_it_ctilda+tanh_ct+mul_W_ht+sum_Wht_bias+output;

	u32 fir_input_offset=0;
	u32 fir_output_offset=0;
	u32 lstm_input_offset=(N*n_bands+n_channel*SIG_LENGTH)*sizeof(dataType);
	u32 lstm_output_offset=(size-n)*sizeof(dataType);



	// FIR initialisation
	if(XFir_top_Initialize(&FIR,FIR_id)!=XST_SUCCESS)
		return 1;
	FIR_Config=XFir_top_LookupConfig(FIR_id);
	XFir_top_DisableAutoRestart(&FIR);

	//LSTM initialisation
if(XLstm_Initialize(&LSTM,LSTM_id)!=XST_SUCCESS)
	return 1;
LSTM_Config=XLstm_LookupConfig(LSTM_id);
XLstm_DisableAutoRestart(&LSTM);

XFir_top_Set_input_add(&FIR,fir_input_offset);
XFir_top_Set_output_add(&FIR,fir_output_offset);
XLstm_Set_input_offset(&LSTM,lstm_input_offset);
XLstm_Set_output_offset(&LSTM,lstm_output_offset);

	//sync with PCIe
	PCIE_STATUS_mWriteReg((u32)XPAR_PCIE_STATUS_0_S00_AXI_BASEADDR,h2c_transfer_flag,(u32)0);
	PCIE_STATUS_mWriteReg((u32)XPAR_PCIE_STATUS_0_S00_AXI_BASEADDR,c2h_transfer_flag,0);
	int flag=1;
	while(flag){
		if(PCIE_STATUS_mReadReg((u32)XPAR_PCIE_STATUS_0_S00_AXI_BASEADDR,h2c_transfer_flag)==(u32)1) // get out of the loop when h2c tranfer is done
			flag=0;
		else{
			flag=1;
		}

		MB_Sleep(2001);
	};
	//start application


	while(!XFir_top_IsReady(&FIR)){};
	XFir_top_Start(&FIR);
	while(!XFir_top_IsDone(&FIR)){};


	//start LSTM

	while(!XLstm_IsReady(&LSTM)){};
	XLstm_Start(&LSTM);
	while(!XLstm_IsDone(&LSTM)){};


	//start sending data back to host via PCIe
	u32 done=1;
	PCIE_STATUS_mWriteReg((u32)XPAR_PCIE_STATUS_0_S00_AXI_BASEADDR,c2h_transfer_flag,done);

	return 0;
}





