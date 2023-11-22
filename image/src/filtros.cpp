#include "filtros.hpp"
#include <omp.h>

using namespace cv;
using namespace std;

void applyBlur(cv::Mat &image, int kernelSize) {
  Timer t;
  
  cv::Mat resultImage = image.clone(); 
 
    int height = image.rows; 
    int width = image.cols; 
 
    for (int y = 0; y < height; ++y) { 
        for (int x = 0; x < width; ++x) { 
            int totalR = 0, totalG = 0, totalB = 0, count = 0; 
 
            for (int ky = -kernelSize; ky <= kernelSize; ++ky) { 
                for (int kx = -kernelSize; kx <= kernelSize; ++kx) { 
                    int newX = x + kx; 
                    int newY = y + ky; 
 
                    if (newX >= 0 && newX < width && newY >= 0 && newY < height) { 
                        cv::Vec3b intensity = image.at<cv::Vec3b>(newY, newX); 
                        totalR += intensity[2]; // Componente R 
                        totalG += intensity[1]; // Componente G 
                        totalB += intensity[0]; // Componente B 
                        count++; 
                    } 
                } 
            } 
 
            // Calcular los valores medios de los componentes R, G y B 
            resultImage.at<cv::Vec3b>(y, x)[2] = totalR / count; 
            resultImage.at<cv::Vec3b>(y, x)[1] = totalG / count; 
            resultImage.at<cv::Vec3b>(y, x)[0] = totalB / count; 
        } 
    } 
 
    // Actualizar la imagen original con la imagen resultante después del desenfoque 
    image = resultImage; 

  t.elapsed("Normal Blur");
}

void applyBlurOMP(cv::Mat &image, int kernelSize) {
  Timer t;
  
  cv::Mat resultImage = image.clone(); 
 
    int height = image.rows; 
    int width = image.cols; 
 
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < height; ++y) { 
        for (int x = 0; x < width; ++x) { 
            int totalR = 0, totalG = 0, totalB = 0, count = 0; 
 
            for (int ky = -kernelSize; ky <= kernelSize; ++ky) { 
                for (int kx = -kernelSize; kx <= kernelSize; ++kx) { 
                    int newX = x + kx; 
                    int newY = y + ky; 
 
                    if (newX >= 0 && newX < width && newY >= 0 && newY < height) { 
                        cv::Vec3b intensity = image.at<cv::Vec3b>(newY, newX); 
                        totalR += intensity[2]; // Componente R 
                        totalG += intensity[1]; // Componente G 
                        totalB += intensity[0]; // Componente B 
                        count++; 
                    } 
                } 
            } 
 
            // Calcular los valores medios de los componentes R, G y B 
            resultImage.at<cv::Vec3b>(y, x)[2] = totalR / count; 
            resultImage.at<cv::Vec3b>(y, x)[1] = totalG / count; 
            resultImage.at<cv::Vec3b>(y, x)[0] = totalB / count; 
        } 
    } 
 
    // Actualizar la imagen original con la imagen resultante después del desenfoque 
    image = resultImage; 

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
  int x, y;
  #pragma omp parallel for private(y, x)
  for(y = 0; y < image.rows; y++) {
    for(x = 0; x < image.cols; x++) {

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
  #pragma omp parallel for
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
