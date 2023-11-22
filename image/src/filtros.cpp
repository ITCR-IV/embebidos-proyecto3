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
  #pragma omp parallel for collapse(2)
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
  t.elapsed("Normal Sepia");
}
void applySepiaOMP(cv::Mat &image) {
  Timer t;
  cv::Mat sepiaKernel = (cv::Mat_<float>(3, 3) << 0.272, 0.534, 0.131, 0.349,
                         0.686, 0.168, 0.393, 0.769, 0.189);
  #pragma omp parallel for collapse(2)
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
  Timer t;
  cv::Mat resultImage = image.clone();

  int height = image.rows;
  int width = image.cols;

  // Kernel de enfoque
  float sharpenKernel[3][3] = { {-1, -1, -1},
                                {-1, 9, -1},
                                {-1, -1, -1} };

  // Aplicar el filtro de enfoque a la imagen
  for (int y = 1; y < height - 1; ++y) {
    for (int x = 1; x < width - 1; ++x) {
      float sumR = 0, sumG = 0, sumB = 0;

      for (int ky = -1; ky <= 1; ++ky) {
        for (int kx = -1; kx <= 1; ++kx) {
          cv::Vec3b intensity = image.at<cv::Vec3b>(y + ky, x + kx);
          sumR += intensity[2] * sharpenKernel[ky + 1][kx + 1];
          sumG += intensity[1] * sharpenKernel[ky + 1][kx + 1];
          sumB += intensity[0] * sharpenKernel[ky + 1][kx + 1];
        }
      }

      sumR = std::min(std::max(sumR, 0.0f), 255.0f);
      sumG = std::min(std::max(sumG, 0.0f), 255.0f);
      sumB = std::min(std::max(sumB, 0.0f), 255.0f);

      resultImage.at<cv::Vec3b>(y, x)[2] = static_cast<uchar>(sumR);
      resultImage.at<cv::Vec3b>(y, x)[1] = static_cast<uchar>(sumG);
      resultImage.at<cv::Vec3b>(y, x)[0] = static_cast<uchar>(sumB);
    }
  }

  // Actualizar la imagen original con la imagen resultante del enfoque
  image = resultImage;
  t.elapsed("Normal Sharpen");
}
void applySharpenOMP(cv::Mat &image) {
  Timer t;
  cv::Mat resultImage = image.clone();

    int height = image.rows;
    int width = image.cols;

    // Kernel de enfoque
    float sharpenKernel[3][3] = { {-1, -1, -1},
                                  {-1, 9, -1},
                                  {-1, -1, -1} };

    // Aplicar el filtro de enfoque a la imagen
    #pragma omp parallel for collapse(2)
    for (int y = 1; y < height - 1; ++y) {
      for (int x = 1; x < width - 1; ++x) {
        float sumR = 0, sumG = 0, sumB = 0;

        for (int ky = -1; ky <= 1; ++ky) {
          for (int kx = -1; kx <= 1; ++kx) {
            cv::Vec3b intensity = image.at<cv::Vec3b>(y + ky, x + kx);
            sumR += intensity[2] * sharpenKernel[ky + 1][kx + 1];
            sumG += intensity[1] * sharpenKernel[ky + 1][kx + 1];
            sumB += intensity[0] * sharpenKernel[ky + 1][kx + 1];
          }
        }

        sumR = std::min(std::max(sumR, 0.0f), 255.0f);
        sumG = std::min(std::max(sumG, 0.0f), 255.0f);
        sumB = std::min(std::max(sumB, 0.0f), 255.0f);

        resultImage.at<cv::Vec3b>(y, x)[2] = static_cast<uchar>(sumR);
        resultImage.at<cv::Vec3b>(y, x)[1] = static_cast<uchar>(sumG);
        resultImage.at<cv::Vec3b>(y, x)[0] = static_cast<uchar>(sumB);
      }
    }

    // Actualizar la imagen original con la imagen resultante del enfoque
    image = resultImage;
    t.elapsed("OpenMP Sharpen");
}

void adjustBrightness(cv::Mat &image, double factor) {
  Timer t;
  int height = image.rows;
  int width = image.cols;

  // Aplicar el ajuste de brillo a cada píxel de la imagen
  for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
          cv::Vec3b intensity = image.at<cv::Vec3b>(y, x);

          for (int c = 0; c < 3; ++c) { // 3 canales (BGR)
              intensity[c] = cv::saturate_cast<uchar>(intensity[c] * factor);
          }

          image.at<cv::Vec3b>(y, x) = intensity;
      }
  }
  t.elapsed("Normal Brightness");
}
void adjustBrightnessOMP(cv::Mat &image, double factor) {
  Timer t;
  int height = image.rows;
  int width = image.cols;

  // Aplicar el ajuste de brillo a cada píxel de la imagen
  #pragma omp parallel for collapse(2)
  for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
          cv::Vec3b intensity = image.at<cv::Vec3b>(y, x);

          for (int c = 0; c < 3; ++c) { // 3 canales (BGR)
              intensity[c] = cv::saturate_cast<uchar>(intensity[c] * factor);
          }

          image.at<cv::Vec3b>(y, x) = intensity;
      }
  }
  t.elapsed("OpenMP Brightness");
}


