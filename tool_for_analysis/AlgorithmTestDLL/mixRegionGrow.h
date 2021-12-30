#pragma once
#include"base.h"

#define DLLEXPORT extern "C" __declspec(dllexport)

void on_MouseHandle(int event, int x, int y, int flags, void* param);
void RegionGrow(Mat src, Mat& matDst, Point2i pt, int th);
void RegionGrowEx(Mat src, Mat& matDst, Point2i pt, int th);//改进版区域增长

//图像增强后做区域生长分割
void mix_IE_ED_GF_RG_TrackBar1(int value, void* mrg);
DLLEXPORT void mix_IE_ED_GF_RG(const char* s, int flag);
//——————————————————————————————————————


//图像增强后通过角点、线特征来做区域生长
void mix_IE_ED_GF_RG_TrackBar2(int value, void* mrg);
DLLEXPORT void mix_IE_ED_GF_RG2(int value, void* mrg);
//________________________________________

//改进版区域增长适配系列
DLLEXPORT void mix_IE_ED_GF_RG_EX(const char* s, int flag);
void mix_IE_ED_GF_RG_EX_TrackBar(int value, void* mrg);
void on_MouseHandle2(int event, int x, int y, int flags, void* param);
