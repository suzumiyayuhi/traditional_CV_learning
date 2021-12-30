#include"line_detect.h"
#define DLLEXPORT extern "C" __declspec(dllexport)

Mat LD_img;
Mat LD_grayImg;
int			LD_low_canny_threshold = 40;		//houghLineP用参数
int			LD_high_canny_threshold = 100;		//houghLineP用参数
int			LD_MAX_canny_threshold = 255;		//houghLineP用参数
float		LD_rho = 1;							//houghLineP用参数
float		LD_theta = CV_PI / 180;				//houghLineP用参数
int			LD_houghLineP_threshold = 80;		//houghLineP用参数


DLLEXPORT void houghLinePDetect(const char* s)
{
	LD_img = imread(s);
	cvtColor(LD_img, LD_grayImg, COLOR_BGR2GRAY);
	GaussianBlur(LD_grayImg, LD_grayImg, Size(5, 5), 1);
	namedWindow("houghLinePDetect", 0);
	createTrackbar("Canny_low_threshold:", "houghLinePDetect",
		&LD_low_canny_threshold, LD_MAX_canny_threshold, houghLinePTrackBar);
	houghLinePTrackBar(0, 0);
	createTrackbar("Canny_high_threshold:", "houghLinePDetect",
		&LD_high_canny_threshold, LD_MAX_canny_threshold, houghLinePTrackBar);
	houghLinePTrackBar(0, 0);
	createTrackbar("houghLineP_threshold:", "houghLinePDetect",
		&LD_houghLineP_threshold, 255, houghLinePTrackBar);
	houghLinePTrackBar(0, 0);

	imshow("source", LD_img);
	waitKey();

}

void houghLinePTrackBar(int, void*)
{
	Mat dst = LD_grayImg.clone();
	Mat dst1 = LD_img.clone();
	Mat temEdge;
	vector<Vec4f> houghLines;
	int kernelSize = 3;
	Sobel(LD_grayImg, temEdge, CV_8UC1, 1, 1, kernelSize, 1.0, 0.0, 4);
	Canny(temEdge, dst, LD_low_canny_threshold, LD_high_canny_threshold);

	HoughLinesP(dst, houghLines, LD_rho, LD_theta, LD_houghLineP_threshold);
	for (int i = 0; i < houghLines.size(); i++)
	{
		Point p1 = Point(houghLines[i][0], houghLines[i][1]);
		Point p2 = Point(houghLines[i][2], houghLines[i][3]);
		line(dst1, p1, p2, Scalar(220, 220, 255), 2);
	}
	imshow("houghLinePDetect", dst1);
	imshow("houghLinePDetect_Canny", dst);
}


DLLEXPORT void edgeLineDetect(const char* s)
{
	LD_img = imread(s);
	cvtColor(LD_img, LD_grayImg, COLOR_BGR2GRAY);
	EDLines temEDLines = EDLines(LD_grayImg);
	Mat dst;
	dst = temEDLines.drawOnImage();
	imshow("source", LD_img);
	imshow("EDLines_result", dst);
	waitKey();
}
