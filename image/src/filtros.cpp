#include "filtros.hpp"
#include <omp.h>

using namespace cv;
using namespace std;

void applyBlur(cv::Mat &image, int strength) {
  Timer t;
  cv::GaussianBlur(image, image, cv::Size(strength, strength), 0);
  t.elapsed("Normal Blur");
}

void applyBlurOMP(cv::Mat &image, int strength) {
  Timer t;
  for(int i = 0; i < image.rows; i++) {
    for(int j = 0; j < image.cols; j++) {
      cv::GaussianBlur(image(cv::Rect(j,i,strength,strength)), image(cv::Rect(j,i,strength,strength)), cv::Size(strength, strength), 0);
    }
  }
  t.elapsed("OpemMP Blur");
}

void applyBlackAndWhite(cv::Mat &image) {
  Timer t;
  
  for(int y = 0; y < image.rows; y++) {
    for(int x = 0; x < image.cols; x++) {
    
      Vec3b pixel = image.at<Vec3b>(y, x);
      
      uint8_t bw = (pixel[0] + pixel[1] + pixel[2]) / 3;
      
      pixel[0] = bw;
      pixel[1] = bw; 
      pixel[2] = bw;
      
      image.at<Vec3b>(y, x) = pixel; 
    }
  }

  t.elapsed("Normal BlackAndWhite");
}

void applyBlackAndWhiteOMP(cv::Mat &image) {
  Timer t;
  
  #pragma omp parallel for
  for(int y = 0; y < image.rows; y++) {
    for(int x = 0; x < image.cols; x++) {

      Vec3b pixel = image.at<Vec3b>(y, x);
            
      uint8_t bw = (pixel[0] + pixel[1] + pixel[2]) / 3;

      pixel[0] = bw;
      pixel[1] = bw;  
      pixel[2] = bw;

      image.at<Vec3b>(y, x) = pixel; 
    }
  }

  t.elapsed("OpemMP BlackAndWhite");
}

void applySepia(cv::Mat &image) {
  Timer t;
  cv::Mat sepiaKernel = (cv::Mat_<float>(3, 3) << 0.272, 0.534, 0.131, 0.349,
                         0.686, 0.168, 0.393, 0.769, 0.189);
  cv::transform(image, image, sepiaKernel);
  t.elapsed("Normal Sepia");
}

void applySepiaOMP(cv::Mat &image) {
  Timer t;
  cv::Mat sepiaKernel = (cv::Mat_<float>(3, 3) << 0.272, 0.534, 0.131, 0.349,
                         0.686, 0.168, 0.393, 0.769, 0.189);
  for(int i = 0; i < image.rows-2; i++) {
    for(int j = 0; j < image.cols-2; j++) {
      float sumB = 0, sumG = 0, sumR = 0;
      for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 3; y++) {
          sumB += sepiaKernel.at<float>(x,y) * image.at<cv::Vec3b>(i+x, j+y)[0];  
          sumG += sepiaKernel.at<float>(x,y) * image.at<cv::Vec3b>(i+x, j+y)[1];
          sumR += sepiaKernel.at<float>(x,y) * image.at<cv::Vec3b>(i+x, j+y)[2];
        }
      }
      image.at<cv::Vec3b>(i,j)[0] = sumB;
      image.at<cv::Vec3b>(i,j)[1] = sumG; 
      image.at<cv::Vec3b>(i,j)[2] = sumR;
    }
  }
  t.elapsed("OpemMP Sepia");
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
