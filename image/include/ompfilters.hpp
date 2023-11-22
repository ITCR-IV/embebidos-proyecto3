#ifndef FILTROS_H
#define FILTROS_H

#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include <iostream>
#include <string>

class Timer {
public:
  timeval tinicio, tfin;

  Timer() {
     gettimeofday(&tinicio, NULL);
  }

  void elapsed(std::string text) {
    gettimeofday(&tfin, NULL);
    double segs = (tfin.tv_sec - tinicio.tv_sec) + (tfin.tv_usec - tinicio.tv_usec) / 1000000.0;
    std::cout << text << " - Tiempo: " << segs << " segs\n" << std::endl;
  }
};


void applyBlur(cv::Mat &image, int strength);
void applyBlurOMP(cv::Mat &image, int strength);

void applyBlackAndWhite(cv::Mat &image);
void applyBlackAndWhiteOMP(cv::Mat &image);

void applySepia(cv::Mat &image);
void applySepiaOMP(cv::Mat &image);

void applySharpen(cv::Mat &image);
void applySharpenOMP(cv::Mat &image);

void adjustBrightness(cv::Mat &image, double factor);
void adjustBrightnessOMP(cv::Mat &image, double factor);

void adjustContrast(cv::Mat &image, double factor);
void adjustContrastOMP(cv::Mat &image, double factor);

void adjustSaturation(cv::Mat &image, double factor);
void adjustSaturationOMP(cv::Mat &image, double factor);

void adjustHue(cv::Mat &image, double factor);
void adjustHueOMP(cv::Mat &image, double factor);

#endif
