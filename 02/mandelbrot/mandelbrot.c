#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000

void calc_mandelbrot(uint8_t image[Y][X]) {
  #pragma omp parallel
  for (int y_pixel = 0; y_pixel < Y; y_pixel++) {
    double cy = ((double)y_pixel / Y) * 2.0 - 1.0; // map y_pixel to Mandelbrot y-axis [-1, 1]
    for (int x_pixel = 0; x_pixel < X; x_pixel++) {
      double x = 0.0;
      double y = 0.0;
      double cx = ((double)x_pixel / X) * 3.5 - 2.5; // map x_pixel to Mandelbrot x-axis [-2.5, 1]
      int iteration = 0;
      while (x*x + y*y <= 2*2 && iteration < MAX_ITER) {
        double x_tmp = x*x - y*y + cx;
        y = 2*x*y + cy;
        x = x_tmp;
        iteration++;
      }
      int norm_iteration = (int)((double)iteration / MAX_ITER * 255); // map iteration to pixel range [0, 255]
      image[y_pixel][x_pixel] = (uint8_t)norm_iteration;
    }
  }
}

int main() {
  uint8_t image[Y][X];
  
  double startTime = omp_get_wtime();
  
  calc_mandelbrot(image);
  
  double endTime = omp_get_wtime();
  
  printf("time: %2.4f seconds\n", endTime-startTime);
  
  
  const int channel_nr = 1, stride_bytes = 0;
  stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);
  return EXIT_SUCCESS;
}