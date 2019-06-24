/*
 * sig_bang.h
 *
 *  Created on: Jun 20, 2019
 *      Author: tangche
 */

#ifndef SRC_SIG_BAND_H_
#define SRC_SIG_BAND_H_

#include "xil_types.h"
#include "xstatus.h"
#include "xsig_band_energy_gen_hw.h"

#define SIG_mWriteReg(BaseAdd,RegOffset,data)\
	Xil_Out32(BaseAdd+RegOffset,(u32)data)

#define SIG_mReadReg(BaseAdd, RegOffset)\
	Xil_In32(BaseAdd+RegOffset)

#endif /* SRC_SIG_BAND_H_ */
