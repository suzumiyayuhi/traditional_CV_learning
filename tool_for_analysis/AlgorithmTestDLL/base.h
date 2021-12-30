#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<vector>
#include<stack>
#include<string.h>
#include<cstring>
#include<io.h>
#include"coner_detect.h"
#include"sift.h"
#include"line_detect.h"
#include"EDLines.h"
#include"mixFeatureDetect.h"
#include"image_enhance.h"
#include"mixRegionGrow.h"
#define DLLEXPORT extern "C" __declspec(dllexport)

using namespace std;
using namespace cv;

const string BASE_DIR = "../../images\\";

const string BASE_DIR_01 = BASE_DIR + "01\\";

const string BASE_DIR_02 = BASE_DIR + "02\\";
const string BASE_DIR_02_SBC = BASE_DIR_02 + "sorted_by_classes\\";
const string DIR_02_SRC_CORNERFRACTURE = BASE_DIR_02_SBC + "cornerfracture\\";
const string DIR_02_SRC_CRACK = BASE_DIR_02_SBC + "crack\\";
const string DIR_02_SRC_HOLE = BASE_DIR_02_SBC + "hole\\";
const string DIR_02_SRC_PATCH = BASE_DIR_02_SBC + "patch\\";
const string DIR_02_SRC_REPAIR = BASE_DIR_02_SBC + "repair\\";
const string DIR_02_SRC_SEAMBROKEN = BASE_DIR_02_SBC + "seambroken\\";
const string DIR_02_SRC_SLAB = BASE_DIR_02_SBC + "slab\\";
const string DIR_02_SRC_TRACK = BASE_DIR_02_SBC + "track\\";
const string DIR_02_SRC_VM = BASE_DIR_02 + "visualized_mask\\";

const string BASE_DIR_04 = BASE_DIR + "04\\";
const string DIR_04_SRC_TRAIN = BASE_DIR_04 + "train\\";
const string DIR_04_SRC_VAL = BASE_DIR_04 + "val_fixed\\";
const string DIR_04_SRC_TRAIN_LABEL = BASE_DIR_04 + "label_grey\\train\\";
const string DIR_04_SRC_VAL_LABEL = BASE_DIR_04 + "label_grey\\val\\";

const string BASE_DIR_05 = BASE_DIR + "05\\";
const string DIR_05_SRC_JOINT = BASE_DIR_05 + "joint\\";						//板缝
const string DIR_05_SRC_MARKING = BASE_DIR_05 + "marking\\";					//标线
const string DIR_05_SRC_SCRATCH = BASE_DIR_05 + "scratch\\";					//划痕
const string DIR_05_SRC_STAIN = BASE_DIR_05 + "stain\\";						//油渍
const string BASE_DIR_05_SORT_BY_FEATURE = BASE_DIR_05 + "SBF\\";				//根据视觉特征细分
const string DIR_05_SRC_SBF_JOINT = BASE_DIR_05_SORT_BY_FEATURE + "joint\\";	//板缝
const string DIR_05_SRC_SBF_MARKING = BASE_DIR_05_SORT_BY_FEATURE + "marking\\";	//标线
const string DIR_05_SRC_SBF_LONG_BAR = BASE_DIR_05_SORT_BY_FEATURE + "long_bar\\"; //大长条(油渍_划痕)
const string DIR_05_SRC_SBF_GROUND_LIGHT = BASE_DIR_05_SORT_BY_FEATURE + "ground_light\\"; //地灯边缘
const string DIR_05_SRC_SBF_SCRATCH = BASE_DIR_05_SORT_BY_FEATURE + "scratch\\";	//划痕
const string DIR_05_SRC_SBF_TAD_POLE = BASE_DIR_05_SORT_BY_FEATURE + "tadpole\\";//蝌蚪状油渍

void Trackbar3(int, void*);//灰度值调整用拖条
void TrackBar4(int, void*);
DLLEXPORT void showGray(const char* imgPath);//查看对应灰度值像素点
DLLEXPORT void testHelloWorld();
DLLEXPORT char* testArg(const char* s);
DLLEXPORT vector<string> getDirFile(string path);
DLLEXPORT char* getCstrFromVec(const char* dirPath);
DLLEXPORT void changeImageGray(const char* imgPath);
