// g++ inference.cpp -o inference -I/work/work/thirdparty/onnxruntime/include -L/work/work/thirdparty/onnxruntime/lib -lonnxruntime

#include </work/work/thirdparty/onnxruntime/include/onnxruntime_cxx_api.h>
#include <iostream>
#include <vector>

int main() {
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "test");
    Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(1);

    const char* model_path = "/work/work/cpp/onnx/basics/logreg.onnx";
    Ort::Session session(env, model_path, session_options);

    std::cout << "Model loaded successfully!" << std::endl;

    // -----------------------------
    // 1. Define input data
    // -----------------------------
    std::vector<float> input_data = {
        0.5f, -1.2f, 3.3f, 0.8f, 2.0f
    };

    std::vector<int64_t> input_shape = {1, 5};

    // -----------------------------
    // 2. Create memory info
    // -----------------------------
    Ort::MemoryInfo memory_info =
        Ort::MemoryInfo::CreateCpu(
            OrtArenaAllocator,
            OrtMemTypeDefault
        );

    // -----------------------------
    // 3. Create input tensor
    // -----------------------------
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
        memory_info,
        input_data.data(),
        input_data.size(),
        input_shape.data(),
        input_shape.size()
    );

    // -----------------------------
    // 4. Define input/output names
    // -----------------------------
    const char* input_names[] = {"input"};
    const char* output_names[] = {"output"};

    // -----------------------------
    // 5. Run inference
    // -----------------------------
    auto output_tensors = session.Run(
        Ort::RunOptions{nullptr},
        input_names,
        &input_tensor,
        1,
        output_names,
        1
    );

    // -----------------------------
    // 6. Read output
    // -----------------------------
    float* output = output_tensors[0].GetTensorMutableData<float>();

    std::cout << "Prediction: " << output[0] << std::endl;

    return 0;
}