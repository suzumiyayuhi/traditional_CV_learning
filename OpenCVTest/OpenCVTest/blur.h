#pragma once
#include<opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;


float** CreateGaussKernel(int kernelSize, float sigma);
float** CreateGaussDerivativeKernel(int kernelSuze, float sigma);
Mat MyGaussBlur(Mat srcImage, int kernelSize, float sigma);
Mat MyGaussDerivativeBlur(Mat srcImage, int kernelSize, float sigma);
Mat LaplaceFliter(Mat srcImage);
Mat LOGFliter(Mat srcImage, int kernelSize);
Mat DOGFliter(Mat srcImage, int kernelSize, float sigma1, float sigma2);

