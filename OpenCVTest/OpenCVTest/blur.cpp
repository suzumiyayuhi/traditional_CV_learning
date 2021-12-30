#include"blur.h"
#include<stdlib.h>
#include<cstring>
#include<cmath>
#define PI 3.1415926535898

float** CreateGaussKernel(int kernelSize, float sigma)
{
	int tem = kernelSize / 2;
	float** out = new float*[kernelSize];
	for (int i = 0; i < kernelSize; i++)
		out[i] = new float[kernelSize]();
	float temSum = 0;
	for (int i = 0; i < kernelSize; i++)
	{
		float x2 = pow(i - tem, 2);
		for (int j = 0; j < kernelSize; j++)
		{
			float y2 = pow(j - tem, 2);
			out[i][j] = exp(-(x2 + y2) / 2 / sigma / sigma) / 2 / sigma / sigma / PI;
			temSum = temSum + out[i][j];
		}
	}
	for (int i = 0; i < kernelSize; i++)
	{
		for (int j = 0; j < kernelSize; j++)
		{
			out[i][j] /= temSum;
		}
	}
	return out;
}

float** CreateGaussDerivativeKernel(int kernelSize, float sigma)
{
	int tem = kernelSize / 2;
	float** out = new float* [kernelSize];
	for (int i = 0; i < kernelSize; i++)
		out[i] = new float[kernelSize]();
	float temSum = 0;
	for (int i = 0; i < kernelSize; i++)
	{
		float x2 = pow(i - tem, 2);
		for (int j = 0; j < kernelSize; j++)
		{
			float y2 = pow(j - tem, 2);
			out[i][j] = exp(-(x2 + y2) / 2 / sigma / sigma) *
				(x2 + y2 - 2 * sigma * sigma) / pow(sigma, 4);
			temSum = temSum + out[i][j];
		}
	}
	for (int i = 0; i < kernelSize; i++)
	{
		for (int j = 0; j < kernelSize; j++)
		{
			out[i][j] /= temSum;
		}
	}
	return out;
}

Mat MyGaussBlur(Mat srcImage, int kernelSize, float sigma)
{
	int rows = srcImage.rows;
	int cols = srcImage.cols;
	float** GaussMask = CreateGaussKernel(kernelSize, sigma);
	Mat out;
	out.create(srcImage.size(), CV_32FC1);
	for (int i = kernelSize / 2; i < rows - kernelSize / 2; i++)
	{
		for (int j = kernelSize / 2; j < cols - kernelSize / 2; j++)
		{
			float temSum = 0;
			for (int k = 0; k < kernelSize; k++)
			{
				for (int l = 0; l < kernelSize; l++)
				{
					temSum += srcImage.at<float>(i - kernelSize / 2 + k, j - kernelSize / 2 + l) *
						GaussMask[k][l];
				}
			}
			out.at<float>(i,j) = temSum;
		}
	}
	out.convertTo(out, CV_8UC1);
	delete []GaussMask;
	return out;
}

Mat MyGaussDerivativeBlur(Mat srcImage, int kernelSize, float sigma)
{
	int rows = srcImage.rows;
	int cols = srcImage.cols;
	float** GaussMask = CreateGaussDerivativeKernel(kernelSize, sigma);
	Mat out;
	out.create(srcImage.size(), CV_32FC1);
	for (int i = kernelSize / 2; i < rows - kernelSize / 2; i++)
	{
		for (int j = kernelSize / 2; j < cols - kernelSize / 2; j++)
		{
			float temSum = 0;
			for (int k = 0; k < kernelSize; k++)
			{
				for (int l = 0; l < kernelSize; l++)
				{
					temSum += srcImage.at<float>(i - kernelSize / 2 + k, j - kernelSize / 2 + l) *
						GaussMask[k][l];
				}
			}
			out.at<float>(i, j) = temSum;
		}
	}
	out.convertTo(out, CV_8UC1);
	delete []GaussMask;
	return out;
}

