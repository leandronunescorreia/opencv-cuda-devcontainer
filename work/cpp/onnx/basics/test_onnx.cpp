// g++ test_onnx.cpp -o test_onnx -I/work/work/thirdparty/onnxruntime/include -L/work/work/thirdparty/onnxruntime/lib -lonnxruntime
// export LD_LIBRARY_PATH=/work/work/thirdparty/onnxruntime/lib:$LD_LIBRARY_PATH

#include </work/work/thirdparty/onnxruntime/include/onnxruntime_cxx_api.h>
#include <iostream>

int main() {
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "test");
    Ort::SessionOptions session_options;

    session_options.SetIntraOpNumThreads(1);

    const char* model_path = "/work/work/cpp/onnx/basics/logreg.onnx";

    Ort::Session session(env, model_path, session_options);

    std::cout << "ONNX model loaded successfully!" << std::endl;
    return 0;
}

// Run these in bash:
// export CPLUS_INCLUDE_PATH=/work/work/thirdparty/onnxruntime/include/:$CPLUS_INCLUDE_PATH
// export LIBRARY_PATH=/work/work/thirdparty/onnxruntime/lib:$LIBRARY_PATH
// export LD_LIBRARY_PATH=/work/work/thirdparty/onnxruntime/lib:$LD_LIBRARY_PATH