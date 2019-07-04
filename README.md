# ece1373_project_seizure
Author:
Mohamed Adel, Chenxi Tang, Jamie, Koerner

Directory Descriptions:

data: All raw test data and final test data

c_code: All synthesisable C codes and software testbenches for different IPs

hls_prj: tcl scripts for Vivado HLS

TCL: tcl scripts to reconstruct this project

hw_code: source codes for hardware test program and SDK source files

support: board constraint files

IP_REPO: custom IPs, not genereated with Vivado HLS


NOTE ON GENERATING HW (THIS PROJECT WAS MADE WITHIN LINUX ENVIRONMENT, IT MAY NOT RUN WITH A WINDOWS OS)

clone the repo and make sure your working directory is the same as the path to this readme file. Change Vivado and SDK paths in sourceme.sh file as necessary. 

In the terminal:

source sourceme.sh

make prj

These two commands will synthesis HLS IPs and build Vivado block design. The systhesis and implementation settings will also be imported. When GUI is open,
open the block design to see connections and IPs used. Click Generate Bitstream to run through the Vivado design. When the operations are completed, launch
Xilinx SDK by

source TCL/sdk.tcl

This will create a new directory named hw.sdk in your working directory. Creat a C application in SDK and copy all files in hw_code/sdc_src into your application
project. Complie, program the FPGA, and launch a debug session to run the MicroBlaze progam. After this, 

make hw_test

This will generate Linux test program and driver to test the hardware. Use the following commands to run the test. 

make rescan

./hw_test