void adjustContrast(cv::Mat &image, double factor) {
  Timer t;
  int height = image.rows;
  int width = image.cols;

  // Ajustar el contraste manualmente
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      for (int c = 0; c < 3; ++c) { // 3 canales (BGR)
        double pixel = image.at<cv::Vec3b>(y, x)[c];
        pixel = ((pixel - 127.0) * factor) + 127.0;
        image.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(pixel);
      }
    }
  }
  t.elapsed("Normal Contrast");
}
void adjustContrastOMP(cv::Mat &image, double factor) {
  Timer t;
  int height = image.rows;
  int width = image.cols;

  // Ajustar el contraste manualmente
  #pragma omp parallel for collapse(2)
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      for (int c = 0; c < 3; ++c) { // 3 canales (BGR)
        double pixel = image.at<cv::Vec3b>(y, x)[c];
        pixel = ((pixel - 127.0) * factor) + 127.0;
        image.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(pixel);
      }
    }
  }
  t.elapsed("OpenMP Contrast");
}


void adjustSaturation(cv::Mat &image, double factor) {
  Timer t;
  int height = image.rows;
  int width = image.cols;

  // Convertir la imagen a HSV manualmente
  cv::Mat hsv;
  cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

  // Ajustar la saturación manualmente
  for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
          cv::Vec3b &pixel = hsv.at<cv::Vec3b>(y, x);

          // Modificar el canal de saturación
          pixel[1] = cv::saturate_cast<uchar>(pixel[1] * factor);
      }
  }

  // Convertir la imagen de vuelta a BGR
  cv::cvtColor(hsv, image, cv::COLOR_HSV2BGR);
  t.elapsed("Normal Saturation");
}
void adjustSaturationOMP(cv::Mat &image, double factor) {
  Timer t;
  int height = image.rows;
  int width = image.cols;

  // Convertir la imagen a HSV manualmente
  cv::Mat hsv;
  cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

  // Ajustar la saturación manualmente
  #pragma omp parallel for collapse(2)
  for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
          cv::Vec3b &pixel = hsv.at<cv::Vec3b>(y, x);

          // Modificar el canal de saturación
          pixel[1] = cv::saturate_cast<uchar>(pixel[1] * factor);
      }
  }

  // Convertir la imagen de vuelta a BGR
  cv::cvtColor(hsv, image, cv::COLOR_HSV2BGR);
  t.elapsed("Normal Saturation");
}

void adjustHue(cv::Mat &image, double factor) {
  Timer t;
  int height = image.rows;
  int width = image.cols;

  // Convertir la imagen a HSV manualmente
  cv::Mat hsv;
  cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

  // Ajustar el tono manualmente
  for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
          cv::Vec3b &pixel = hsv.at<cv::Vec3b>(y, x);

          // Modificar el canal de tono
          pixel[0] = static_cast<uchar>(pixel[0] + factor);

          // Asegurar que el valor del tono esté en el rango correcto (0 - 179 en espacio HSV)
          if (pixel[0] > 179) {
              pixel[0] -= 180;
          }
      }
  }

  // Convertir la imagen de vuelta a BGR
  cv::cvtColor(hsv, image, cv::COLOR_HSV2BGR);
  t.elapsed("Normal Hue");
}
void adjustHueOMP(cv::Mat &image, double factor) {
  Timer t;
  int height = image.rows;
  int width = image.cols;

  // Convertir la imagen a HSV manualmente
  cv::Mat hsv;
  cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

  // Ajustar el tono manualmente
  #pragma omp parallel for collapse(2)
  for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
          cv::Vec3b &pixel = hsv.at<cv::Vec3b>(y, x);

          // Modificar el canal de tono
          pixel[0] = static_cast<uchar>(pixel[0] + factor);

          // Asegurar que el valor del tono esté en el rango correcto (0 - 179 en espacio HSV)
          if (pixel[0] > 179) {
              pixel[0] -= 180;
          }
      }
  }

  // Convertir la imagen de vuelta a BGR
  cv::cvtColor(hsv, image, cv::COLOR_HSV2BGR);
  t.elapsed("Normal Hue");
}
