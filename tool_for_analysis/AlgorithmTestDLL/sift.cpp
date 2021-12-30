#include"sift.h"
#define DLLEXPORT extern "C" __declspec(dllexport)

Mat SIFT_imgSift;
Mat SIFT_imgSiftGray;
int keyPoints = 50;//sift用
int MAX_keyPoints = 500;//sift用

DLLEXPORT void sigleImgSift(const char* s)
{
	SIFT_imgSift = imread(s);
	cvtColor(SIFT_imgSift, SIFT_imgSiftGray, COLOR_BGR2GRAY);
	namedWindow("sigleSift", 0);
	createTrackbar("Key Points:", "sigleSift", &keyPoints, MAX_keyPoints, siftTrackBar);
	siftTrackBar(0, 0);
	waitKey();
}

void siftTrackBar(int, void*)
{
	Mat dst = SIFT_imgSiftGray.clone();
	int kpCount = keyPoints;
	vector<KeyPoint> kp;
	Ptr<SiftFeatureDetector> siftDT = SiftFeatureDetector::create(kpCount);
	siftDT->detect(SIFT_imgSiftGray, kp);
	drawKeypoints(SIFT_imgSiftGray, kp, dst);
	imshow("sigleSift", dst);
}
