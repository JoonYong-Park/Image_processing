//#include <math.h>
//#include <stdlib.h>
//
//#define PI 3.14159265358979323846
//#define SIGMA 1.0
//#define MASK_SIZE 5
//
//double gaussian(int x, int y, double sigma) {
//    return (1.0 / (2.0 * PI * sigma * sigma)) * exp(-(x * x + y * y) / (2.0 * sigma * sigma));
//}
//
//void gaussian_smoothing(unsigned char** image, int width, int height) {
//    // Create Gaussian mask
//    double mask[MASK_SIZE][MASK_SIZE];
//    for (int i = 0; i < MASK_SIZE; i++) {
//        for (int j = 0; j < MASK_SIZE; j++) {
//            mask[i][j] = gaussian(i - MASK_SIZE / 2, j - MASK_SIZE / 2, SIGMA);
//        }
//    }
//
//    // Apply Gaussian mask to the image
//    unsigned char** smoothed_image = (unsigned char**)malloc(sizeof(unsigned char*) * height);
//    for (int i = 0; i < height; i++) {
//        smoothed_image[i] = (unsigned char*)malloc(sizeof(unsigned char) * width);
//        for (int j = 0; j < width; j++) {
//            double sum = 0.0;
//            for (int k = 0; k < MASK_SIZE; k++) {
//                for (int l = 0; l < MASK_SIZE; l++) {
//                    int x = j + l - MASK_SIZE / 2;
//                    int y = i + k - MASK_SIZE / 2;
//                    if (x >= 0 && x < width && y >= 0 && y < height) {
//                        sum += image[y][x] * mask[k][l];
//                    }
//                }
//            }
//            smoothed_image[i][j] = (unsigned char)sum;
//        }
//    }
//
//    // Replace original image with smoothed image
//    for (int i = 0; i < height; i++) {
//        for (int j = 0; j < width; j++) {
//            image[i][j] = smoothed_image[i][j];
//        }
//        free(smoothed_image[i]);
//    }
//    free(smoothed_image);
//}
