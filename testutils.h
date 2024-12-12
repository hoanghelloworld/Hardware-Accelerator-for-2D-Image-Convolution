#ifndef __TESTUTILS_H__
#define __TESTUTILS_H__

#include <stdio.h>
#include "conv.h"
#include "define.h"

int applyKernelToWindow(char *kernel,
                           int *window,
                           int numKernelElements);
void handcraftedConv2D(int *matrixIn,
                  int *matrixOut,
                  char *kernel,
                  int kSize, int height, int width);
void printMatrix(const char *title, int *matrix, int rows, int cols);

#endif /* ifndef __TESTUTILS_H__ */
