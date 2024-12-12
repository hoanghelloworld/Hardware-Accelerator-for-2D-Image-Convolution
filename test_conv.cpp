#include <stdio.h>
#include "conv.h"
#include "testutils.h"

// Edge
char kernel[KERNEL_DIM * KERNEL_DIM] = {
    -1, -1, -1,
    -1, 8, -1,
    -1, -1, -1,
};

int main()
{
    // Define input and output matrices
    int input[HEIGHT][WIDTH] = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };
    int output[HEIGHT][WIDTH] = {0};
    int output_ref[HEIGHT][WIDTH] = {0};

    // Do the convolution on the core
    printf("Calling Core function\n");
    do_convolution(input, output, kernel);
    printf("Core function ended\n");

    // Print the output matrix
    printf("Output Matrix:\n");
    printMatrix("Result Core", (int *)output, HEIGHT, WIDTH);

    // Do the convolution (Reference)
    printf("Calling Reference function\n");
    handcraftedConv2D((int*)input, (int*)output_ref, kernel, KERNEL_DIM, HEIGHT, WIDTH);
    printf("Reference function ended\n");
    printMatrix("Ref Core", (int *)output_ref, HEIGHT, WIDTH);
    return 0;
}
