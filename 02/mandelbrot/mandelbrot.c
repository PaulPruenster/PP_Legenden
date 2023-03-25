#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000

void calc_mandelbrot(uint8_t image[Y][X]) {
	// TODO: Write your code here!
        for (int i=0; i<Y; i++) {
                for (int j=0; j<X; j++) {
                        float x = 0.0;
                        float y = 0.0;

                        float cx = 0.0; // dont know what they do now
                        float cy = 0.0;

                        int iteration = 0;
                        while (x*x + y*y <= 2*2 && iteration < MAX_ITER) {
                                float x_tmp = x*x - y*y + cx;
                                y = 2*x*y + cy;
                                x = x_tmp;
                                iteration++;
                        }

                        image[i][j] = iteration % 256;
                }
        }
}

int main() {
	uint8_t image[Y][X];

	calc_mandelbrot(image);

	const int channel_nr = 1, stride_bytes = 0;
	stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);
	return EXIT_SUCCESS;
}