#include"hough.h"

Mat myHough(Mat srcImage, Mat& thetaImage, int kernelSize, int sigma, int lowCannyThreshold, int highCannyThreshold, int houghThreshold, int flag)
{
	Mat cannyRes = myCanny(srcImage, thetaImage, kernelSize, sigma, lowCannyThreshold, highCannyThreshold);
	//Mat cannyRes = srcImage;
	imshow("Canny result", cannyRes);
	srcImage.convertTo(srcImage, CV_32FC1);
	int rows = cannyRes.rows;
	int cols = cannyRes.cols;
	Mat paraSpace;
	if(flag == 0)
		paraSpace = Mat::zeros(Size(rows + 1500, 181), CV_32FC1);
	else if (flag == 1)
		paraSpace = Mat::zeros(Size(2000, 1000), CV_32FC1);
	else
		paraSpace = Mat::zeros(Size(rows + 1500, 181), CV_32FC1);
//	Mat radiusSpace = Mat::zeros(paraSize, CV_32FC1);
	Mat houghRes = srcImage;
	
	
	if (flag == 0)//直线补全;ρ，θ空间
	{
		for (int i = 1; i < rows - 1; i++)
		{
			for (int j = 1; j < cols - 1; j++)
			{
				float tem = cannyRes.at<float>(i, j);
				if (tem < 1)
					continue;
				/*
				float theta = atan(i / j);
				if (theta < 0)
					theta = CV_PI / 2 - theta;
				float r = sqrt(pow(i, 2) + pow(j, 2));
				float rou = j * j / sqrt(pow(i, 2) + pow(j, 2)) + i * i / sqrt(pow(i, 2) + pow(j, 2));
				theta = theta * 180 / CV_PI;
				paraSpace.at<float>(round(theta), round(rou)) += 10.;*/

				for (int temTheta = 0; temTheta < 181; temTheta++)
				{
					float temThetaRadius = temTheta * CV_PI / 180;
					float rho = j * cos(temThetaRadius) + i * sin(temThetaRadius);
					rho = round(rho) + 1200;
					//cout << rho << "----------------" << temTheta << endl;
					paraSpace.at<float>(temTheta, rho) += 1;
					//	radiusSpace.at<float>(temTheta, rho) = sqrt(pow(i, 2) + pow(j, 2));
				}
			}
		}
		int paraRows = paraSpace.rows;
		int paraCols = paraSpace.cols;
		Mat houghRes = cannyRes.clone();
		for (int i = 1; i < paraRows - 1; i++)
		{
			for (int j = 1; j < paraCols - 1; j++)
			{
				if (paraSpace.at<float>(i, j) >= houghThreshold)
				{
					int p1_x = 0;
					int p1_y = (j - 1200) / sin(i * CV_PI / 180);
					int p2_x = (j - 1200) / cos(i * CV_PI / 180);
					int p2_y = 0;
					Point p1 = Point(p1_x, p1_y);
					Point p2 = Point(p2_x, p2_y);
					//cout << p1_x << " " << p1_y << " " << p2_x << " " << p2_y << endl << endl << endl;
					line(srcImage, p1, p2, Scalar(255, 255, 0), 1);
					//line(houghRes, p1, p2, Scalar(255), 2);
				}
			}
		}
	}

	if (flag == 1)//圆形补全;x0,y0,r空间
	{
		int*** paraSpace3D = new int** [rows];
		for (int i = 0; i < rows; i++)
		{
			paraSpace3D[i] = new int* [cols];
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				paraSpace3D[i][j] = new int[rows + cols]();
			}
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				for (int k = 0; k < cols + rows; k++)
				{
					paraSpace3D[i][j][k] = 0;
				}
			}
		}
		/*临时计算梯度方向以及梯度角*/
		int** temThetaSpace = new int* [rows];
		int** temGradiSpace = new int* [rows];
		for (int i = 0; i < rows; i++)
		{
			temThetaSpace[i] = new int[cols]();
			temGradiSpace[i] = new int[cols]();
		}	
		for (int i = 1; i < rows - 1; i++)
		{
			for (int j = 1; j < cols - 1; j++)
			{
				float lev = srcImage.at<float>(i, j);
				int flag = 2;//0,0';1,45';2,90';3,135'
				float temMax = 0;
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 3; l++)
					{
						if (abs(lev - srcImage.at<float>(i - 1 + k, j - 1 + l)) > temMax)
						{
							temMax = abs(lev - srcImage.at<float>(i - 1 + k, j - 1 + l));
							if ((k == 0 && l == 0) && (k == 2 && l == 2))
								flag = 3;
							else if ((k == 0 && l == 1) || (k == 2 && l == 1))
								flag = 2;
							else if ((k == 0 && l == 2) && (k == 2 && l == 0))
								flag = 1;
							else if (k==1 && l==1)
								continue;
							else
								flag = 0;
						}
					}
				}
				if (flag == 0)
				{
					temThetaSpace[i][j] = temMax;
					temGradiSpace[i][j] = 0;
				}
				else if (flag == 1)
				{
					temThetaSpace[i][j] = temMax;
					temGradiSpace[i][j] = CV_PI / 4;
				}
				else if (flag == 2)
				{
					temThetaSpace[i][j] = 0;
					temGradiSpace[i][j] = 0;
				}
				else if (flag == 3)
				{
					temThetaSpace[i][j] = temMax;
					temGradiSpace[i][j] = 3 * CV_PI / 4;
				}
			}
		}
		//_____________________________________________________
		// 
		// 
		//参数空间转换实现1，有问题
		/*
		for (int i = 1; i < rows - 1; i++)
		{
			for (int j = 1; j < cols - 1; j++)
			{
				float tem = cannyRes.at<float>(i, j);
				if (tem < 1)
					continue;
				for (int r = 0; r < 50; r++)
				{
					float temmm = temThetaSpace[i][j];
					if (temmm == 0 && temGradiSpace[i][j] == 0)
						continue;
					int x0 = j - r * j / cos(temmm);
					int y0 = i - r * i / sin(temmm);
					if (x0 > 0 && y0 > 0 && x0 < cols && y0 < rows)
					{
						paraSpace3D[y0][x0][r] += 1;
						paraSpace.at<float>(y0, x0) += 100;
						//cout << x0 << "____" << y0 << endl;
					}
				}
			}
		}*/
		
		//2号实现;x0,y0映射空间有些不对劲
		/*for (int i = 2; i < rows - 2; i++)
		{
			for (int j = 2; j < cols - 2; j++)
			{
				if (cannyRes.at<float>(i, j) < 3)
					continue;
				for (int r = 1; r < 20; r++)
				{
					for (int x0 = 1; x0 < cols - 1; x0++)
					{
						//int y0 = x0 * tan(temThetaSpace[i][j]) - j * tan(temThetaSpace[i][j]) + i;
						int y0 = x0 * tan(thetaImage.at<float>(i,j)) -
							j * tan(thetaImage.at<float>(i, j)) + i;
						//cout << x0 << "____" << y0 << "_____" << r << endl;
						
						if (x0 > 0 && y0 > 0 && x0 < cols && y0 < rows)
						{
							paraSpace.at<float>(y0, x0) += 1;
							paraSpace3D[y0][x0][r] += 1;
							//cout << x0 << "____" << y0 << endl;
						}
					}

				}
			}
		}*/

		
		//3号实现,小图硬币基本能用，大图几乎失效	
		/*for (int i = 2; i < rows - 2; i++)
		{
			for (int j = 2; j < cols - 2; j++)
			{
				if (cannyRes.at<float>(i, j) < 3)
					continue;
				
				for (int the = 0; the < 180; the++)
				{
					for (int r = 5; r < 150; r++)
					{
						float temThe = the * CV_PI / 180;
						int x0 = j + cos(temThe) * r;
						int y0 = i + sin(temThe) * r;
						if (x0 > 0 && y0 > 0 && x0 < cols && y0 < rows)
						{
							paraSpace3D[y0][x0][r] += 1;
							//cout << x0 << "____" << y0 << endl;
						}
						x0 = j - cos(temThe) * r;
						y0 = i - sin(temThe) * r;
						if (x0 > 0 && y0 > 0 && x0 < cols && y0 < rows)
						{
							paraSpace3D[y0][x0][r] += 1;
							//cout << x0 << "____" << y0 << endl;
						}
						//cout << endl << endl;
					}
					
				}
				
			}
		}*/

		//4号实现;半径和圆心精度缺了那么一点点
		/**/for (int i = 2; i < rows - 2; i++)
		{
			for (int j = 2; j < cols - 2; j++)
			{
				if (cannyRes.at<float>(i, j) < 3)
					continue;
				for (int r = 0; r < 50; r++)
				{
					for (int x0 = 1; x0 < cols - 1; x0++)
					{
						//int y0 = x0 * tan(temThetaSpace[i][j]) - j * tan(temThetaSpace[i][j]) + i;
						int y0 = i - sqrt(pow(r, 2) - pow(j - x0, 2));
						//cout << x0 << "____" << y0 << "_____" << r << endl;

						if (x0 > 0 && y0 > 0 && x0 < cols && y0 < rows)
						{
							paraSpace.at<float>(y0, x0) += 1;
							paraSpace3D[y0][x0][r] += 1;
							//cout << x0 << "____" << y0 << endl;
						}

						y0 = i + sqrt(pow(r, 2) - pow(j - x0, 2));
						if (x0 > 0 && y0 > 0 && x0 < cols && y0 < rows)
						{
							paraSpace.at<float>(y0, x0) += 3;
							paraSpace3D[y0][x0][r] += 1;
							//cout << x0 << "____" << y0 << endl;
						}
					}

				}
			}
		}

		//__________________________________________________

		srcImage.convertTo(srcImage, CV_8UC3);
		houghRes = srcImage;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				for (int k = 0; k < rows + cols; k++)
				{
					if (paraSpace3D[i][j][k] >= houghThreshold)
					{
						/*整体误差微调
						Point center = Point(j+5, i-8);
						//cout << i << "_____" << j << "_____"<< k << endl;
						circle(houghRes, center, k-4, Scalar(255, 255, 255));*/

						Point center = Point(j, i);
						//cout << i << "_____" << j << "_____"<< k << endl;
						circle(houghRes, center, k, Scalar(255, 255, 0));
					}
				}
			}
		}
	}
	

	paraSpace.convertTo(paraSpace, CV_8UC1);
	imshow("parameter space", paraSpace);
	imshow("hough result", houghRes);
	//imshow("ddd", srcImage);
	for (int i = 0; i < thetaImage.rows; i++)
	{
		for (int j = 0; j < thetaImage.cols; j++)
		{
			thetaImage.at<float>(i, j) = thetaImage.at<float>(i, j) / CV_PI * 180;
		}
	}
	//thetaImage.convertTo(thetaImage, CV_8UC1);
	//imshow("theta image", thetaImage);

	waitKey(0);
	destroyAllWindows();
	return cannyRes;
}