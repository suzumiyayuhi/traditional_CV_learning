#include"mixRegionGrow.h"

#define DLLEXPORT extern "C" __declspec(dllexport)

class MRG
{
public:
	Mat srcImg;
	Mat graySrcImg;
	Mat ieImg;
	Mat flagMat;
	int	g_fa = 50, g_fb = 100, g_ga = 30, g_gb = 120;//线性展宽用参数
	int gamma = 10;//伽马变换用参数
	int flag = 0;
	int th_diffence = 40;
	int blockSize = 3;
	int c = 2;
	int mode = 0;
private:

};

void RegionGrow(Mat src, Mat& matDst, Point2i pt, int th)
{
	Point2i start = pt;
	Mat flagMat = Mat::zeros(src.size(), CV_8UC1);
	matDst = Mat::zeros(src.size(), CV_8UC1);
	int startGrayLevel = 0;
	int currentGrayLevel = 0;
	int dir[8][2] = {
		-1,-1,
		-1,0,
		-1,1,
		0,-1,
		0,1,
		1,-1,
		1,0,
		1,-1
	};
	stack<Point2i> pts;
	pts.push(pt);
	while (!pts.empty())
	{
		start = pts.top();
		pts.pop();
		int sx = start.x;
		int sy = start.y;
		flagMat.at<uchar>(sy, sx) = 1;
		startGrayLevel = src.at<uchar>(sy, sx);
		for (int i = 0; i < 8; i++)
		{
			int cx = sx + dir[i][0];
			int cy = sy + dir[i][1];
			if (cx<0 || cx>src.cols - 1 || cy<0 || cy>src.rows - 1)
				continue;
			//matDst.at<uchar>(cy, cx) = 255;
			matDst.at<uchar>(cy, cx) = src.at<uchar>(cy, cx);
			currentGrayLevel = src.at<uchar>(cy, cx);
			//cout << abs(startGrayLevel - currentGrayLevel) << endl;
			if (abs(startGrayLevel - currentGrayLevel) < th && flagMat.at<uchar>(cy, cx) == 0)
			{
				pts.push(Point2i(cx, cy));
			}
		}
	}
}

void RegionGrowEx(Mat src, Mat& matDst, Point2i pt, int th)
{
	Point2i start = pt;
	Mat flagMat = Mat::zeros(src.size(), CV_8UC1);
	matDst = Mat::zeros(src.size(), CV_8UC1);
	int startGrayLevel = 0;
	int currentGrayLevel = 0;

	int ksize = 5;
	int krows = ksize * ksize - 1;
	int** dir = new int* [krows];
	for (int i = 0; i < krows; i++)
		dir[i] = new int[2]();
	for (int i = 0; i < krows; i++)
	{
		if (-2 + i / 5 == 0 && -2 + i % 5 == 0)
		{
			continue;
		}
		dir[i][0] = -2 + i / 5;
		dir[i][1] = -2 + i % 5;
	}

	stack<Point2i> pts;
	pts.push(pt);
	while (!pts.empty())
	{
		start = pts.top();
		pts.pop();
		int sx = start.x;
		int sy = start.y;
		flagMat.at<uchar>(sy, sx) = 1;
		startGrayLevel = src.at<uchar>(sy, sx);
		for (int i = 0; i < krows; i++)
		{
			int cx = sx + dir[i][0];
			int cy = sy + dir[i][1];
			if (cx<0 || cx>src.cols - 1 || cy<0 || cy>src.rows - 1)
				continue;
			//matDst.at<uchar>(cy, cx) = 255;
			matDst.at<uchar>(cy, cx) = src.at<uchar>(cy, cx);
			currentGrayLevel = src.at<uchar>(cy, cx);
			//cout << abs(startGrayLevel - currentGrayLevel) << endl;
			if (abs(startGrayLevel - currentGrayLevel) < th && flagMat.at<uchar>(cy, cx) == 0)
			{
				pts.push(Point2i(cx, cy));
			}
		}
	}
}

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	MRG mmrg = *(MRG*)param;
	Mat src_gray, dst;
	//	src_gray = mmrg.ieImg;
	Point2i  pt;
	switch (event)
	{

	case EVENT_LBUTTONDOWN:
		cout << x << "\t" << y << endl;
		pt = Point2i(x, y);
		break;

		//左键放开
	case EVENT_LBUTTONUP:
		circle(mmrg.srcImg, Point2i(x, y), 3, Scalar(210, 210, 255), -1);
		pt = Point2i(x, y);
		RegionGrow(mmrg.ieImg, dst, pt, mmrg.th_diffence);//区域生长
		//bitwise_and(src_gray, dst, dst); //与运算
		imshow("mix_IE_ED_GF_RG", dst);
		break;
	}

}

