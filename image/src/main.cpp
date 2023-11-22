#include <opencv2/opencv.hpp>
#include <vector>

#include "filtros.hpp"

int main() {
  cv::Mat image = cv::imread("../server/image.jpg");

  // Aplicar los filtros deseados
  applyBlur(image, 5);
  applyBlurOMP(image, 5);
  applyBlackAndWhite(image);
  applyBlackAndWhiteOMP(image);
  applySepia(image);
  applySepiaOMP(image);
  // applySharpen(image);
  // adjustBrightness(image, 50);
  // adjustContrast(image, 1.5);
  // adjustSaturation(image, 1.5);
  // adjustHue(image, 10);

  return 0;
}
