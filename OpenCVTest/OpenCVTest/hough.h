#pragma once
#include"canny.h"
Mat myHough(Mat srcImage, Mat& thetaImage, int kernelSize, int sigma, 
	int lowCannyThreshold, int highCannyThreshold, int houghThreshold, int flag);