void mix_IE_ED_GF_RG_TrackBar1(int value, void* mrg)
{
	Mat dst, edlines_img, goodFeature_img;
	MRG* mmrg = (MRG*)mrg;
	imshow("srcImg", mmrg->srcImg);
	Mat IE_img;
	if (mmrg->flag == 0)
	{
		IE_img = NoArgimageEnhance(mmrg->graySrcImg, 0);
	}
	else if (mmrg->flag == 1)
	{
		IE_img = NoArgimageEnhance(mmrg->graySrcImg, 1);
	}
	else if (mmrg->flag == 2)
	{
		IE_img = NoArgimageEnhance(mmrg->graySrcImg, 2);
	}
	else if (mmrg->flag == 3)
	{
		IE_img = GammaMapping(mmrg->graySrcImg, mmrg->gamma, mmrg->c);
	}
	else if (mmrg->flag == 4)
	{
		IE_img = LinearWide(mmrg->graySrcImg, mmrg->g_fa, mmrg->g_fb, mmrg->g_ga, mmrg->g_gb);
	}
	else if (mmrg->flag == 5)
	{
		IE_img = MyAdaptiveThreshold_Binary(mmrg->graySrcImg, mmrg->blockSize, mmrg->mode, mmrg->c);
	}
	else if (mmrg->flag == 6)
	{
		IE_img = MyAdaptiveThreshold_ThCut(mmrg->graySrcImg, mmrg->blockSize, mmrg->mode, mmrg->c);
	}
	else
	{
		IE_img = mmrg->graySrcImg;
	}
	namedWindow("IE_img", 0);
	imshow("IE_img", IE_img);
	mmrg->ieImg = IE_img;
	Mat RegionGrow_img = IE_img.clone();
	setMouseCallback("IE_img", on_MouseHandle, mrg);//调用回调函数 
	//setMouseCallback("mix_IE_ED_GF_RG", on_MouseHandle);
}

DLLEXPORT void mix_IE_ED_GF_RG(const char* s, int flag)
{
	MRG mrg;
	mrg.flag = flag;
	mrg.srcImg = imread(s);
	cvtColor(mrg.srcImg, mrg.graySrcImg, COLOR_BGR2GRAY);
	namedWindow("mix_IE_ED_GF_RG");

	if (flag == 3)
	{
		createTrackbar("gamma:", "mix_IE_ED_GF_RG",
			&mrg.gamma, 720, mix_IE_ED_GF_RG_TrackBar1, &mrg);
		//		mix_IE_ED_GF_RG_TrackBar1(0, &mrg);
		createTrackbar("c:", "mix_IE_ED_GF_RG",
			&mrg.c, 50, mix_IE_ED_GF_RG_TrackBar1, &mrg);
		//		mix_IE_ED_GF_RG_TrackBar1(0, &mrg);
	}
	else if (flag == 4)
	{
		createTrackbar("fa:", "mix_IE_ED_GF_RG",
			&mrg.g_fa, 255, mix_IE_ED_GF_RG_TrackBar1, &mrg);
		//		mix_IE_ED_GF_RG_TrackBar1(0, &mrg);
		createTrackbar("fb:", "mix_IE_ED_GF_RG",
			&mrg.g_fb, 255, mix_IE_ED_GF_RG_TrackBar1, &mrg);
		//		mix_IE_ED_GF_RG_TrackBar1(0, &mrg);
		createTrackbar("ga:", "mix_IE_ED_GF_RG",
			&mrg.g_ga, 255, mix_IE_ED_GF_RG_TrackBar1, &mrg);
		//		mix_IE_ED_GF_RG_TrackBar1(0, &mrg);
		createTrackbar("gb:", "mix_IE_ED_GF_RG",
			&mrg.g_gb, 255, mix_IE_ED_GF_RG_TrackBar1, &mrg);
		//		mix_IE_ED_GF_RG_TrackBar1(0, &mrg);
	}
	else if (flag == 5 || flag == 6)
	{
		createTrackbar("blockSize", "mix_IE_ED_GF_RG",
			&mrg.blockSize, 50, mix_IE_ED_GF_RG_TrackBar1, &mrg);
		createTrackbar("mode", "mix_IE_ED_GF_RG",
			&mrg.mode, 1, mix_IE_ED_GF_RG_TrackBar1, &mrg);
		createTrackbar("c", "mix_IE_ED_GF_RG",
			&mrg.c, 50, mix_IE_ED_GF_RG_TrackBar1, &mrg);
	}
	createTrackbar("region grow th:", "mix_IE_ED_GF_RG",
		&mrg.th_diffence, 255, mix_IE_ED_GF_RG_TrackBar1, &mrg);
	mix_IE_ED_GF_RG_TrackBar1(0, &mrg);

	waitKey();
}


