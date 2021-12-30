#pragma once
#include"base.h"
#define DLLEXPORT extern "C" __declspec(dllexport)

DLLEXPORT void sigleImgSift(const char* s);
void siftTrackBar(int, void*);
