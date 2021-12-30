#include"canny.h"

#define PI 3.1415926535898

Mat NMS(Mat srcImage, Mat& dstImage, Mat thetaImage)
{
	int c1 = 0, c2 = 0;
	int rows = srcImage.rows;
	int cols = srcImage.cols;
	Mat temImage;
	srcImage.convertTo(srcImage, CV_32FC1);
	temImage.create(srcImage.size(), CV_32FC1);
	//temImage = srcImage;
	//实现3
	/*
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			float tem = (float)srcImage.at<float>(i, j);
			float temMax = tem;

			float temTheta = thetaImage.at<float>(i, j);
			temTheta = (double)temTheta * 180 / PI;
			float temTheta0 = temTheta;
			float temTheta1 = temTheta - 45;
			float temTheta2 = temTheta - 90;
			float temTheta3 = temTheta - 135;
			temTheta = fmin(abs(temTheta0), abs(temTheta1));
			temTheta = fmin(abs(temTheta), abs(temTheta2));
			temTheta = fmin(abs(temTheta), abs(temTheta3));
			if (srcImage.at<float>(i, j) <= 5)
			{
				temImage.at<float>(i, j) = 0;
			}
			else if (temTheta == temTheta0)
			{
				temMax = srcImage.at<float>(i, j);
				float temMax1 = srcImage.at<float>(i - 1, j);
				float temMax2 = srcImage.at<float>(i + 1, j);
				if (temMax > temMax1 && temMax > temMax2)
					temImage.at<float>(i, j) = temMax;

				//cout << temMax << endl;
			}
			else if (temTheta == temTheta1)
			{
				temMax = srcImage.at<float>(i, j);
				float g1 = srcImage.at<float>(i - 1, j);
				float g2 = srcImage.at<float>(i + 1, j);
				float g3 = srcImage.at<float>(i - 1, j - 1);
				float g4 = srcImage.at<float>(i + 1, j + 1);
				float g5 = srcImage.at<float>(i, j - 1);
				float g6 = srcImage.at<float>(i, j + 1);
				float temMax1 = (g2 + g4) / 2;
				float temMax2 = (g1 + g3) / 2;
				float temMax3 = (g5 + g3) / 2;
				float temMax4 = (g6 + g4) / 2;
				if (temMax > temMax1 && temMax > temMax2 ||
					temMax > temMax3 && temMax > temMax4)
					temImage.at<float>(i, j) = temMax;
				//cout << temMax << endl;
			}
			else if (temTheta == temTheta2)
			{

				temMax = srcImage.at<float>(i, j);
				float temMax1 = srcImage.at<float>(i, j - 1);
				float temMax2 = srcImage.at<float>(i, j + 1);
				if (temMax > temMax1 && temMax > temMax2)
					temImage.at<float>(i, j) = temMax;
				//cout << temMax << endl;
			}
			else if (temTheta == temTheta3)
			{
				temMax = srcImage.at<float>(i, j);
				float g1 = srcImage.at<float>(i, j + 1);
				float g2 = srcImage.at<float>(i, j - 1);
				float g3 = srcImage.at<float>(i - 1, j + 1);
				float g4 = srcImage.at<float>(i + 1, j - 1);
				float g5 = srcImage.at<float>(i - 1, j);
				float g6 = srcImage.at<float>(i + 1, j);
				float temMax1 = (g2 + g4) / 2;
				float temMax2 = (g1 + g3) / 2;
				float temMax3 = (g5 + g3) / 2;
				float temMax4 = (g6 + g4) / 2;
				if (temMax > temMax1 && temMax > temMax2 ||
					temMax > temMax3 && temMax > temMax4)
					temImage.at<float>(i, j) = temMax;


				//cout << temMax << endl;
			}
		}

	}*/

	/*实现1
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			float tem = (float)srcImage.at<float>(i, j);
			float temMax = tem;

			float temTheta = thetaImage.at<float>(i, j);
			//temTheta = temTheta * 180 / PI;
			float temTheta0 = temTheta;
			float temTheta1 = temTheta - PI / 4;
			float temTheta2_1 = temTheta - PI / 2;
			float temTheta2_2 = temTheta + PI / 2;
			float temTheta3 = temTheta + PI / 4;
	//		cout << temTheta0 << " " << temTheta1 << " " << temTheta2_1 << " " << temTheta2_2 << " " << temTheta3 << endl;
			temTheta = fmin(abs(temTheta0), abs(temTheta1));
			temTheta = fmin(abs(temTheta), abs(temTheta2_1));
			temTheta = fmin(abs(temTheta), abs(temTheta2_2));
			temTheta = fmin(abs(temTheta), abs(temTheta3));
			if (srcImage.at<float>(i, j) <= 1)
			{
				temImage.at<float>(i, j) = 0;
			}
			else if (temTheta == temTheta0)
			{
				temMax = srcImage.at<float>(i, j);
				float temMax1 = srcImage.at<float>(i - 1, j);
				float temMax2 = srcImage.at<float>(i + 1, j);
				if (temMax > temMax1 && temMax > temMax2)
					temImage.at<float>(i, j) = temMax;
				//cout << temMax << endl;
			}
			else if (temTheta == temTheta1)
			{
				temMax = srcImage.at<float>(i, j);
				float temMax1 = srcImage.at<float>(i - 1, j - 1);
				float temMax2 = srcImage.at<float>(i + 1, j + 1);
				if (temMax > temMax1 && temMax > temMax2)
					temImage.at<float>(i, j) = temMax;
				//cout << i << " " << j << endl;
				//cout << temMax << endl;
			}
			else if (temTheta == temTheta2_1 || temTheta == temTheta2_2)
			{
				temMax = srcImage.at<float>(i, j);
				float temMax1 = srcImage.at<float>(i, j - 1);
				float temMax2 = srcImage.at<float>(i, j + 1);
				if (temMax > temMax1 && temMax > temMax2)
					temImage.at<float>(i, j) = temMax;

				cout << i << " " << j << endl;
				//cout << temMax << endl;
			}
			else if (temTheta == temTheta3)
			{

				temMax = srcImage.at<float>(i, j);
				float temMax1 = srcImage.at<float>(i - 1, j + 1);
				float temMax2 = srcImage.at<float>(i + 1, j - 1);
				if (temMax > temMax1 && temMax > temMax2)
					temImage.at<float>(i, j) = temMax;

			//	cout << i << " " << j << endl;
			}
		}

	}
*/
//实现2
	/**/float g1, g2, g3, g4;
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
				+ (1 - abs(thetaImage.at<float>(i, j))) * g2;
			float tem2 = abs(thetaImage.at<float>(i, j)) * g3
				+ (1 - abs(thetaImage.at<float>(i, j))) * g4;

			//tem1 = (g1 + g2)/2;
			//tem2 = (g3 + g4)/2;
			if (srcImage.at<float>(i, j) >= tem1 && srcImage.at<float>(i, j) >= tem2)
			{
				temImage.at<float>(i, j) = srcImage.at<float>(i, j);
			}
			else
			{
				temImage.at<float>(i, j) = 0;
			}

		}
	}


	return temImage;
}