Mat LaplaceFliter(Mat srcImage)
{
	float mask[3][3] = { {0,-1,0},{-1,4,-1},{0,-1,0} };
	int rows = srcImage.rows;
	int cols = srcImage.cols;
	Mat out;
	out.create(srcImage.size(), CV_32FC1);
	int temSum = 0;
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					temSum += srcImage.at<float>(i + k - 1, j + l - 1) * mask[k][l];
					//cout << k << " " << l << endl;
				}
				//cout << temSumX << " " << temSumY << " " << temSum << endl;
			}
			temSum = fmax(temSum, 0);
			out.at<float>(i, j) = temSum;
			temSum = 0;
		}
	}/**/

	return out;
}

Mat LOGFliter(Mat srcImage, int kernelSize)
{
	//й╣ож1
	/*
	float sigma = ((kernelSize - 1) * 0.5 - 1) * 0.3 + 0.8;
	Mat temRes = MyGaussBlur(srcImage, kernelSize, sigma);
	temRes.convertTo(temRes, CV_32FC1);
	return LaplaceFliter(temRes);*/
	
	/**/
	float sigma = ((kernelSize - 1) * 0.5 - 1) * 0.3 + 0.8;
	int tem = kernelSize / 2;
	float** mask = new float* [kernelSize];
	for (int i = 0; i < kernelSize; i++)
		mask[i] = new float[kernelSize]();
	float temSum = 0;
	for (int i = 0; i < kernelSize; i++)
	{
		float x2 = pow(i - tem, 2);
		for (int j = 0; j < kernelSize; j++)
		{
			float y2 = pow(j - tem, 2);
			mask[i][j] = exp(-(x2 + y2) / 2 / sigma / sigma) *
				(1 - (x2 + y2) / 2 / sigma / sigma) *
				(-1 / CV_PI / pow(sigma, 4));
			//temSum = temSum + out[i][j];
		}
	}
	/*
	for (int i = 0; i < kernelSize; i++)
	{
		for (int j = 0; j < kernelSize; j++)
		{
			cout << mask[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl << endl;
	*/
	Mat out;
	out.create(srcImage.size(), CV_32FC1);
	int rows = out.rows;
	int cols = out.cols;
	for (int i = kernelSize / 2; i < rows - kernelSize / 2; i++)
	{
		for (int j = kernelSize / 2; j < cols - kernelSize / 2; j++)
		{
			float temSum = 0;
			for (int k = 0; k < kernelSize; k++)
			{
				for (int l = 0; l < kernelSize; l++)
				{
					temSum += srcImage.at<float>(i - kernelSize / 2 + k, j - kernelSize / 2 + l) *
						mask[k][l];
				}
			}
			out.at<float>(i, j) = temSum;
		}
	}
	//out.convertTo(out, CV_8UC1);
	delete []mask;
	return out;
	


	/*
	float mask[5][5] = {
		{0,0,0,0,0},
		{0,0,-1,0,0},
		{0,-1,4,-1,0},
		{0,0,-1,0,0},
		{0,0,0,0,0} };
	float** gaussMask = CreateGaussKernel(3, 3);
	for (int i = 1; i < 4; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			float temSum = 0;
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					temSum += mask[i - 3 / 2 + k][j - 3 / 2 + l] * gaussMask[k][l];
				}
			}
			mask[i][j] = temSum;
		}
	}
	int rows = srcImage.rows;
	int cols = srcImage.cols;
	Mat out;
	out.create(srcImage.size(), CV_32FC1);
	float temSum = 0;
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					temSum += srcImage.at<float>(i + k - 1, j + l - 1) * mask[k + 1][l + 1];
					//cout << k << " " << l << endl;
				}
				//cout << temSumX << " " << temSumY << " " << temSum << endl;
			}
			temSum = fmax(temSum, 0);
			out.at<float>(i, j) = temSum;
			temSum = 0;
		}
	}

	out.convertTo(out, CV_8UC1);
	imshow("LogFiliter", out);
	waitKey(0);
	destroyAllWindows();
	return out;*/

}

Mat DOGFliter(Mat srcImage, int kernelSize, float sigma1, float sigma2)
{
	Mat tem1 = MyGaussBlur(srcImage, kernelSize, sigma1);
	Mat tem2 = MyGaussBlur(srcImage, kernelSize, sigma2);
	tem1.convertTo(tem1, CV_32FC1);
	tem2.convertTo(tem2, CV_32FC1);
	Mat tem3 = tem2 - tem1;
	return tem3;
}
