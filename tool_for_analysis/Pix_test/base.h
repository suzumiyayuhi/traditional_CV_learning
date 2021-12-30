#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include<stack>
#include<Windows.h>
#include<map>
#include<fstream>
#include<sstream>
using namespace std;
using namespace cv;

void PaperTest(char* src);
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void mix_IE_ED_GF_RG_TrackBar1(int value, void* mrg);
void ClickRegionGrowDrawRec(const char* src);
Mat RegionGrowDrawRec(Mat src, Point2i pt, Mat flagMat);
Mat RegionGrowChangePatchCrackLabel(Mat src, Point2i pt, Mat& flagMat);
Rect GetRegionGrowRec(Mat src, Point2i pt, Mat& flagMat);
vector<string> getDirFile(string path);
char* getCstrFromVec(const char* dirPath);
