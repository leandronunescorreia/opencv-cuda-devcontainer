// export LD_LIBRARY_PATH=/work/work/thirdparty/onnxruntime/lib:$LD_LIBRARY_PATH && g++ provider.cpp -o provider -I/work/work/thirdparty/onnxruntime/include -L/work/work/thirdparty/onnxruntime/lib -lonnxruntime

#include </work/work/thirdparty/onnxruntime/include/onnxruntime_cxx_api.h>
#include <iostream>

int main(){
  //check providers
  auto providers = Ort::GetAvailableProviders();
  for (auto provider : providers) {
    std::cout << provider << std::endl;
  }
  return 0;
}