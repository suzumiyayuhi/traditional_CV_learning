#pragma once
#include"base.h"
#define DLLEXPORT extern "C" __declspec(dllexport)

void houghLinePTrackBar(int, void*);

DLLEXPORT void houghLinePDetect(const char* s);
DLLEXPORT void edgeLineDetect(const char* s);
