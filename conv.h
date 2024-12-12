#ifndef __CORE_H__
#define __CORE_H__

#include <hls_video.h>
#include "define.h"
#include <ap_axi_sdata.h>

// Our IP core
void do_convolution(int input[HEIGHT][WIDTH],
                   int output[HEIGHT][WIDTH],
                   char kernel[KERNEL_DIM * KERNEL_DIM]);

int sumWindow(hls::Window < KERNEL_DIM, KERNEL_DIM, int> *window);

#endif /* __CORE_H__ */
