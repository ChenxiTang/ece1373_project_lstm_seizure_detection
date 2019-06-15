# ece1373_project_seizure
cd data: Put all raw data, weights and other relevant data in this 
directory

cd c_code: Put all source c codes in this folder, make a new directory 
for different IP

cd hls_prj: If you have tcls script that could automatically rebuild all 
the IP, put them in there. If not, jut leave it empty as it is right now


NOTE ON GENERATING HW FOR SINGLE IP TEST	

clone the repo and make sure your working directory is ~/ece1373_project_seizure/

In the terminal:

source sourceme.sh

make ip_test

If there is no bug, you should be able to see the block design opened. Add your IP to IP repo path and replace dummy with your test IP. Change offset address to a 
low value (0x00010000 for example). Click generate bit stream. 

When generation is finished, you may see warnings about timing issues. It will be improved for the final design. If WNS<-1ns, it may be safe to ignore for now. 

Open Hardware Manager and program the board. 

After the board is programmed, compile your testbench and use the following command to make sure that the host PC knows where PCIe device is

make rescan

After this you can run your test program.