source /opt/Xilinx/Vivado/2017.2/settings64.sh
source /opt/util/sourceme.sh
source ~/Xilinx/SDK/2017.2/settings64.sh
export CAFFE_ROOT=/opt/caffe
export PYCAFFE_ROOT=$CAFFE_ROOT/python
export PYTHONPATH=$PYCAFFE_ROOT:$PYTHONPATH
export PATH=$CAFFE_ROOT/build/tools:$PYCAFFE_ROOT:$PATH
export XILINXD_LICENSE_FILE=27012@mlm.ece.utoronto.ca:40012@mlm.ece.utoronto.ca
export JTAG="localhost:3121/xilinx_tcf/Digilent/210308A1D026"
export XDMA="/dev/xdma1"
export FPGA_PCI="0000:02:00.0"
export FPGA_PCI_ADDR="0000\:02\:00.0"
export FPGA_PASSWORD="ekYD3qPUAMbm49UD"

