#include"coner_detect.h"

Mat CD_img;
Mat CD_imageGray;
int thresh = 200;			//harris阈值
int MaxThresh = 255;		//harris阈值最大值
int ConersCount = 100;		//goodFeatureToTrack MaxCorner参数
int MaxConersCount = 500;	//goodFeatureToTrack MaxCorner参数最大值

DLLEXPORT void opencvHarris(const char* s)
{
	CD_img = imread(s);
	cvtColor(CD_img, CD_imageGray, COLOR_BGR2GRAY);
	GaussianBlur(CD_imageGray, CD_imageGray, Size(5, 5), 1);
	namedWindow("Harris", 0);
	createTrackbar("threshold:", "Harris", &thresh, MaxThresh, Trackbar);
	imshow("Harris", CD_img);
	Trackbar(0, 0);
	waitKey();

}

void Trackbar(int, void*)
{
	Mat dst = Mat::zeros(CD_img.size(), CV_32FC1);
	Mat temImg = CD_img.clone();
	cornerHarris(CD_imageGray, dst, 3, 3, 0.04, BORDER_DEFAULT);
	normalize(dst, dst, 0, 255, NORM_MINMAX);
	convertScaleAbs(dst, dst);
	imshow("dst", dst);
	for (int i = 0; i < CD_img.rows; i++)
	{
		for (int j = 0; j < CD_img.cols; j++)
		{
			if (dst.at<uchar>(i, j) > thresh)
			{
				circle(temImg, Point(j, i), 2, Scalar(0, 0, 255), 2);
			}
		}
	}
	imshow("Harris", temImg);
}

DLLEXPORT void opencvGoodFeatureToTrack(const char* s)
{
	CD_img = imread(s);
	cvtColor(CD_img, CD_imageGray, COLOR_BGR2GRAY);
	GaussianBlur(CD_imageGray, CD_imageGray, Size(5, 5), 1);
	namedWindow("GoodFeatureTotrack", 0);
	createTrackbar("Max corners:", "GoodFeatureTotrack", &ConersCount, MaxConersCount, Trackbar1);
	imshow("GoodFeatureTotrack", CD_img);
	Trackbar1(0, 0);
	waitKey();
}

void Trackbar1(int, void*)
{
	Mat dst = Mat::zeros(CD_img.size(), CV_32FC1);
	Mat temImg = CD_img.clone();
	vector<Point2f> corners;
	goodFeaturesToTrack(CD_imageGray, corners, ConersCount, 0.01, 3.0, Mat(), 3, false, 0.04);
	//指定亚像素计算迭代标注，暂时似乎没必要
	TermCriteria tc = TermCriteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 40, 0.01);

	for (int i = 0; i < corners.size(); i++)
	{
		circle(temImg, corners[i], 1, Scalar(0, 255, 0), 2, 8, 0);
	}
	imshow("GoodFeatureTotrack", temImg);
}
