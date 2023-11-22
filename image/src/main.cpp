#include <opencv2/opencv.hpp>
#include <ostream>
#include <vector>

#include "ompfilters.hpp"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <image_path>" << std::endl;
    return -1;
  }

  std::string imagePath = argv[1];

  cv::Mat image1 = cv::imread(imagePath);
  cv::Mat image2 = cv::imread(imagePath);

  if (image1.empty() || image2.empty()) {
    std::cerr << "Error: Could not open or read the image." << std::endl;
    return -1;
  }

  // Aplicar los filtros deseados
  applyBlur(image1, 5);
  applyBlurOMP(image2, 5);

  applyBlackAndWhite(image1);
  applyBlackAndWhiteOMP(image2);

  applySepia(image1);
  applySepiaOMP(image2);

  applySharpen(image1);
  applySharpenOMP(image2);

  adjustBrightness(image1, 50);
  adjustBrightnessOMP(image2, 50);

  adjustContrast(image1, 1.5);
  adjustContrastOMP(image2, 1.5);

  adjustSaturation(image1, 1.5);
  adjustSaturationOMP(image2, 1.5);

  adjustHue(image1, 10);
  adjustHueOMP(image2, 10);

  return 0;
}
