//rm -rf build 2>/dev/null || true && cmake -S . -B build -DCMAKE_PREFIX_PATH=/work/work/thirdparty/libtorch/ -DTORCH_DISABLE_PYTHON=ON -DPython3_INCLUDE_DIR=/usr/local/conda/include/python3.9 -DPython3_LIBRARY=/usr/local/conda/lib/libpython3.9.so -DCMAKE_BUILD_TYPE=Debug && cmake --build build --config Debug -j && cp build/simple_blob . && ./simple_blob

#include <torch/torch.h>
#include <torch/script.h>
#include <iostream>
#include <dirent.h>
#include <opencv2/opencv.hpp>

torch::Tensor read_images(std::string location) {
	cv::Mat img = cv::imread(location, 1);
	cv::resize(img, img, cv::Size(224, 224), cv::INTER_CUBIC);
	torch::Tensor img_tensor = torch::from_blob(img.data, {img.rows, img.cols, 3}, torch::kByte);
	img_tensor = img_tensor.permute({2, 0, 1});
	return img_tensor.clone();
}


int main() {
  std::cout << "is cuda available: " << torch::cuda::is_available() << "\n";
  std::cout << "device count: " << torch::cuda::device_count() << "\n";

  torch::Tensor img_tensor = read_images("/work/work/cpp/torch/read-images/dogecoin_900x510.jpg");

  std::cout << "img_tensor shape: " << img_tensor.sizes() << "\n";
  
  return 0;
}