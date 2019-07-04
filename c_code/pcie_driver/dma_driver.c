#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <byteswap.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/unistd.h>

#include "dma_test.h"


void xdma_driver(dataType*mem,
	const int dma_size,
	const int out_size,
	int input_offset,
	int output_offset
) {
	// Size to DMA in
	printf("start hardware function\n");
	int size = dma_size;
	int wait_time = 0;
	int status = 0;

	// constants setup
	volatile void* map_base;
	const char* pPath = getenv("XDMA");
	
	const char* ctrl_device_0 = "/dev/xdma0_user";
	const char* dma_to_device_0 = "/dev/xdma0_h2c_0";
	const char* dma_from_device_0 = "/dev/xdma0_c2h_0";
	
	const char* ctrl_device_1 = "/dev/xdma1_user";
	const char* dma_to_device_1 = "/dev/xdma1_h2c_0";
	const char* dma_from_device_1 = "/dev/xdma1_c2h_0";


	// Setup control registers
	int ctrl_fd;
	if (strcmp(pPath, "/dev/xdma0") == 0)
		ctrl_fd = open((const char*)ctrl_device_0, O_RDWR | O_SYNC);
	else
		ctrl_fd = open((const char*)ctrl_device_1, O_RDWR | O_SYNC);
	map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, ctrl_fd, 0);
	printf("Memory mapped at address %p.\n", map_base);

        
	
	char* in_buffer = NULL;
	char* allocated = NULL;

	// Create aligned memory alloc for DMA (should do this during initial read) 
	posix_memalign((void**)& allocated, 4096/*alignment*/, size * sizeof(dataType) + 4096);
	in_buffer = allocated;
	memcpy(in_buffer, (void*)mem, size * sizeof(dataType));
	printf("Copied input to buffer\n");

	// DMA input values
	int dma_to_device_fd;
	if (strcmp(pPath, "/dev/xdma0") == 0)
		dma_to_device_fd = open((const char*)dma_to_device_0, O_RDWR | O_NONBLOCK);
	else{
		dma_to_device_fd = open((const char*)dma_to_device_1, O_RDWR | O_NONBLOCK);
		printf("dma_to_device_fd done %d\n",dma_to_device_fd);

	}

	

	uint32_t addr = input_offset;
	lseek(dma_to_device_fd, addr, SEEK_SET);
	printf("lseek done\n");
	write(dma_to_device_fd, (char*)in_buffer, size * sizeof(dataType));
	printf("write function done\n");
	free(in_buffer);
	printf("Wrote inputs via DMA\n");


	status=1;
	write_int(map_base, PCIE_BASE+ h2c_reg, status);
	printf("status wrote\n");

	struct timespec ts_start, ts_end;
	clock_gettime(CLOCK_MONOTONIC, &ts_start);

	while (read_int(map_base,PCIE_BASE+ c2h_reg)==0) {
		sleep(3);
		printf("\rSleep wait %d", wait_time+=3);
		fflush(stdout);
	};
	clock_gettime(CLOCK_MONOTONIC, &ts_end);
	timespec_sub(&ts_end, &ts_start);
	printf("CLOCK_MONOTONIC reports %ld.%09ld seconds (total) for core\n", ts_end.tv_sec, ts_end.tv_nsec);
	int new_status=read_int(map_base,PCIE_BASE+ h2c_reg);
	printf("reg read %d\n",new_status);
	// DMA outputs back
	char* out_buffer = NULL;
	int dma_from_device_fd;
	if (strcmp(pPath, "/dev/xdma0") == 0)
		dma_from_device_fd = open((const char*)dma_from_device_0, O_RDWR | O_NONBLOCK);
	else
		dma_from_device_fd = open((const char*)dma_from_device_1, O_RDWR | O_NONBLOCK);


	posix_memalign((void**)& allocated, 4096/*alignment*/, out_size * sizeof(dataType) + 4096);
	out_buffer = allocated;
	lseek(dma_from_device_fd, output_offset, SEEK_SET);
	read(dma_from_device_fd, out_buffer, out_size * sizeof(dataType));
	printf("Outputs read via DMA\n");

	// copy results to result buffer
	memcpy((void*)(mem+size ), out_buffer, out_size * sizeof(dataType));
	free(out_buffer);
	close(dma_from_device_fd);
	close(dma_to_device_fd);
	 
}
