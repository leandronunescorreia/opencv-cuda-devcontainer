//rm -rf build 2>/dev/null || true && cmake -S . -B build -DCMAKE_PREFIX_PATH=/work/work/thirdparty/libtorch/ -DTORCH_DISABLE_PYTHON=ON -DPython3_INCLUDE_DIR=/usr/local/conda/include/python3.9 -DPython3_LIBRARY=/usr/local/conda/lib/libpython3.9.so -DCMAKE_BUILD_TYPE=Debug && cmake --build build --config Debug -j && cp build/simple_linear . && ./simple_linear

#include <torch/torch.h>
#include <iostream>

int main() {
  std::cout << "is cuda available: " << torch::cuda::is_available() << "\n";
  std::cout << "device count: " << torch::cuda::device_count() << "\n";

  int EPOCHS = 100;

  torch::Tensor x = torch::randn({10,3}, torch::requires_grad());
  torch::Tensor y = torch::randn({10,1}, torch::requires_grad());

  torch::nn::Linear linear(3,1);
  torch::nn::MSELoss criterion;

  torch::optim::Adam optimizer(linear->parameters(), torch::optim::AdamOptions(0.001));

  for (int epoch = 0; epoch < EPOCHS; ++epoch) {
    optimizer.zero_grad();
    torch::Tensor pred = linear->forward(x);
    torch::Tensor loss = criterion(pred, y);
    loss.backward();
    optimizer.step();

    if (epoch % 10 == 0) {
      std::cout << "Epoch [" << epoch << "/100], Loss: " << loss.item<float>() << std::endl;
    }
  }
}