#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

void Prewitt(Mat originImage, Mat& dstImage, Mat& thetaImage);
void PreWittOpenCV(Mat  srcImage, Mat& dstImage);
void Sobel(Mat originImage, Mat& dstImage, Mat& thetaImage);
Mat getPartial(Mat srcImage, int flag);
/** @brief flag == 0 X, flag == 1 Y, else X + Y

*/