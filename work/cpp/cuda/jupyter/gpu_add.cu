
#include <iostream>
#include <cuda_runtime.h>
#include "gpu_api.h"

__global__ void gpuAddKernel(int a, int b, int* c) {
    *c = a + b;
}

void gpuAdd(int a, int b, int* result) {
    int* d_c;
    cudaMalloc(&d_c, sizeof(int));

    gpuAddKernel<<<1,1>>>(a, b, d_c);
    cudaMemcpy(result, d_c, sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(d_c);
    std::cout << "Result from GPU: " << *result << std::endl;
}