Mat doubleThreshold(Mat srcImage, Mat thetaImage, int lowThreshold, int highThreshold)
{
	Mat outImg;
	outImg.create(srcImage.size(), CV_32FC1);
	int rows = srcImage.rows;
	int cols = srcImage.cols;

	//实现1
	/*
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (srcImage.at<float>(i, j) >= highThreshold)
			{
			//	outImg.at<float>(i, j) = srcImage.at<float>(i, j);
				outImg.at<float>(i, j) = 255;
			}
			else if (srcImage.at<float>(i, j) <= lowThreshold)
			{
				outImg.at<float>(i, j) = 0;
			}
			else
			{
				int dir[8][2] = { -1,-1,
				-1,0,
				-1,1,
				0,-1,
				0,1,
				1,-1,
				1,0,
				1,1 };
//				bool flag = false;
				for (int k = 0; k != 8; k++)
				{
					if (srcImage.at<float>(i + dir[k][0], j + dir[k][1]) > highThreshold)
					{
					//	outImg.at<float>(k, j) = srcImage.at<float>(k, j);
						outImg.at<float>(k, j) = 255;
					}
				}

			}
		}
	}
*/

//实现2
/*
for (int i = 1; i < rows - 1; i++)
{
	for (int j = 1; j < cols - 1; j++)
	{
		if (srcImage.at<float>(i, j) >= highThreshold)
		{
			//	outImg.at<float>(i, j) = srcImage.at<float>(i, j);
			outImg.at<float>(i, j) = 255;
		}
		else if (srcImage.at<float>(i, j) <= lowThreshold)
		{
			outImg.at<float>(i, j) = 0;
		}
		else
		{
			outImg.at<float>(i, j) = srcImage.at<float>(i, j);
		}
	}
}
*/
//实现3
/**/
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (srcImage.at<float>(i, j) >= highThreshold)
			{
				if (abs(thetaImage.at<float>(i, j) < 1))
				{
					if (srcImage.at<float>(i - 1, j) > lowThreshold)
						outImg.at<float>(i - 1, j) = highThreshold;
					if (srcImage.at<float>(i + 1, j) > lowThreshold)
						outImg.at<float>(i + 1, j) = highThreshold;
					if (thetaImage.at<float>(i, j) < 0)
					{
						if (srcImage.at<float>(i - 1, j - 1) > lowThreshold)
							outImg.at<float>(i - 1, j - 1) = highThreshold;
						if (srcImage.at<float>(i + 1, j + 1) > lowThreshold)
							outImg.at<float>(i + 1, j + 1) = highThreshold;
					}
					else
					{
						if (srcImage.at<float>(i - 1, j + 1) > lowThreshold)
							outImg.at<float>(i - 1, j + 1) = highThreshold;
						if (srcImage.at<float>(i + 1, j - 1) > lowThreshold)
							outImg.at<float>(i + 1, j - 1) = highThreshold;
					}
				}
				else
				{
					if (srcImage.at<float>(i, j - 1) > lowThreshold)
						outImg.at<float>(i, j - 1) = highThreshold;
					if (srcImage.at<float>(i, j + 1) > lowThreshold)
						outImg.at<float>(i, j + 1) = highThreshold;
					if (thetaImage.at<float>(i, j) < 0)
					{
						if (srcImage.at<float>(i - 1, j - 1) > lowThreshold)
							outImg.at<float>(i - 1, j - 1) = highThreshold;
						if (srcImage.at<float>(i + 1, j + 1) > lowThreshold)
							outImg.at<float>(i + 1, j + 1) = highThreshold;
					}
					else
					{
						if (srcImage.at<float>(i - 1, j + 1) > lowThreshold)
							outImg.at<float>(i + 1, j - 1) = highThreshold;
						if (srcImage.at<float>(i + 1, j - 1) > lowThreshold)
							outImg.at<float>(i + 1, j - 1) = highThreshold;
					}
				}

			}


		}
	}


	//实现4
	/*
		for (int i = 1; i < rows - 1; i++)
		{
			for (int j = 1; j < cols - 1; j++)
			{
				if (srcImage.at<float>(i, j) >= highThreshold)
				{
					//	outImg.at<float>(i, j) = srcImage.at<float>(i, j);
					outImg.at<float>(i, j) = 255;
				}
				else if (srcImage.at<float>(i, j) <= lowThreshold)
				{
					outImg.at<float>(i, j) = 0;
				}
				else
				{
					float temTheta = thetaImage.at<float>(i, j);
					temTheta = (double)temTheta * 180 / PI;
					float temTheta0 = temTheta;
					float temTheta1 = temTheta - 45;
					float temTheta2 = temTheta - 90;
					float temTheta3 = temTheta - 135;
					temTheta = fmin(abs(temTheta0), abs(temTheta1));
					temTheta = fmin(abs(temTheta), abs(temTheta2));
					temTheta = fmin(abs(temTheta), abs(temTheta3));

					if (temTheta == temTheta0)
					{
						float temMax1 = srcImage.at<float>(i - 1, j);
						float temMax2 = srcImage.at<float>(i + 1, j);
						if (temMax1 >= lowThreshold && temMax2 >= lowThreshold)
						{
							srcImage.at<float>(i, j) = highThreshold + 3;
							outImg.at<float>(i, j) = highThreshold;
						}
						//cout << temMax << endl;
					}
					else if (temTheta == temTheta1)
					{
						float g1 = srcImage.at<float>(i - 1, j);
						float g2 = srcImage.at<float>(i + 1, j);
						float g3 = srcImage.at<float>(i - 1, j - 1);
						float g4 = srcImage.at<float>(i + 1, j + 1);
						float g5 = srcImage.at<float>(i, j - 1);
						float g6 = srcImage.at<float>(i, j + 1);
						if (g1 >= lowThreshold || g2 >= lowThreshold ||
							g3 >= lowThreshold || g4 >= lowThreshold ||
							g5 >= lowThreshold || g6 >= lowThreshold)
						{
							srcImage.at<float>(i, j) = highThreshold + 3;
							outImg.at<float>(i, j) = highThreshold;
						}

						//cout << temMax << endl;
					}
					else if (temTheta == temTheta2)
					{

						float temMax1 = srcImage.at<float>(i, j - 1);
						float temMax2 = srcImage.at<float>(i, j + 1);
						if (temMax1 >= lowThreshold && temMax2 >= lowThreshold)
						{
							srcImage.at<float>(i, j) = highThreshold + 3;
							outImg.at<float>(i, j) = highThreshold;
						}
						//cout << temMax << endl;
					}
					else if (temTheta == temTheta3)
					{
						float g1 = srcImage.at<float>(i, j + 1);
						float g2 = srcImage.at<float>(i, j - 1);
						float g3 = srcImage.at<float>(i - 1, j + 1);
						float g4 = srcImage.at<float>(i + 1, j - 1);
						float g5 = srcImage.at<float>(i - 1, j);
						float g6 = srcImage.at<float>(i + 1, j);
						if (g1 >= lowThreshold || g2 >= lowThreshold ||
							g3 >= lowThreshold || g4 >= lowThreshold ||
							g5 >= lowThreshold || g6 >= lowThreshold)
						{
							srcImage.at<float>(i, j) = highThreshold + 3;
							outImg.at<float>(i, j) = highThreshold;
						}
						//cout << temMax << endl;
					}
				}
			}
		}
		*/


	return outImg;
}

Mat myCanny(Mat srcImage, Mat& thetaImage, int kernelSize, int sigma, int lowThreshold, int highThreshold)
{
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	srcImage.convertTo(srcImage, CV_32FC1);

	Mat gaussBlurImg = MyGaussBlur(srcImage, kernelSize, sigma);
	gaussBlurImg.convertTo(gaussBlurImg, CV_32FC1);
	Mat dstImage;
	dstImage.create(srcImage.size(), CV_32FC1);
	thetaImage.create(srcImage.size(), CV_32FC1);

	//Prewitt(gaussBlurImg, dstImage, thetaImage);
	Sobel(gaussBlurImg, dstImage, thetaImage);
	//imshow("sobel", dstImage);

	Mat nmsImage = NMS(dstImage, thetaImage, thetaImage);
	//imshow("nmsImage", nmsImage);
	Mat resultImage = doubleThreshold(nmsImage, thetaImage, lowThreshold, highThreshold);
	//imshow("canny result", resultImage);
	//waitKey();
	//destroyAllWindows();
	return resultImage;
}
