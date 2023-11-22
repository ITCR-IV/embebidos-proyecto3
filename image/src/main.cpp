#include <opencv2/opencv.hpp>
#include <vector>

#include "filtros.hpp"

int main() {
  cv::Mat image1 = cv::imread("../server/image.jpg");
  cv::Mat image2 = cv::imread("../server/image.jpg");

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
