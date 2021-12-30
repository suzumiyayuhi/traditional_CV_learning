#pragma once
#include"base.h"

#define DLLEXPORT extern "C" __declspec(dllexport)


void Trackbar(int, void*);	//harris拖动条
void Trackbar1(int, void*);	//GoodFeatureToTrack拖动条

DLLEXPORT void opencvHarris(const char* s);
DLLEXPORT void opencvGoodFeatureToTrack(const char* s);