DLLEXPORT void mix_IE_ED_GF_RG_EX(const char* s, int flag)
{
	MRG mrg;
	mrg.flag = flag;
	mrg.srcImg = imread(s);
	cvtColor(mrg.srcImg, mrg.graySrcImg, COLOR_BGR2GRAY);
	namedWindow("mix_IE_ED_GF_RG_EX");

	if (flag == 3)
	{
		createTrackbar("gamma:", "mix_IE_ED_GF_RG_EX", &mrg.gamma, 720, mix_IE_ED_GF_RG_EX_TrackBar, &mrg);
		createTrackbar("c:", "mix_IE_ED_GF_RG_EX", &mrg.c, 50, mix_IE_ED_GF_RG_EX_TrackBar, &mrg);
	}
	else if (flag == 4)
	{
		createTrackbar("fa:", "mix_IE_ED_GF_RG_EX",
			&mrg.g_fa, 255, mix_IE_ED_GF_RG_EX_TrackBar, &mrg);
		createTrackbar("fb:", "mix_IE_ED_GF_RG_EX",
			&mrg.g_fb, 255, mix_IE_ED_GF_RG_EX_TrackBar, &mrg);
		createTrackbar("ga:", "mix_IE_ED_GF_RG_EX",
			&mrg.g_ga, 255, mix_IE_ED_GF_RG_EX_TrackBar, &mrg);
		createTrackbar("gb:", "mix_IE_ED_GF_RG_EX",
			&mrg.g_gb, 255, mix_IE_ED_GF_RG_EX_TrackBar, &mrg);
	}
	else if (flag == 5 || flag == 6)
	{
		createTrackbar("blockSize", "mix_IE_ED_GF_RG_EX",
			&mrg.blockSize, 50, mix_IE_ED_GF_RG_EX_TrackBar, &mrg);
		createTrackbar("mode", "mix_IE_ED_GF_RG_EX",
			&mrg.mode, 1, mix_IE_ED_GF_RG_EX_TrackBar, &mrg);
		createTrackbar("c", "mix_IE_ED_GF_RG_EX",
			&mrg.c, 50, mix_IE_ED_GF_RG_EX_TrackBar, &mrg);
	}
	createTrackbar("region grow th:", "mix_IE_ED_GF_RG_EX",
		&mrg.th_diffence, 255, mix_IE_ED_GF_RG_EX_TrackBar, &mrg);
	mix_IE_ED_GF_RG_EX_TrackBar(0, &mrg);

	waitKey();
}

void mix_IE_ED_GF_RG_EX_TrackBar(int value, void* mrg)
{
	Mat dst, edlines_img, goodFeature_img;
	MRG* mmrg = (MRG*)mrg;
	imshow("srcImg", mmrg->srcImg);
	Mat IE_img;
	if (mmrg->flag == 0)
	{
		IE_img = NoArgimageEnhance(mmrg->graySrcImg, 0);
	}
	else if (mmrg->flag == 1)
	{
		IE_img = NoArgimageEnhance(mmrg->graySrcImg, 1);
	}
	else if (mmrg->flag == 2)
	{
		IE_img = NoArgimageEnhance(mmrg->graySrcImg, 2);
	}
	else if (mmrg->flag == 3)
	{
		IE_img = GammaMapping(mmrg->graySrcImg, mmrg->gamma, mmrg->c);
	}
	else if (mmrg->flag == 4)
	{
		IE_img = LinearWide(mmrg->graySrcImg, mmrg->g_fa, mmrg->g_fb, mmrg->g_ga, mmrg->g_gb);
	}
	else if (mmrg->flag == 5)
	{
		IE_img = MyAdaptiveThreshold_Binary(mmrg->graySrcImg, mmrg->blockSize, mmrg->mode, mmrg->c);
	}
	else if (mmrg->flag == 6)
	{
		IE_img = MyAdaptiveThreshold_ThCut(mmrg->graySrcImg, mmrg->blockSize, mmrg->mode, mmrg->c);
	}
	else
	{
		IE_img = mmrg->graySrcImg;
	}
	namedWindow("IE_img", 0);
	imshow("IE_img", IE_img);
	mmrg->ieImg = IE_img;
	Mat RegionGrow_img = IE_img.clone();
	setMouseCallback("IE_img", on_MouseHandle2, mrg);//调用回调函数 
	//setMouseCallback("mix_IE_ED_GF_RG", on_MouseHandle);
}

void on_MouseHandle2(int event, int x, int y, int flags, void* param)
{
	MRG mmrg = *(MRG*)param;
	Mat src_gray, dst;
	//	src_gray = mmrg.ieImg;
	Point2i  pt;
	switch (event)
	{

	case EVENT_LBUTTONDOWN:
		cout << x << "\t" << y << endl;
		pt = Point2i(x, y);
		break;

		//左键放开
	case EVENT_LBUTTONUP:
		circle(mmrg.srcImg, Point2i(x, y), 3, Scalar(205, 120, 255), -1);
		pt = Point2i(x, y);
		RegionGrowEx(mmrg.ieImg, dst, pt, mmrg.th_diffence);//区域生长
		//bitwise_and(src_gray, dst, dst); //与运算
		imshow("mix_IE_ED_GF_RG_EX", dst);
		break;
	}
}
