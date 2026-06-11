//rm -rf build 2>/dev/null || true && cmake -S . -B build -DCMAKE_PREFIX_PATH=/work/work/thirdparty/libtorch/ -DTORCH_DISABLE_PYTHON=ON -DPython3_INCLUDE_DIR=/usr/local/conda/include/python3.9 -DPython3_LIBRARY=/usr/local/conda/lib/libpython3.9.so -DCMAKE_BUILD_TYPE=Debug && cmake --build build --config Debug -j && cp build/check . && ./check

#include <torch/torch.h>
#include <iostream>

int main() {
    std::cout << "is cuda available: " << torch::cuda::is_available() << "\n";
    std::cout << "device count: " << torch::cuda::device_count() << "\n";

  torch::Tensor tensor = torch::randn({3,3});
  std::cout << "The random matrix is:" << std::endl << tensor << std::endl;

  //Initialize the device to CPU
  torch::DeviceType device = torch::kCPU;
  //If CUDA is available,run on GPU
  if (torch::cuda::is_available())
      device = torch::kCUDA;
  std::cout << "Running on: " << (device == torch::kCUDA ? "GPU" : "CPU") << std::endl;

}