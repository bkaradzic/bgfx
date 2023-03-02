#ifndef __CUDA_NOISE_KERNEL_H
#define __CUDA_NOISE_KERNEL_H

#include <curand.h>
#include <curand_kernel.h>

extern "C" __global__ void calculateNoise(uint32_t width, uint32_t height, int seed, cudaSurfaceObject_t image)
{
  uint32_t x = blockIdx.x * blockDim.x + threadIdx.x;
  uint32_t y = blockIdx.y * blockDim.y + threadIdx.y;

  if (x >= width || y >= height)
  {
    return;
  }

  int id = y * width + x;
  curandState rngState;
  curand_init(seed, id, 0, &rngState);

  uchar4 rgba;
  rgba.x = uint8_t(((curand_normal(&rngState) + 1.0) * 0.5) * 255);
  rgba.y = uint8_t(((curand_normal(&rngState) + 1.0) * 0.5) * 255);
  rgba.z = uint8_t(((curand_normal(&rngState) + 1.0) * 0.5) * 255);
  rgba.w = uint8_t(((curand_normal(&rngState) + 1.0) * 0.5) * 255);

  surf2Dwrite(rgba, image, x * sizeof(uchar4), y);
}

#endif