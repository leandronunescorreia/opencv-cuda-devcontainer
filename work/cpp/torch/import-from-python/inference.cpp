// rm -rf build 2>/dev/null || true && cmake -S . -B build -DCMAKE_PREFIX_PATH=/work/work/thirdparty/libtorch/ -DTORCH_DISABLE_PYTHON=ON -DPython3_INCLUDE_DIR=/usr/local/conda/include/python3.9 -DPython3_LIBRARY=/usr/local/conda/lib/libpython3.9.so -DCMAKE_BUILD_TYPE=Debug && cmake --build build --config Debug -j && cp build/inference . && ./inference
#include <iostream>
#include <torch/torch.h>
#include <torch/script.h>
#include <filesystem>
#include <vector>

using namespace std;
int main() {

    torch::jit::script::Module python_model;

    try {
        python_model = torch::jit::load("/work/work/cpp/torch/import-from-python/python_model.pt");
    } catch (const c10::Error &er) {
        cout << "Error" << er.what();
    }

    auto y = torch::randn({1, 5});

    std::vector<torch::jit::IValue> samples{y};

    torch::Tensor output = python_model.forward(samples).toTensor();

    cout << "Output " << output.item() << endl;

    return 0;
}