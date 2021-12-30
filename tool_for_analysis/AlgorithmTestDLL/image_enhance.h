#pragma once
#include<opencv2/opencv.hpp>

#define DLLEXPORT extern "C" __declspec(dllexport)

using namespace std;
using namespace cv;
/*图像增强方法
* 0，直方图均衡化
* 1，拉普拉斯算子局部增强
* 2，log函数映射（非线性映射）
* 3，伽马变换
* 4，线性对比度展宽
* 5，自适应阈值，图像二值化
* 6，自适应阈值，截断式
*/

Mat NoArgimageEnhance(Mat m, int mode);
Mat GammaMapping(Mat m, int gamma, int c);
Mat LinearWide(Mat m, int fa, int fb, int ga, int gb);
Mat MyAdaptiveThreshold_Binary(Mat m, int blockSize, int mode, int c);
Mat MyAdaptiveThreshold_ThCut(Mat m, int blockSize, int mode, int c);

DLLEXPORT void EnhanceImageOutput(int dataSet, int flag);
