#include "testutils.h"
#include <iostream>

void printMatrix(const char *title, int *matrix, int rows, int cols)
{
    printf("%s\n", title);
    printf("----------------------------------\n");

    for (int i = 0; i < rows; i++)
    {
        printf("ROW: %02d --->  ", i);
        for (int j = 0; j < cols; j++)
        {
            printf(" %04d ", matrix[i * cols + j]);
        }
        printf("\n");
    }
    printf("\n");
}

// The convolution is all about summing the product of the window and the kernel
int applyKernelToWindow(char *kernel, int *window, int numKernelElements)
{
    int accumulator = 0;

    for (int idx = 0; idx < numKernelElements; idx++)
    {
        accumulator = accumulator + (kernel[idx] * window[idx]);
    }
    return accumulator;
}

void handcraftedConv2D(int *matrixIn,
                  int *matrixOut,
                  char *kernel,
                  int kSize, int height, int width)
{
    int kCenterX = kSize / 2;
    int kCenterY = kSize / 2;
    int accConvolution = 0;
    int numKernelElements = kSize * kSize;
    int samplingWindow[KERNEL_DIM * KERNEL_DIM];

    for (int rows = 0; rows < height; rows++)
    {
        for (int cols = 0; cols < width; cols++)
        {
            accConvolution = 0;
            // Populate our window by sampling on the matrix
            for (int rowsWindow = 0; rowsWindow < kSize; rowsWindow++)
            {
                for (int colsWindow = 0; colsWindow < kSize; colsWindow++)
                {
                    // The window must be centered on the current pixel, so we need to
                    // subtract some pixels back from the current positon
                    int repos_row = rows - (kSize - 1) / 2 + rowsWindow;
                    int repos_col = cols - (kSize - 1) / 2 + colsWindow;
                    int currPixVal = 0;
                    if (repos_row >= 0 && repos_row < height && repos_col >= 0 && repos_col < width)
                    {
                        currPixVal = *(matrixIn + repos_row * width + repos_col);
                    }
                    samplingWindow[rowsWindow * kSize + colsWindow] = currPixVal;
                }
            }

            // Now multiply the window by the kernel and sum it's result
            accConvolution = applyKernelToWindow((char *)kernel,
                                                    (int *)samplingWindow,
                                                    numKernelElements);

            matrixOut[rows * WIDTH + cols] = accConvolution;
        }
    }
}
