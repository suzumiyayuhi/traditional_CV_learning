#pragma once
#include"blur.h"
#include"sharpening.h"
using namespace std;
using namespace cv;

Mat NMS(Mat srcImage, Mat& dstImage, Mat thetaImage);

Mat doubleThreshold(Mat srcImage, Mat thetaImage, int lowThreshold, int highThreshold);

Mat myCanny(Mat srcImage, Mat& thetaImage, int kernelSize, int sigma, int lowThreshold, int highThreshold);
