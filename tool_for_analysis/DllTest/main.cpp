#include<iostream>
#include<Windows.h>
#include<base.h>
//#include"EDLines.h"
using namespace std;

#define WAIT_TIME 1

#pragma comment(lib,"AlgorithmTestDLL.lib")

void testDLL()
{
	HMODULE hMod = LoadLibrary(L"AlgorithmTestDLL.dll");
	//testHelloWorld();
	//getDirFile("images\\");
	//cout << getCstrFromVec(DIR_04_SRC_VAL.c_str()) << endl;
	/*
	char* s = getCstrFromVec(DIR_05_SRC_SBF_SCRATCH.c_str());
	opencvHarris(s);
	*/




	FreeLibrary(hMod);
}

void conerDetectTest()
{
	HMODULE hMod = LoadLibrary(L"AlgorithmTestDLL.dll");
	//未经处理直接角点侦测
	/**/
	string tem05 = DIR_05_SRC_SBF_SCRATCH + "1_00418.bmp";
	string tem02 = DIR_02_SRC_CRACK + "000703_original.bmp";
	string tem04 = DIR_04_SRC_TRAIN + "000735.bmp";
	opencvHarris(tem02.c_str());
	//opencvGoodFeatureToTrack(tem04.c_str());

	FreeLibrary(hMod);
}

void siftDetectTest()
{
	HMODULE hMod = LoadLibrary(L"AlgorithmTestDLL.dll");
	string tem04 = DIR_04_SRC_TRAIN + "000735.bmp";
	sigleImgSift(tem04.c_str());
	FreeLibrary(hMod);
}

void lineDetectTest()
{
	HMODULE hMod = LoadLibrary(L"AlgorithmTestDLL.dll");
	string tem04 = DIR_04_SRC_TRAIN + "000735.bmp";
	//houghLinePDetect(tem04.c_str());

	edgeLineDetect(tem04.c_str());
	FreeLibrary(hMod);
}

void edlinesTest()
{
	//EDLines 使用范例
	/*
	Mat imageRGB = imread("000735.bmp");
	Mat image = imread("000735.bmp", 0);
	EDLines lineHandler = EDLines(image);
	Mat outputImage;

	imshow("INPUT IMAGE", imageRGB);
	waitKey(WAIT_TIME);
	outputImage = lineHandler.getSmoothImage();
	imshow("SMOOTHING", outputImage);
	waitKey(WAIT_TIME);
	outputImage = lineHandler.getGradImage();
	imshow("GRADIENT AND THRESHOLDING", outputImage);
	waitKey(WAIT_TIME);
	outputImage = lineHandler.getAnchorImage();
	imshow("ANCHORING AND CONNECTING THEM", outputImage);
	waitKey(WAIT_TIME);
	outputImage = lineHandler.getEdgeImage();
	imshow("EDGES", outputImage);
	waitKey(WAIT_TIME);
	outputImage = lineHandler.getLineImage();
	imshow("ED LINES", outputImage);
	waitKey(WAIT_TIME);
	outputImage = lineHandler.drawOnImage();
	imshow("ED LINES OVER SOURCE IMAGE", outputImage);
	waitKey(0);
	*/

	HMODULE hMod = LoadLibrary(L"AlgorithmTestDLL.dll");
	string tem04 = DIR_04_SRC_TRAIN + "000735.bmp";
	edgeLineDetect(tem04.c_str());
	FreeLibrary(hMod);
}

void mixDetectTest()
{
	HMODULE hMod = LoadLibrary(L"AlgorithmTestDLL.dll");
	string tem04 = DIR_04_SRC_TRAIN + "000735.bmp";
	string tem05 = DIR_05_SRC_SBF_TAD_POLE + "6_04073.bmp";
	//先进行灰度调整(二值化)再使用角点直线混合侦测
	/*
	//mixEDlines_GoodFeature(tem04.c_str());
	mixEDlines_GoodFeature2(tem04.c_str());
	*/

	//图像增强后在处理
	//mix_IE_ED_GF(tem04.c_str(), 4);
	//mix_IE_ED_GF2(tem04.c_str(), 4);
	mix_IE_ED_GF2(tem05.c_str(), 4);
	FreeLibrary(hMod);
}

