#include"mixFeatureDetect.h"

#define DLLEXPORT extern "C" __declspec(dllexport)

class MFD
{
public:
	Mat srcImg;
	Mat graySrcImg;
	int	g_fa = 50, g_fb = 100, g_ga = 30, g_gb = 120;//线性展宽用参数
	int gamma = 10;//伽马变换用参数
	int flag = 0;
	int blockSize = 3;
	int c = 2;
	int mode = 0;
	/*图像增强模式
	* 0，直方图均衡化
	* 1，拉普拉斯算子局部增强
	* 2，log函数映射（非线性映射）
	* 3，伽马变换
	* 4，线性对比度展宽
	*/
private:

};

Mat		MFD_img;
Mat		MFD_gray;
//mixEDLines_GoodFeature用参数
int		MFD_mix_EDgood_grayLowthreshold = 40;
int		MFD_mix_EDgood_grayHighthreshold = 100;
int		MFD_grayMax = 255;
int		MFD_mix_EDgood_maxCorners = 100;
int		MFD_mix_EDgood_MAX_maxCorners = 500;
//________________________________________________________________
int		MFD_mode = 0;
/*图像增强方法
* 0，直方图均衡化
* 1，拉普拉斯算子局部增强
* 2，log函数映射（非线性映射）
* 3，伽马变换
* 4，线性对比度展宽
*/
//________________________________________________________________
int g_value = 1;

DLLEXPORT void mixEDlines_GoodFeature(const char* s)
{
	MFD_img = imread(s);
	cvtColor(MFD_img, MFD_gray, COLOR_BGR2GRAY);
	namedWindow("mix_EDGood", 0);
	createTrackbar("lowThreshold:", "mix_EDGood", &MFD_mix_EDgood_grayLowthreshold, MFD_grayMax, mixED_GoodTrackBar);
	mixED_GoodTrackBar(0, 0);
	createTrackbar("highThreshold:", "mix_EDGood", &MFD_mix_EDgood_grayHighthreshold, MFD_grayMax, mixED_GoodTrackBar);
	mixED_GoodTrackBar(0, 0);
	createTrackbar("MaxCorners:", "mix_EDGood", &MFD_mix_EDgood_maxCorners, MFD_mix_EDgood_MAX_maxCorners, mixED_GoodTrackBar);
	mixED_GoodTrackBar(0, 0);

	imshow("mix_EDGood_source", MFD_img);
	waitKey();
}


