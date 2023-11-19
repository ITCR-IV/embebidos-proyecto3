#ifndef FILTROS_H
#define FILTROS_H

#include <opencv2/opencv.hpp>

void applyBlur(cv::Mat &image, int strength);

void applyBlackAndWhite(cv::Mat &image);

void applySepia(cv::Mat &image);

void applySharpen(cv::Mat &image);

void adjustBrightness(cv::Mat &image, double factor);

void adjustContrast(cv::Mat &image, double factor);

void adjustSaturation(cv::Mat &image, double factor);

void adjustHue(cv::Mat &image, double factor);

#endif
