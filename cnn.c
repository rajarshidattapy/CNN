#include <stdio.h>
#include <stdlib.h>

#define IMG_SIZE 5
#define FILTER_SIZE 3
#define POOL_SIZE 2

// Sample image (5x5 grayscale)
float image[IMG_SIZE][IMG_SIZE] = {
    {1, 1, 2, 4, 5},
    {5, 6, 7, 8, 9},
    {9, 8, 7, 6, 5},
    {4, 3, 2, 1, 0},
    {1, 2, 3, 4, 5}
};

// Example filter (3x3)
float filter[FILTER_SIZE][FILTER_SIZE] = {
    {1, 0, -1},
    {1, 0, -1},
    {1, 0, -1}
};

// Apply ReLU activation
float relu(float x) {
    return x > 0 ? x : 0;
}

// Convolution operation
void conv2D(float input[IMG_SIZE][IMG_SIZE], float output[IMG_SIZE - FILTER_SIZE + 1][IMG_SIZE - FILTER_SIZE + 1]) {
    for (int i = 0; i <= IMG_SIZE - FILTER_SIZE; i++) {
        for (int j = 0; j <= IMG_SIZE - FILTER_SIZE; j++) {
            float sum = 0.0;
            for (int ki = 0; ki < FILTER_SIZE; ki++) {
                for (int kj = 0; kj < FILTER_SIZE; kj++) {
                    sum += input[i + ki][j + kj] * filter[ki][kj];
                }
            }
            output[i][j] = relu(sum); // Apply ReLU
        }
    }
}

// Max Pooling (2x2)
void maxPool(float input[3][3], float output[1][1]) {
    float max = input[0][0];
    for (int i = 0; i < POOL_SIZE; i++) {
        for (int j = 0; j < POOL_SIZE; j++) {
            if (input[i][j] > max)
                max = input[i][j];
        }
    }
    output[0][0] = max;
}

int main() {
    float conv_output[IMG_SIZE - FILTER_SIZE + 1][IMG_SIZE - FILTER_SIZE + 1];
    conv2D(image, conv_output);

    printf("Convolution + ReLU Output:\n");
    for (int i = 0; i < IMG_SIZE - FILTER_SIZE + 1; i++) {
        for (int j = 0; j < IMG_SIZE - FILTER_SIZE + 1; j++) {
            printf("%.2f ", conv_output[i][j]);
        }
        printf("\n");
    }

    float pool_output[1][1];
    maxPool(conv_output, pool_output);

    printf("\nMax Pooling Output (2x2):\n");
    printf("%.2f\n", pool_output[0][0]);

    return 0;
}
