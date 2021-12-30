#include"blur.h"
#include"sharpening.h"
#include"canny.h"
#include"hough.h"
using namespace std;
using namespace cv;
#define PI 3.1415926535898

Mat NMSmmm(Mat srcImage, Mat& dstImage, Mat thetaImage)
{
	int c1 = 0, c2 = 0;
	int rows = srcImage.rows;
	int cols = srcImage.cols;
	Mat temImage;
	srcImage.convertTo(srcImage, CV_32FC1);
	temImage.create(srcImage.size(), CV_32FC1);
	//	temImage = srcImage;
		/*实现1
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			float tem = (float)srcImage.at<float>(i, j);
			float temMax = tem;

			float temTheta = thetaImage.at<float>(i, j);
			temTheta = temTheta * 180 / PI;
			float temTheta0 = temTheta;
			float temTheta1 = temTheta - 45;
			float temTheta2 = temTheta - 90;
			float temTheta3 = temTheta - 135;
			temTheta = fmin(abs(temTheta0), abs(temTheta1));
			temTheta = fmin(abs(temTheta), abs(temTheta2));
			temTheta = fmin(abs(temTheta), abs(temTheta3));
			if (temTheta == temTheta0)
			{
				temMax = srcImage.at<float>(i, j);
				float temMax1 = srcImage.at<float>(i, j - 1);
				float temMax2 = srcImage.at<float>(i, j + 1);
				if (temMax > temMax1 && temMax > temMax2)
					temImage.at<float>(i, j) = temMax;
				//cout << temMax << endl;
			}
			else if (temTheta == temTheta1)
			{
				temMax = srcImage.at<float>(i, j);
				float temMax1 = srcImage.at<float>(i - 1, j + 1);
				float temMax2 = srcImage.at<float>(i + 1, j - 1);
				if (temMax > temMax1 && temMax > temMax2)
					temImage.at<float>(i, j) = temMax;
				//cout << temMax << endl;
			}
			else if (temTheta == temTheta2)
			{
				temMax = srcImage.at<float>(i, j);
				float temMax1 = srcImage.at<float>(i - 1, j);
				float temMax2 = srcImage.at<float>(i + 1, j);
				if (temMax > temMax1 && temMax > temMax2)
					temImage.at<float>(i, j) = temMax;
				//cout << temMax << endl;
			}
			else if (temTheta == temTheta3)
			{
				temMax = srcImage.at<float>(i, j);
				float temMax1 = srcImage.at<float>(i - 1, j - 1);
				float temMax2 = srcImage.at<float>(i + 1, j + 1);
				if (temMax > temMax1 && temMax > temMax2)
					temImage.at<float>(i, j) = temMax;
				//cout << temMax << endl;
			}
		}

	}
*/
/*实现2*/
	float g1, g2, g3, g4;
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (abs(srcImage.at<float>(i, j) <= 4))
			{
				temImage.at<float>(i, j) = 0;
				continue;
			}
			else if (abs(thetaImage.at<float>(i, j) > 1))
			{
				g2 = srcImage.at<float>(i - 1, j);
				g4 = srcImage.at<float>(i + 1, j);
				if (thetaImage.at<float>(i, j) > 0)
				{
					g1 = srcImage.at<float>(i - 1, j - 1);
					g3 = srcImage.at<float>(i + 1, j + 1);
				}
				else
				{
					g1 = srcImage.at<float>(i - 1, j + 1);
					g3 = srcImage.at<float>(i + 1, j - 1);
				}
			}
			else
			{
				g2 = srcImage.at<float>(i, j - 1);
				g4 = srcImage.at<float>(i, j + 1);
				if (thetaImage.at<float>(i, j) > 0)
				{
					g1 = srcImage.at<float>(i - 1, j - 1);
					g3 = srcImage.at<float>(i + 1, j + 1);
				}
				else
				{
					g3 = srcImage.at<float>(i - 1, j + 1);
					g1 = srcImage.at<float>(i + 1, j - 1);
				}
			}
			float tem1 = abs(thetaImage.at<float>(i, j)) * g1
				+ (1 - abs(thetaImage.at<float>(i, j)) * g2);
			float tem2 = abs(thetaImage.at<float>(i, j)) * g3
				+ (1 - abs(thetaImage.at<float>(i, j)) * g4);

			if (srcImage.at<float>(i, j) >= tem1 && srcImage.at<float>(i, j) >= tem2)
			{
				temImage.at<float>(i, j) = srcImage.at<float>(i, j);
				c1++;
			}
			else
			{
				temImage.at<float>(i, j) = 0;
				c2++;
			}

		}
	}

	return temImage;
}
