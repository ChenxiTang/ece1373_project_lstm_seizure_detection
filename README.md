# ece1373_project_seizure
cd data: Put all raw data, weights and other relevant data in this 
directory

cd c_code: Put all source c codes in this folder, make a new directory 
for different IP

cd hls_prj: If you have tcls script that could automatically rebuild all 
the IP, put them in there. If not, jut leave it empty as it is right now


NOTE ON RECONSTRUCTING THE PROJECT (in Linux environment) 

clone the repo and make sure your working directory is ~/ece1373_project_seizure

In the terminal:

source sourceme.sh
vivado -mode tcl
source TCL/top.tcl

These three commands will generate project directories and Vivado block designs containing MB processor, PCIe-AXI bridge, DDR4 MIG that addresses 2GB of memory, an FIR compiler, and seven dummy blocks to be replaced with HLS projects. After everything is set up, the GUI will open. 

More to be added:
*Current issues: PCIe-AXI Bridge Gen3 driver is not provided by Xilinx, we may not be able to use MB processor if we use PCIe-DMA bridge in Endpoint configuration, Ultrascale does not support PCIe-DMA bridge in root complex configuration (needed for MB processor control) 
