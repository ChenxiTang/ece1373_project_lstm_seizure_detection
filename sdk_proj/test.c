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
#include "PCIE_Status.h"
#include "add.h"
#include "xsig_band_energy_gen_hw.h"
#include "xsig_band_energy_gen.h"
#include "sig_band.h"
#include "microblaze_sleep.h"

#define N 256
#define SIG_LENGTH 61440
#define n_bands 1
#define n_channel 1

typedef float dataType;

XSig_band_energy_gen Fir_device;
XSig_band_energy_gen_Config* Fir_config;

int main(){


	u32 out_offset = (N*n_bands+n_channel*SIG_LENGTH)*sizeof(dataType);

	if(XSig_band_energy_gen_Initialize(&Fir_device,FIR_id)!=XST_SUCCESS)
		return 1;
	Fir_config=XSig_band_energy_gen_LookupConfig(FIR_id);

	XSig_band_energy_gen_DisableAutoRestart(&Fir_device);

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

	XSig_band_energy_gen_Set_input_offset(&Fir_device,0);
	XSig_band_energy_gen_Set_output_offset(&Fir_device,out_offset);
	while(!XSig_band_energy_gen_IsReady(&Fir_device)){};
	XSig_band_energy_gen_Start(&Fir_device);
	while(!XSig_band_energy_gen_IsDone(&Fir_device)){};



	u32 done=1;
	PCIE_STATUS_mWriteReg((u32)XPAR_PCIE_STATUS_0_S00_AXI_BASEADDR,c2h_transfer_flag,done);

	return 0;
}





