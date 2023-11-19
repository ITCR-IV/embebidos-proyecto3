#include <opencv2/opencv.hpp>
#include <vector>

#include "filtros.hpp"

int main() {
  cv::Mat image = cv::imread("../server/image.jpg");

  // Aplicar los filtros deseados
  // applyBlur(image, 5);
  applyBlackAndWhite(image);
  // applySepia(image);
  // applySharpen(image);
  // adjustBrightness(image, 50);
  // adjustContrast(image, 1.5);
  // adjustSaturation(image, 1.5);
  // adjustHue(image, 10);

  // Guardar la imagen modificada
  cv::imwrite("output.jpg", image);

  return 0;
}
