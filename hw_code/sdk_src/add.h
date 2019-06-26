/*
 * add.h
 *
 *  Created on: Jun 20, 2019
 *      Author: tangche
 */

#ifndef SRC_ADD_H_
#define SRC_ADD_H_

#include "xparameters.h"
#include "xlstm.h"
#include "PCIE_Status.h"
#include "xfir_top.h"
#include "sig_band.h"

#define h2c_transfer_flag PCIE_STATUS_S00_AXI_SLV_REG0_OFFSET
#define c2h_transfer_flag PCIE_STATUS_S00_AXI_SLV_REG1_OFFSET

#define FIR_id XPAR_XFIR_TOP_0_DEVICE_ID
#define LSTM_id XPAR_LSTM_0_DEVICE_ID

#endif /* SRC_ADD_H_ */
