#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include"blur.h"
#include"sharpening.h"
#include"resize.h"

using namespace cv;
using namespace std;

void mySift(Mat srcImage, Mat& resultImage, int featureLevel);
