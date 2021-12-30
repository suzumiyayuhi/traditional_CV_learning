#include"base.h"

class MRG
{
public:
	Mat srcImg;
	Mat srcImg2;
	Mat ieImg;
	Mat flagMat;
private:

};

void PaperTest(char* src)
{
	//Mat srcImage = imread("images\\zi.png");
//Mat srcImage = imread("images\\car_fog.png");
	Mat srcImage = imread(src);
	Mat grayImage = srcImage.clone();
	Mat imagePri[10];
	//cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	imshow("source grayImage", grayImage);

	grayImage.convertTo(grayImage, CV_32FC3);
	int cols = grayImage.cols;
	for (int i = 1; i < 11; i++)
	{
		float sigmaPara = i * 0.01 * cols;
		float gaussPara = 1 / (sigmaPara * powf(2 * CV_PI, 0.5)) * exp(-2 / 2 / pow(sigmaPara, 2));
		cout << gaussPara << endl;
		imagePri[i - 1] = grayImage * gaussPara;
	}
	for (int i = 0; i < 10; i++)
	{
		imagePri[i].convertTo(imagePri[i], CV_8UC3);
		//normalize(imagePri[i], imagePri[i], 255, NORM_MINMAX);
		imshow(to_string(i), imagePri[i] * 50);
	}
	waitKey();
	destroyAllWindows();
}

Mat RegionGrowDrawRec(Mat src, Point2i pt, Mat flagMat)
{
	Mat matDst;
	Point2i start = pt;
	matDst = Mat::zeros(src.size(), CV_8UC3);
	Scalar startScalarLevel;
	Scalar currentScalarLevel;
	int leftX = pt.x, leftY = pt.y, rightX = pt.x, rightY = pt.y;
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
		if (sx < leftX)
			leftX = sx;
		if (sy < leftY)
			leftY = sy;
		if (sx > rightX)
			rightX = sx;
		if (sy > rightY)
			rightY = sy;
		flagMat.at<uchar>(sy, sx) = 1;
		startScalarLevel = src.at<Vec3b>(sy, sx);
		for (int i = 0; i < 8; i++)
		{
			int cx = sx + dir[i][0];
			int cy = sy + dir[i][1];
			if (cx<0 || cx>src.cols - 1 || cy<0 || cy>src.rows - 1)
				continue;
			currentScalarLevel = src.at<Vec3b>(cy, cx);
			if (startScalarLevel == currentScalarLevel && flagMat.at<uchar>(cy, cx) == 0)
			{
				matDst.at<Vec3b>(sy, sx) = src.at<Vec3b>(sy, sx);
				pts.push(Point2i(cx, cy));
			}
		}
	}
	Rect temRect(Point(leftX, leftY), Point(rightX, rightY));
	rectangle(matDst, temRect, Scalar(255, 255, 255));
	return matDst;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	MRG mmrg = *(MRG*)param;
	Mat dst;
	Point2i  pt;
	Scalar tem = mmrg.ieImg.at<Vec3b>(y, x);
	switch (event)
	{

	case EVENT_LBUTTONDOWN:
		cout << x << "\t" << y << endl;
		//imshow("IE_img2", mmrg.ieImg);
		cout << tem << endl;
		pt = Point2i(x, y);
		break;

		//左键放开
	case EVENT_LBUTTONUP:
		circle(mmrg.srcImg2, Point2i(x, y), 3, Scalar(210, 210, 255), -1);
		imshow("srcImg2", mmrg.srcImg2);
		pt = Point2i(x, y);
		dst = RegionGrowDrawRec(mmrg.ieImg, pt, mmrg.flagMat);//区域生长
		//bitwise_and(src_gray, dst, dst); //与运算
		imshow("RegionGrowDrawRec", dst);
		break;
	}

}

void ClickRegionGrowDrawRec(const char* s)
{
	MRG mrg;
	mrg.srcImg = imread(s);
	mrg.srcImg2 = mrg.srcImg.clone();
	mrg.ieImg = mrg.srcImg.clone();
	mrg.flagMat = Mat::zeros(mrg.srcImg.size(), CV_8UC1);
	MRG* mmrg = &mrg;

	namedWindow("srcImg");
	imshow("srcImg", mrg.srcImg);
	namedWindow("srcImg2");
	imshow("srcImg2", mrg.srcImg2);
	namedWindow("RegionGrowDrawRec");
	setMouseCallback("srcImg", on_MouseHandle, mmrg);//调用回调函数 
	waitKey();
}

Rect GetRegionGrowRec(Mat src, Point2i pt, Mat& flagMat)
{
	Mat matDst;
	Point2i start = pt;
	matDst = Mat::zeros(src.size(), CV_8UC3);
	Scalar startScalarLevel;
	Scalar currentScalarLevel;
	int leftX = pt.x, leftY = pt.y, rightX = pt.x, rightY = pt.y;
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
		if (sx < leftX)
			leftX = sx;
		if (sy < leftY)
			leftY = sy;
		if (sx > rightX)
			rightX = sx;
		if (sy > rightY)
			rightY = sy;
		flagMat.at<uchar>(sy, sx) = 1;
		startScalarLevel = src.at<Vec3b>(sy, sx);
		for (int i = 0; i < 8; i++)
		{
			int cx = sx + dir[i][0];
			int cy = sy + dir[i][1];
			if (cx<0 || cx>src.cols - 1 || cy<0 || cy>src.rows - 1)
				continue;
			currentScalarLevel = src.at<Vec3b>(cy, cx);
			if (startScalarLevel == currentScalarLevel && flagMat.at<uchar>(cy, cx) == 0)
			{
				matDst.at<Vec3b>(sy, sx) = src.at<Vec3b>(sy, sx);
				pts.push(Point2i(cx, cy));
			}
		}
	}
	Rect temRect(Point(leftX, leftY), Point(rightX, rightY));
	return temRect;
}

vector<string> getDirFile(string path)
{
	vector<cv::String> filePath;
	cv::String dirPath = cv::String(path + "*.*");
	glob(dirPath, filePath);
	/*
	for (int i = 0; i < filePath.size(); i++)
	{
		cout << filePath[i].c_str() << endl;
	}*/
	return filePath;
}

char* getCstrFromVec(const char* dirPath)
{
	vector<string> vec = getDirFile(dirPath);
	int i;
	cout << vec.size() << endl;
	cin >> i;
	int temss = strlen(vec[i].c_str());
	char* out = new char[temss];
	strcpy_s(out, temss + 1, vec[i].c_str());
	cout << out << endl;
	return out;
}

Mat RegionGrowChangePatchCrackLabel(Mat src, Point2i pt, Mat& flagMat)
{
	Mat matDst = src.clone();
	Point2i start = pt;
	Scalar startScalarLevel;
	Scalar currentScalarLevel;
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
		startScalarLevel = src.at<Vec3b>(sy, sx);
		for (int i = 0; i < 8; i++)
		{
			int cx = sx + dir[i][0];
			int cy = sy + dir[i][1];
			if (cx<0 || cx>src.cols - 1 || cy<0 || cy>src.rows - 1)
				continue;
			currentScalarLevel = src.at<Vec3b>(cy, cx);
			if (startScalarLevel == currentScalarLevel && flagMat.at<uchar>(cy, cx) == 0)
			{
				matDst.at<Vec3b>(sy, sx) = Vec3b(222, 222, 255);
				pts.push(Point2i(cx, cy));
			}
		}
	}
	return matDst;
}