void mixED_GoodTrackBar(int, void*)
{
	Mat srcImg = MFD_img.clone();
	Mat dst = MFD_img.clone();
	Mat grayChangeImg = MFD_gray.clone();
	Mat goodFeatureImg = MFD_img.clone();
	Mat edlinesImg;
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			if (grayChangeImg.at<uchar>(i, j) < MFD_mix_EDgood_grayLowthreshold
				|| grayChangeImg.at<uchar>(i, j) > MFD_mix_EDgood_grayHighthreshold)
			{
				grayChangeImg.at<uchar>(i, j) = 255;
			}
			else
			{
				grayChangeImg.at<uchar>(i, j) = 0;
			}
		}
	}
	imshow("Mix_grayChange", grayChangeImg);

	vector<Point2f> corners;
	goodFeaturesToTrack(grayChangeImg, corners, MFD_mix_EDgood_maxCorners, 0.01, 3.0, Mat(), 3, false, 0.04);
	//指定亚像素计算迭代标注，暂时似乎没必要
	//TermCriteria tc = TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 40, 0.01);

	for (int i = 0; i < corners.size(); i++)
	{
		circle(goodFeatureImg, corners[i], 1, Scalar(0, 255, 0), 2, 8, 0);
	}
	imshow("Mix_GoodFeature", goodFeatureImg);

	EDLines temEDLines = EDLines(grayChangeImg);
	edlinesImg = temEDLines.drawOnImage();
	imshow("Mix_EDlines", edlinesImg);

	dst = temEDLines.drawOnImage();
	for (int i = 0; i < corners.size(); i++)
	{
		circle(dst, corners[i], 1, Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("mix_EDGood", dst);

}


DLLEXPORT void mixEDlines_GoodFeature2(const char* s)
{
	MFD_img = imread(s);
	cvtColor(MFD_img, MFD_gray, COLOR_BGR2GRAY);
	namedWindow("mix_EDGood2", 0);
	createTrackbar("lowThreshold:", "mix_EDGood2", &MFD_mix_EDgood_grayLowthreshold, MFD_grayMax, mixED_GoodTrackBar2);
	mixED_GoodTrackBar2(0, 0);
	createTrackbar("highThreshold:", "mix_EDGood2", &MFD_mix_EDgood_grayHighthreshold, MFD_grayMax, mixED_GoodTrackBar2);
	mixED_GoodTrackBar2(0, 0);
	createTrackbar("MaxCorners:", "mix_EDGood2", &MFD_mix_EDgood_maxCorners, MFD_mix_EDgood_MAX_maxCorners, mixED_GoodTrackBar2);
	mixED_GoodTrackBar2(0, 0);

	imshow("mix_EDGood_source2", MFD_img);
	waitKey();
}


void mixED_GoodTrackBar2(int, void*)
{
	Mat srcImg = MFD_img.clone();
	Mat dst = MFD_img.clone();
	Mat grayChangeImg = MFD_gray.clone();
	Mat goodFeatureImg = MFD_img.clone();
	Mat edlinesImg;
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			if (grayChangeImg.at<uchar>(i, j) < MFD_mix_EDgood_grayLowthreshold
				|| grayChangeImg.at<uchar>(i, j) > MFD_mix_EDgood_grayHighthreshold)
			{
				grayChangeImg.at<uchar>(i, j) = 255;
			}
		}
	}
	imshow("Mix_grayChange2", grayChangeImg);

	vector<Point2f> corners;
	goodFeaturesToTrack(grayChangeImg, corners, MFD_mix_EDgood_maxCorners, 0.01, 3.0, Mat(), 3, false, 0.04);
	//指定亚像素计算迭代标注，暂时似乎没必要
	//TermCriteria tc = TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 40, 0.01);

	for (int i = 0; i < corners.size(); i++)
	{
		circle(goodFeatureImg, corners[i], 1, Scalar(0, 255, 0), 2, 8, 0);
	}
	imshow("Mix_GoodFeature2", goodFeatureImg);

	EDLines temEDLines = EDLines(grayChangeImg);
	edlinesImg = temEDLines.drawOnImage();
	imshow("Mix_EDlines2", edlinesImg);

	dst = temEDLines.drawOnImage();
	for (int i = 0; i < corners.size(); i++)
	{
		circle(dst, corners[i], 1, Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("mix_EDGood2", dst);

}


DLLEXPORT void mix_IE_ED_GF(const char* s, int flag)
{
	MFD mfd;
	mfd.flag = flag;
	mfd.srcImg = imread(s);
	cvtColor(mfd.srcImg, mfd.graySrcImg, COLOR_BGR2GRAY);

	namedWindow("mix_imgEnhance_EDlines_GoodFeature", 0);

	if (flag == 3)
	{
		createTrackbar("gamma:", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.gamma, 720, mix_IE_ED_GF_TrackBar, &mfd);
		mix_IE_ED_GF_TrackBar(0, &mfd);
		createTrackbar("c:", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.c, 50, mix_IE_ED_GF_TrackBar, &mfd);
		mix_IE_ED_GF_TrackBar(0, &mfd);
	}
	else if (flag == 4)
	{
		createTrackbar("fa:", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.g_fa, 255, mix_IE_ED_GF_TrackBar, &mfd);
		mix_IE_ED_GF_TrackBar(0, &mfd);
		createTrackbar("fb:", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.g_fb, 255, mix_IE_ED_GF_TrackBar, &mfd);
		mix_IE_ED_GF_TrackBar(0, &mfd);
		createTrackbar("ga:", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.g_ga, 255, mix_IE_ED_GF_TrackBar, &mfd);
		mix_IE_ED_GF_TrackBar(0, &mfd);
		createTrackbar("gb:", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.g_gb, 255, mix_IE_ED_GF_TrackBar, &mfd);
		mix_IE_ED_GF_TrackBar(0, &mfd);
	}
	else if (flag == 5 || flag == 6)
	{
		createTrackbar("blockSize", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.blockSize, 50, mix_IE_ED_GF_TrackBar, &mfd);
		createTrackbar("mode", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.mode, 1, mix_IE_ED_GF_TrackBar, &mfd);
		createTrackbar("c", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.c, 50, mix_IE_ED_GF_TrackBar, &mfd);
	}
	createTrackbar("lowThreshold:", "mix_imgEnhance_EDlines_GoodFeature",
		&MFD_mix_EDgood_grayLowthreshold, MFD_grayMax, mix_IE_ED_GF_TrackBar, &mfd);
	mix_IE_ED_GF_TrackBar(0, &mfd);
	createTrackbar("highThreshold:", "mix_imgEnhance_EDlines_GoodFeature",
		&MFD_mix_EDgood_grayHighthreshold, MFD_grayMax, mix_IE_ED_GF_TrackBar, &mfd);
	mix_IE_ED_GF_TrackBar(0, &mfd);
	createTrackbar("MaxCorners:", "mix_imgEnhance_EDlines_GoodFeature",
		&MFD_mix_EDgood_maxCorners, MFD_mix_EDgood_MAX_maxCorners, mix_IE_ED_GF_TrackBar, &mfd);
	mix_IE_ED_GF_TrackBar(0, &mfd);


	waitKey();
}

void mix_IE_ED_GF_TrackBar(int value, void* mfd)
{
	Mat IE_img;
	MFD mmfd = *(MFD*)mfd;
	Mat dst = mmfd.srcImg.clone();
	Mat goodFeatureImg = mmfd.srcImg.clone();
	Mat edlinesImg;
	imshow("srcimg", mmfd.srcImg);
	if (mmfd.flag == 0)
	{
		IE_img = NoArgimageEnhance(mmfd.graySrcImg, 0);
	}
	else if (mmfd.flag == 1)
	{
		IE_img = NoArgimageEnhance(mmfd.graySrcImg, 1);
	}
	else if (mmfd.flag == 2)
	{
		IE_img = NoArgimageEnhance(mmfd.graySrcImg, 2);
	}
	else if (mmfd.flag == 3)
	{
		//cout << mmfd.gamma << " " << mmfd.c << endl;
		IE_img = GammaMapping(mmfd.graySrcImg, mmfd.gamma, mmfd.c);
	}
	else if (mmfd.flag == 4)
	{
		IE_img = LinearWide(mmfd.graySrcImg, mmfd.g_fa, mmfd.g_fb, mmfd.g_ga, mmfd.g_gb);
	}
	else if (mmfd.flag == 5)
	{
		IE_img = MyAdaptiveThreshold_Binary(mmfd.graySrcImg, mmfd.blockSize, mmfd.mode, mmfd.c);
	}
	else if (mmfd.flag == 6)
	{
		IE_img = MyAdaptiveThreshold_ThCut(mmfd.graySrcImg, mmfd.blockSize, mmfd.mode, mmfd.c);
	}
	else
	{
		IE_img = mmfd.graySrcImg;
	}
	imshow("IE_img", IE_img);

	Mat grayChangeImg = IE_img.clone();
	for (int i = 0; i < grayChangeImg.rows; i++)
	{
		for (int j = 0; j < grayChangeImg.cols; j++)
		{
			if (grayChangeImg.at<uchar>(i, j) < MFD_mix_EDgood_grayLowthreshold
				|| grayChangeImg.at<uchar>(i, j) > MFD_mix_EDgood_grayHighthreshold)
			{
				grayChangeImg.at<uchar>(i, j) = 255;
			}
		}
	}
	imshow("grayChange", grayChangeImg);

	vector<Point2f> corners;
	goodFeaturesToTrack(grayChangeImg, corners, MFD_mix_EDgood_maxCorners, 0.01, 3.0, Mat(), 3, false, 0.04);
	for (int i = 0; i < corners.size(); i++)
	{
		circle(goodFeatureImg, corners[i], 1, Scalar(0, 255, 0), 2, 8, 0);
	}
	imshow("GoodFeature", goodFeatureImg);

	EDLines temEDLines = EDLines(grayChangeImg);
	edlinesImg = temEDLines.drawOnImage();
	imshow("EDlines", edlinesImg);

	dst = temEDLines.drawOnImage();
	for (int i = 0; i < corners.size(); i++)
	{
		circle(dst, corners[i], 1, Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("mix_imgEnhance_EDlines_GoodFeature", dst);
}


DLLEXPORT void mix_IE_ED_GF2(const char* s, int flag)
{
	MFD mfd;
	mfd.flag = flag;
	mfd.srcImg = imread(s);
	cvtColor(mfd.srcImg, mfd.graySrcImg, COLOR_BGR2GRAY);

	namedWindow("mix_imgEnhance_EDlines_GoodFeature");

	if (flag == 3)
	{
		createTrackbar("gamma:", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.gamma, 720, mix_IE_ED_GF_TrackBar2, &mfd);
		mix_IE_ED_GF_TrackBar2(0, &mfd);
		createTrackbar("c:", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.c, 50, mix_IE_ED_GF_TrackBar2, &mfd);
		mix_IE_ED_GF_TrackBar2(0, &mfd);
	}
	else if (flag == 4)
	{
		createTrackbar("fa:", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.g_fa, 255, mix_IE_ED_GF_TrackBar2, &mfd);
		mix_IE_ED_GF_TrackBar2(0, &mfd);
		createTrackbar("fb:", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.g_fb, 255, mix_IE_ED_GF_TrackBar2, &mfd);
		mix_IE_ED_GF_TrackBar2(0, &mfd);
		createTrackbar("ga:", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.g_ga, 255, mix_IE_ED_GF_TrackBar2, &mfd);
		mix_IE_ED_GF_TrackBar2(0, &mfd);
		createTrackbar("gb:", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.g_gb, 255, mix_IE_ED_GF_TrackBar2, &mfd);
		mix_IE_ED_GF_TrackBar2(0, &mfd);
	}
	else if (flag == 5 || flag == 6)
	{
		createTrackbar("blockSize", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.blockSize, 50, mix_IE_ED_GF_TrackBar2, &mfd);
		createTrackbar("mode", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.mode, 1, mix_IE_ED_GF_TrackBar2, &mfd);
		createTrackbar("c", "mix_imgEnhance_EDlines_GoodFeature",
			&mfd.c, 50, mix_IE_ED_GF_TrackBar2, &mfd);
	}
	createTrackbar("lowThreshold:", "mix_imgEnhance_EDlines_GoodFeature",
		&MFD_mix_EDgood_grayLowthreshold, MFD_grayMax, mix_IE_ED_GF_TrackBar2, &mfd);
	mix_IE_ED_GF_TrackBar2(0, &mfd);
	createTrackbar("highThreshold:", "mix_imgEnhance_EDlines_GoodFeature",
		&MFD_mix_EDgood_grayHighthreshold, MFD_grayMax, mix_IE_ED_GF_TrackBar2, &mfd);
	mix_IE_ED_GF_TrackBar2(0, &mfd);
	createTrackbar("MaxCorners:", "mix_imgEnhance_EDlines_GoodFeature",
		&MFD_mix_EDgood_maxCorners, MFD_mix_EDgood_MAX_maxCorners, mix_IE_ED_GF_TrackBar2, &mfd);
	mix_IE_ED_GF_TrackBar2(0, &mfd);


	waitKey();
}

void mix_IE_ED_GF_TrackBar2(int value, void* mfd)
{
	Mat IE_img;
	MFD mmfd = *(MFD*)mfd;
	Mat dst = mmfd.srcImg.clone();
	Mat goodFeatureImg = mmfd.srcImg.clone();
	Mat edlinesImg;
	imshow("srcimg", mmfd.srcImg);
	if (mmfd.flag == 0)
	{
		IE_img = NoArgimageEnhance(mmfd.graySrcImg, 0);
	}
	else if (mmfd.flag == 1)
	{
		IE_img = NoArgimageEnhance(mmfd.graySrcImg, 1);
	}
	else if (mmfd.flag == 2)
	{
		IE_img = NoArgimageEnhance(mmfd.graySrcImg, 2);
	}
	else if (mmfd.flag == 3)
	{
		//cout << mmfd.gamma << " " << mmfd.c << endl;
		IE_img = GammaMapping(mmfd.graySrcImg, mmfd.gamma, mmfd.c);
	}
	else if (mmfd.flag == 4)
	{
		IE_img = LinearWide(mmfd.graySrcImg, mmfd.g_fa, mmfd.g_fb, mmfd.g_ga, mmfd.g_gb);
	}
	else if (mmfd.flag == 5)
	{
		IE_img = MyAdaptiveThreshold_Binary(mmfd.graySrcImg, mmfd.blockSize, mmfd.mode, mmfd.c);
	}
	else if (mmfd.flag == 6)
	{
		IE_img = MyAdaptiveThreshold_ThCut(mmfd.graySrcImg, mmfd.blockSize, mmfd.mode, mmfd.c);
	}
	else
	{
		IE_img = mmfd.graySrcImg;
	}
	imshow("IE_img", IE_img);

	Mat grayChangeImg = IE_img.clone();
	for (int i = 0; i < grayChangeImg.rows; i++)
	{
		for (int j = 0; j < grayChangeImg.cols; j++)
		{
			if (grayChangeImg.at<uchar>(i, j) < MFD_mix_EDgood_grayLowthreshold
				|| grayChangeImg.at<uchar>(i, j) > MFD_mix_EDgood_grayHighthreshold)
			{
				grayChangeImg.at<uchar>(i, j) = 255;
			}
			else
			{
				grayChangeImg.at<uchar>(i, j) = 0;
			}
		}
	}
	imshow("grayChange", grayChangeImg);

	vector<Point2f> corners;
	goodFeaturesToTrack(grayChangeImg, corners, MFD_mix_EDgood_maxCorners, 0.01, 3.0, Mat(), 3, false, 0.04);
	for (int i = 0; i < corners.size(); i++)
	{
		circle(goodFeatureImg, corners[i], 1, Scalar(0, 255, 0), 2, 8, 0);
	}
	imshow("GoodFeature", goodFeatureImg);

	EDLines temEDLines = EDLines(grayChangeImg);
	edlinesImg = temEDLines.drawOnImage();
	imshow("EDlines", edlinesImg);

	dst = temEDLines.drawOnImage();
	for (int i = 0; i < corners.size(); i++)
	{
		circle(dst, corners[i], 1, Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("mix_imgEnhance_EDlines_GoodFeature", dst);
}
