#include"sharpening.h"


void Prewitt(Mat originImage, Mat& dstImage, Mat& thetaImage)
{
	//    cvtColor(originImage, originImage, COLOR_BGR2GRAY);
	//    originImage.convertTo(originImage, CV_32FC1);
	float maskX[3][3] = { {1,0,-1},{1,0,-1},{1,0,-1} };
	float maskY[3][3] = { {1,1,1},{0,0,0},{-1,-1,-1} };
	int rows = originImage.rows;
	int cols = originImage.cols;
	Mat EdgeX, EdgeY, Edge;
	EdgeX.create(originImage.size(), CV_32FC1);
	EdgeY.create(originImage.size(), CV_32FC1);
	Edge.create(originImage.size(), CV_32FC1);
	int temSumX = 0;
	int temSumY = 0;
	int temSum = 0;
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					temSumX += originImage.at<float>(i + k - 1, j + l - 1) * maskX[k][l];
					temSumY += originImage.at<float>(i + k - 1, j + l - 1) * maskY[k][l];
					//cout << k << " " << l << endl;
				}
				//cout << temSumX << " " << temSumY << " " << temSum << endl;
			}
			temSum = sqrt(pow(temSumX, 2) + pow(temSumY, 2));
			temSumX = fmax(temSumX, 0);
			temSumY = fmax(temSumY, 0);
			EdgeX.at<float>(i, j) = temSumX;
			EdgeY.at<float>(i, j) = temSumY;
			Edge.at<float>(i, j) = temSum;
			/**/
			if (temSumY == 0)
				temSumY = 1;
			thetaImage.at<float>(i, j) = atan(temSumX / temSumY);
			temSumX = 0; temSumY = 0; temSum = 0;
			//cout << EdgeX.at<float>(i, j) << " " << EdgeY.at<float>(i, j) << " " << Edge.at<float>(i, j) << endl;

		}
	}/**/
	EdgeX.convertTo(EdgeX, CV_8UC1);
	EdgeY.convertTo(EdgeY, CV_8UC1);
	Edge.convertTo(Edge, CV_8UC1);
	//    thetaImage.convertTo(thetaImage, CV_8UC1);
	//    imshow("EdgeX", EdgeX);
	//    imshow("EdgeY", EdgeY);
	//    waitKey(0);
	//    destroyAllWindows();
	dstImage = Edge;
}

void PreWittOpenCV(Mat  srcImage, Mat& dstImage)
{
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY); //转换为灰度图像
	//转换为浮点类型
	srcImage.convertTo(srcImage, CV_32FC1);
	//x,y方向上的卷积核
	Mat maskX = (Mat_<double>(3, 3) << 1, 1, 1, 0, 0, 0, -1, -1, -1);
	Mat maskY = (Mat_<double>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
	Mat Edgex;
	Mat EdgeY;
	//卷积操作
	filter2D(srcImage, Edgex, srcImage.depth(), maskX);
	filter2D(srcImage, EdgeY, srcImage.depth(), maskY);

	//计算目标图像

	dstImage.create(srcImage.size(), CV_32FC1);
	int rows = Edgex.rows;
	int cols = Edgex.cols;

	imshow("Edgex", Edgex);
	imshow("Edgey", EdgeY);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			dstImage.at<float>(i, j) = max(Edgex.at<float>(i, j), EdgeY.at<float>(i, j));
		}
	}


	convertScaleAbs(dstImage, dstImage);
	dstImage.convertTo(dstImage, CV_8UC1);
	imshow("dstImage", dstImage);
	waitKey(0);
	destroyAllWindows();
}

void Sobel(Mat originImage, Mat& dstImage, Mat& thetaImage)
{
	float maskX[3][3] = { {1,0,-1},{2,0,-2},{1,0,-1} };
	float maskY[3][3] = { {1,2,1},{0,0,0},{-1,-2,-1} };
	int rows = originImage.rows;
	int cols = originImage.cols;
	Mat EdgeX, EdgeY, Edge;
	EdgeX.create(originImage.size(), CV_32FC1);
	EdgeY.create(originImage.size(), CV_32FC1);
	Edge.create(originImage.size(), CV_32FC1);
	int temSumX = 0;
	int temSumY = 0;
	int temSum = 0;
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					temSumX += originImage.at<float>(i + k - 1, j + l - 1) * maskX[k][l];
					temSumY += originImage.at<float>(i + k - 1, j + l - 1) * maskY[k][l];
					//cout << k << " " << l << endl;
				}

			}
			//cout << temSumX << " " << temSumY << " " << temSum << endl;
			temSum = sqrt(pow(temSumX, 2) + pow(temSumY, 2));
			temSumX = fmax(temSumX, 0);
			temSumY = fmax(temSumY, 0);
			EdgeX.at<float>(i, j) = temSumX;
			EdgeY.at<float>(i, j) = temSumY;
			Edge.at<float>(i, j) = temSum;

			if (temSumY == 0)
				temSumY = 1;
			thetaImage.at<float>(i, j) = atan(temSumX / temSumY);
			temSumX = 0; temSumY = 0; temSum = 0;
			//cout << EdgeX.at<float>(i, j) << " " << EdgeY.at<float>(i, j) << " " << Edge.at<float>(i, j) << endl;

		}
	}/**/
	EdgeX.convertTo(EdgeX, CV_8UC1);
	EdgeY.convertTo(EdgeY, CV_8UC1);
	Edge.convertTo(Edge, CV_8UC1);
	//    thetaImage.convertTo(thetaImage, CV_8UC1);
	imshow("EdgeX", EdgeX);
	imshow("EdgeY", EdgeY);
	//    imshow("Edge", Edge);
	//    waitKey(0);
	//    destroyAllWindows();
	dstImage = Edge;
}

Mat getPartial(Mat srcImage, int flag)
{
	float maskX[3][3] = { {1,0,-1},{2,0,-2},{1,0,-1} };
	float maskY[3][3] = { {1,2,1},{0,0,0},{-1,-2,-1} };
	Mat EdgeX, EdgeY, Edge;
	EdgeX.create(srcImage.size(), CV_32FC1);
	EdgeY.create(srcImage.size(), CV_32FC1);
	Edge.create(srcImage.size(), CV_32FC1);
	int temSumX = 0;
	int temSumY = 0;
	int temSum = 0;
	for (int i = 1; i < srcImage.rows - 1; i++)
	{
		for (int j = 1; j < srcImage.cols - 1; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					temSumX += srcImage.at<float>(i + k - 1, j + l - 1) * maskX[k][l];
					temSumY += srcImage.at<float>(i + k - 1, j + l - 1) * maskY[k][l];
					//cout << k << " " << l << endl;
				}
			}
			temSum = sqrt(pow(temSumX, 2) + pow(temSumY, 2));
			temSumX = fmax(temSumX, 0);
			temSumY = fmax(temSumY, 0);
			EdgeX.at<float>(i, j) = temSumX;
			EdgeY.at<float>(i, j) = temSumY;
			Edge.at<float>(i, j) = temSum;
			if (temSumY == 0)
				temSumY = 1;
			temSumX = 0; temSumY = 0; temSum = 0;
		}
	}

	if (flag == 0)
		return EdgeX;
	if (flag == 1)
		return EdgeY;
	else
		return Edge;
}
