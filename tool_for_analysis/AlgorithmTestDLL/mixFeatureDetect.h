#pragma once
#include"base.h"

#define DLLEXPORT extern "C" __declspec(dllexport)

void mixED_GoodTrackBar(int, void*);
void mixED_GoodTrackBar2(int, void*);
void mix_IE_ED_GF_TrackBar(int, void*);
void mix_IE_ED_GF_TrackBar2(int value, void* mfd);

DLLEXPORT void mixEDlines_GoodFeature(const char* s);
DLLEXPORT void mixEDlines_GoodFeature2(const char* s);
DLLEXPORT void mix_IE_ED_GF(const char* s, int flag);
DLLEXPORT void mix_IE_ED_GF2(const char* s, int flag);
