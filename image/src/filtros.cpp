#include "filtros.hpp"

void applyBlur(cv::Mat &image, int strength) {
  cv::GaussianBlur(image, image, cv::Size(strength, strength), 0);
}

void applyBlackAndWhite(cv::Mat &image) {
  cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
}

void applySepia(cv::Mat &image) {
  cv::Mat sepiaKernel = (cv::Mat_<float>(3, 3) << 0.272, 0.534, 0.131, 0.349,
                         0.686, 0.168, 0.393, 0.769, 0.189);
  cv::transform(image, image, sepiaKernel);
}

void applySharpen(cv::Mat &image) {
  cv::Mat sharpenKernel =
      (cv::Mat_<float>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);
  cv::filter2D(image, image, image.depth(), sharpenKernel);
}

void adjustBrightness(cv::Mat &image, double factor) {
  image.convertTo(image, -1, 1, factor);
}

void adjustContrast(cv::Mat &image, double factor) {
  image.convertTo(image, -1, factor, 0);
}

void adjustSaturation(cv::Mat &image, double factor) {
  cv::Mat hsv;
  cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

  std::vector<cv::Mat> channels;
  cv::split(hsv, channels);
  channels[1] *= factor;

  cv::merge(channels, hsv);
  cv::cvtColor(hsv, image, cv::COLOR_HSV2BGR);
}

void adjustHue(cv::Mat &image, double factor) {
  cv::Mat hsv;
  cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

  std::vector<cv::Mat> channels;
  cv::split(hsv, channels);
  channels[0] += factor;

  cv::merge(channels, hsv);
  cv::cvtColor(hsv, image, cv::COLOR_HSV2BGR);
}