void imageEnhanceFlagHint()
{
	/*图像增强方法
	* 0，直方图均衡化
	* 1，拉普拉斯算子局部增强
	* 2，log函数映射（非线性映射）
	* 3，伽马变换
	* 4，线性对比度展宽
	* 5，自适应阈值，图像二值化
	* 6，自适应阈值，截断式
	*/
	cout << "\n\nselect enhance mode:\n";
	cout << "0.equalize hist\n";
	cout << "1.laplacian enhance\n";
	cout << "2.nonlinear enhance\n";
	cout << "3.gamma transform\n";
	cout << "4.linear wide\n";
	cout << "5.adaptive threshold(binary)\n";
	cout << "6.adaptive threshold(binary_inf)\n";
}

void GenerateHint()
{
	cout << "1. DATASET 01\n";
	cout << "2. DATASET 02 Crack\n";
	cout << "3. DATASET 04 Train\n";
	cout << "4. DATASET 04 Validate\n";
	cout << "5. DATASET 05 Scratch\n";
}

void loopMain(const char* c)
{
	HMODULE hMod = LoadLibrary(L"AlgorithmTestDLL.dll");
	int mode = 0;
	int EnhanceMode = 0;
	int DataSet = 0;
	while (cin >> mode)
	{
		switch (mode)
		{
		case 1:
			mixEDlines_GoodFeature(c);
			break;

		case 2:
			mixEDlines_GoodFeature2(c);
			break;

		case 3:
			imageEnhanceFlagHint();
			cin >> EnhanceMode;
			mix_IE_ED_GF(c, EnhanceMode);
			break;

		case 4:
			imageEnhanceFlagHint();
			cin >> EnhanceMode;
			mix_IE_ED_GF2(c, EnhanceMode);
			break;

		case 5:
			sigleImgSift(c);
			break;

		case 6:
			imageEnhanceFlagHint();
			cin >> EnhanceMode;
			mix_IE_ED_GF_RG(c, EnhanceMode);
			break;

		case 7:
			imageEnhanceFlagHint();
			cin >> EnhanceMode;
			mix_IE_ED_GF_RG_EX(c, EnhanceMode);
			break;

		case 20:
			imageEnhanceFlagHint();
			cin >> EnhanceMode;
			GenerateHint();
			cin >> DataSet;
			EnhanceImageOutput(DataSet, EnhanceMode);
			break;

		case 21:
			showGray(c);
			break;
		default:
			return;
		}
		destroyAllWindows();

		cout << "select mode:\n";
		cout << "1.EDlines and GoodFeature with threshold\n";
		cout << "2.EDlines and GoodFeature with threshold (binary)\n";
		cout << "3.EDlines and GoodFeature with threshold and image enhancing\n";
		cout << "4.EDlines and GoodFeature with threshold (binary) and image enhancing\n";
		cout << "5.Single SIFT\n";
		cout << "6.using region grow after image enhancing\n";
		cout << "7.using region growEx after image enhancing\n";
		cout << "20.generate a serise of image after enhancing\n";
		cout << "21.show Pixel by given Gray\n";
	}
	FreeLibrary(hMod);
}

int main(int argc, char** argv)
{


	cout << "select mode:\n";
	cout << "1.EDlines and GoodFeature with threshold\n";
	cout << "2.EDlines and GoodFeature with threshold (binary)\n";
	cout << "3.EDlines and GoodFeature with threshold and image enhancing\n";
	cout << "4.EDlines and GoodFeature with threshold (binary) and image enhancing\n";
	cout << "5.Single SIFT\n";
	cout << "6.using region grow after image enhancing\n";
	cout << "7.using region growEx after image enhancing\n";
	cout << "20.generate a serise of image after enhancing\n";
	cout << "21.show Pixel by given Gray\n";
	//conerDetectTest();
	//siftDetectTest();
	//lineDetectTest();
	//mixDetectTest();
	//edlinesTest();

	//string tem04 = DIR_04_SRC_TRAIN + "000735.bmp";
	//mix_IE_ED_GF_RG(tem04.c_str(), 6);
	//cout << argc << endl;
	if (argc > 1)
	{
		char* c = argv[1];
		loopMain(c);
	}
	else
	{
		string tem04 = DIR_04_SRC_TRAIN + "000735.bmp";
		loopMain(tem04.c_str());
	}

	return 0;
}
