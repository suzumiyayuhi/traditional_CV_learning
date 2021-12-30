#include"base.h"
#define DLLEXPORT extern "C" __declspec(dllexport)

Mat B_img;
Mat B_imageGray;
int lowThreshold = 50;		//对比度调整用参数
int highThreshold = 100;	//对比度调整用参数
int B_MAXThresh = 255;

DLLEXPORT void testHelloWorld()
{
	cout << "hello world!" << endl;
	cout << "hello world!" << endl;
	cout << "hello world!" << endl;
	cout << "hello world!" << endl;
}

DLLEXPORT char* testArg(const char* s)
{
	cout << s << endl;
	string ss = s;
	int er;
	cin >> er;
	cout << er << endl;

	char* temStr = new char[ss.size()];
	for (int i = 0; i < ss.size(); i++)
	{
		temStr[i] = ss[i];
	}
	return temStr;
}

DLLEXPORT vector<string> getDirFile(string path)
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

DLLEXPORT char* getCstrFromVec(const char* dirPath)
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

DLLEXPORT void changeImageGray(const char* imgPath)
{
	B_img = imread(imgPath);
	cvtColor(B_img, B_imageGray, COLOR_BGR2GRAY);
	namedWindow("ChangeImageGrayLevel", 0);
	createTrackbar("lowThreshold:", "ChangeImageGrayLevel", &lowThreshold, B_MAXThresh, Trackbar3);
	Trackbar3(0, 0);
	createTrackbar("highThreshold:", "ChangeImageGrayLevel", &highThreshold, B_MAXThresh, Trackbar3);
	Trackbar3(0, 0);
	imshow("ChangeImageGrayLevel_0", B_img);
	waitKey();
	/**/
	cout << "save?(Y/N)";
	char flag;
	flag = getchar();
	if (flag == 'Y')
	{
		Mat dst = B_imageGray.clone();
		for (int i = 0; i < dst.rows; i++)
		{
			for (int j = 0; j < dst.cols; j++)
			{
				if (dst.at<uchar>(i, j) < lowThreshold || dst.at<uchar>(i, j) > highThreshold)
				{
					dst.at<uchar>(i, j) = 255;
				}
			}
		}
		char* ts = new char[strlen(imgPath)];
		strcpy_s(ts, strlen(imgPath) + 1, imgPath);
		const char* tem = "_CIG.jpg";
		strcat_s(ts, strlen(ts) + strlen(tem) + 1, tem);
		cout << ts << endl;
		imwrite(ts, dst);
	}
	else
		return;
}

void Trackbar3(int, void*)
{
	Mat dst = B_imageGray.clone();
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			if (dst.at<uchar>(i, j) < lowThreshold || dst.at<uchar>(i, j) > highThreshold)
			{
				dst.at<uchar>(i, j) = 255;
			}
			else
			{
				dst.at<uchar>(i, j) = 0;
			}
		}
	}
	imshow("ChangeImageGrayLevel", dst);

}

void TrackBar4(int, void*)
{
	Mat dst = B_imageGray.clone();
	Mat dst1 = Mat::zeros(dst.size(), CV_8UC1);
	Mat temDst = B_img.clone();
	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			if (dst.at<uchar>(i, j) == lowThreshold)
			{
				circle(temDst, Point(j, i), 1, Scalar(0, 255, 0), 1);
				dst1.at<uchar>(i, j) = dst.at<uchar>(i, j);
			}
		}
	}
	imshow("ShowImageGrayLevel", dst1);
	imshow("ShowImageGrayLevel2", temDst);
}

DLLEXPORT void showGray(const char* imgPath)
{
	B_img = imread(imgPath);
	cvtColor(B_img, B_imageGray, COLOR_BGR2GRAY);
	namedWindow("ShowImageGrayLevel", 0);
	createTrackbar("Threshold:", "ShowImageGrayLevel", &lowThreshold, B_MAXThresh, TrackBar4);
	TrackBar4(0, 0);

	waitKey();
}
