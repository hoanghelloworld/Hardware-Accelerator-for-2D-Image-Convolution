#include "conv.h"
#include "define.h" // Make sure to include define.h

void do_convolution(int input[HEIGHT][WIDTH],
                   int output[HEIGHT][WIDTH],
                   char kernel[KERNEL_DIM * KERNEL_DIM])
{
#pragma HLS INTERFACE s_axilite port=input bundle=INPUT_BUS
#pragma HLS INTERFACE s_axilite port=output bundle=OUTPUT_BUS
#pragma HLS INTERFACE s_axilite port=kernel bundle=KERNEL_BUS
#pragma HLS INTERFACE s_axilite port=return bundle=CRTL_BUS

    hls::Window<KERNEL_DIM, KERNEL_DIM, int> window;

    // Iterate on all pixels for our HEIGHTxWIDTH
    for (int idxRow = 0; idxRow < HEIGHT; idxRow++) {
        for (int idxCol = 0; idxCol < WIDTH; idxCol++) {
#pragma HLS PIPELINE
            // Put data on the window and multiply with the kernel
            for (int idxWinRow = 0; idxWinRow < KERNEL_DIM; idxWinRow++) {
                for (int idxWinCol = 0; idxWinCol < KERNEL_DIM; idxWinCol++) {
                    int row = idxRow - KERNEL_DIM / 2 + idxWinRow;
                    int col = idxCol - KERNEL_DIM / 2 + idxWinCol;
                    int val = 0;
                    if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH)
                    {
                        val = input[row][col];
                    }
                    // Multiply kernel by the sampling window
                    val = (int)kernel[(idxWinRow * KERNEL_DIM) + idxWinCol] * val;
                    window.insert(val, idxWinRow, idxWinCol);
                }
            }

            // Calculate convolution result
            int valOutput = 0;
            valOutput = sumWindow(&window);

            output[idxRow][idxCol] = valOutput;
        }
    }
}

// Sum all values inside window (Already multiplied by the kernel)
int sumWindow(hls::Window<KERNEL_DIM, KERNEL_DIM, int> *window)
{
    int accumulator = 0;

    // Iterate on the window multiplying and accumulating the kernel and sampling
    // window
    for (int idxRow = 0; idxRow < KERNEL_DIM; idxRow++) {
        for (int idxCol = 0; idxCol < KERNEL_DIM; idxCol++) {
            accumulator = accumulator + (int)window->getval(idxRow, idxCol);
        }
    }
    return accumulator;
}
