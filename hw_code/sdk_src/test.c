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
#include "sig_band.h"

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

	u32 fir_input_offset=0;
	u32 fir_output_offset=0;
	u32 lstm_input_offset=0;
	u32 lstm_output_offset=0;

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

	//sync with PCIe
	PCIE_STATUS_mWriteReg((u32)XPAR_PCIE_STATUS_0_S00_AXI_BASEADDR,h2c_transfer_flag,(u32)0);
	int flag=1;
	while(flag){
		if(PCIE_STATUS_mReadReg((u32)XPAR_PCIE_STATUS_0_S00_AXI_BASEADDR,h2c_transfer_flag)==(u32)1) // get out of the loop when h2c tranfer is done
			flag=0;
		else{
			flag=1;
		}

		MB_Sleep(2000);
	};
	//start application
	XFir_top_Set_input_add(&FIR,fir_input_offset);
	XFir_top_Set_output_add(&FIR,fir_output_offset);

	while(!XFir_top_IsReady(&FIR)){};
	XFir_top_Start(&FIR);
	while(!XFir_top_IsDone(&FIR)){};

	/*
	//start LSTM
	XLstm_Set_input_offset(&LSTM,lstm_input_offset);
	XLstm_Set_output_offset(&LSTM,lstm_output_offset);
	while(!XLstm_IsReady(&LSTM)){};
	XLstm_Start(&LSTM);
	while(!XLstm_IsDone(&LSTM)){};
*/

	//start sending data back to host via PCIe
	u32 done=1;
	PCIE_STATUS_mWriteReg((u32)XPAR_PCIE_STATUS_0_S00_AXI_BASEADDR,c2h_transfer_flag,done);

	return 0;
}





