#include"image_enhance.h"
#include"base.h"
#define DLLEXPORT extern "C" __declspec(dllexport)

/*无参数图像增强方法，mode参数
* 0，直方图均衡化
* 1，拉普拉斯算子局部增强
* 2，log函数映射（非线性映射）
*/

Mat NoArgimageEnhance(Mat m, int mode)
{
	Mat res;
	if (mode == 0)
	{
		equalizeHist(m, res);
		return res;
	}
	else if (mode == 1)
	{
		Mat temMask = (Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
		filter2D(m, res, CV_8UC1, temMask);
		return res;
	}
	else if (mode == 2)
	{
		int c = 255 / log(256);
		res = m.clone();
		for (int i = 0; i < m.rows; i++)
		{
			for (int j = 0; j < m.cols; j++)
			{
				res.at<uchar>(i, j) = c * log(1 + res.at<uchar>(i, j));
			}
		}
		normalize(res, res, 0, 255, NORM_MINMAX);
		return res;
	}
	else
	{
		return m;
	}
}

Mat GammaMapping(Mat m, int gamma, int c)
{
	float temgamma = (float)gamma / 30.0;
	float temc = (float)c / 50.0;
	Mat res = m.clone();
	res.convertTo(res, CV_32FC1);
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			res.at<float>(i, j) = temc * pow(res.at<float>(i, j), temgamma);
		}
	}
	normalize(res, res, 0, 255, NORM_MINMAX);
	res.convertTo(res, CV_8UC1);
	return res;
}

Mat LinearWide(Mat m, int fa, int fb, int ga, int gb)
{
	Mat res = m.clone();
	float alpha = ga / fa;
	float beta = (gb - ga) / (fb - fa);
	float gamma = (255 - gb) / (255 - fb);
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			if (res.at<uchar>(i, j) < fa)
			{
				res.at<uchar>(i, j) = alpha * res.at<uchar>(i, j);
			}
			else if (res.at<uchar>(i, j) >= fa && res.at<uchar>(i, j) < fb)
			{
				res.at<uchar>(i, j) = beta * (res.at<uchar>(i, j) - fa) + ga;
			}
			else
			{
				res.at<uchar>(i, j) = gamma * (res.at<uchar>(i, j) - fb) + gb;
			}
		}
	}
	return res;
}

Mat MyAdaptiveThreshold_Binary(Mat m, int blockSize, int mode, int c)
{
	//mode参数
	/*
	* 0.领域均值
	* 1.领域高斯加权和
	*/
	Mat dst;
	if (blockSize <= 2)
		return m;
	if (blockSize % 2 == 0)
	{
		blockSize = blockSize + 1;
	}
	adaptiveThreshold(m, dst, 255, mode, THRESH_BINARY, blockSize, c);
	return dst;
}

Mat MyAdaptiveThreshold_ThCut(Mat m, int blockSize, int mode, int c)
{
	//mode参数
	/*
	* 0.领域均值
	* 1.领域高斯加权和
	*/
	Mat dst;
	if (blockSize <= 2)
		return m;
	if (blockSize % 2 == 0)
	{
		blockSize++;
	}
	adaptiveThreshold(m, dst, 50, mode, THRESH_BINARY, blockSize, c);
	return dst;
}

DLLEXPORT void EnhanceImageOutput(int dataSet, int flag)
{
	int gamma, c, fa, fb, ga, gb, blockSize;
	string DirIndex[6];
	DirIndex[0] = "0";
	DirIndex[1] = BASE_DIR_01;
	DirIndex[2] = DIR_02_SRC_CRACK;
	DirIndex[3] = DIR_04_SRC_TRAIN;
	DirIndex[4] = DIR_04_SRC_VAL;
	DirIndex[5] = DIR_05_SRC_SCRATCH;
	vector<string> files;
	glob(DirIndex[dataSet] + "*.bmp", files);
	int temss = files.size();

	if (flag == 0)
	{
		for (int i = 0; i < temss; i++)
		{
			Mat temm = imread(files[i]);
			cvtColor(temm, temm, COLOR_BGR2GRAY);
			Mat out = NoArgimageEnhance(temm, flag);
			string outputDir = DirIndex[dataSet] + "Enhance";
			const char* imgName = strrchr(files[i].c_str(), '\\');
			outputDir = outputDir + imgName;
			//cout << outputDir << endl;

			imwrite(outputDir, out);
		}
	}
	else if (flag == 1)
	{
		for (int i = 0; i < temss; i++)
		{
			Mat temm = imread(files[i]);
			cvtColor(temm, temm, COLOR_BGR2GRAY);
			Mat out = NoArgimageEnhance(temm, flag);
			string outputDir = DirIndex[dataSet] + "Enhance";
			const char* imgName = strrchr(files[i].c_str(), '\\');
			outputDir = outputDir + imgName;
			imwrite(outputDir, out);
		}
	}
	else if (flag == 2)
	{
		for (int i = 0; i < temss; i++)
		{
			Mat temm = imread(files[i]);
			cvtColor(temm, temm, COLOR_BGR2GRAY);
			Mat out = NoArgimageEnhance(temm, flag);
			string outputDir = DirIndex[dataSet] + "Enhance";
			const char* imgName = strrchr(files[i].c_str(), '\\');
			outputDir = outputDir + imgName;
			imwrite(outputDir, out);
		}
	}
	if (flag == 3)
	{
		cout << "input gamma and c\n";
		cin >> gamma >> c;
		for (int i = 0; i < temss; i++)
		{
			Mat temm = imread(files[i]);
			cvtColor(temm, temm, COLOR_BGR2GRAY);
			Mat out = GammaMapping(temm, gamma, c);
			string outputDir = DirIndex[dataSet] + "Enhance";
			const char* imgName = strrchr(files[i].c_str(), '\\');
			outputDir = outputDir + imgName;
			imwrite(outputDir, out);
		}
	}
	else if (flag == 4)
	{
		cout << "input fa fb ga gb\n";
		cin >> fa >> fb >> ga >> gb;
		for (int i = 0; i < temss; i++)
		{
			Mat temm = imread(files[i]);
			cvtColor(temm, temm, COLOR_BGR2GRAY);
			Mat out = LinearWide(temm, fa, fb, ga, gb);
			string outputDir = DirIndex[dataSet] + "Enhance";
			const char* imgName = strrchr(files[i].c_str(), '\\');
			outputDir = outputDir + imgName;
			imwrite(outputDir, out);
		}
	}
	else if (flag == 5 || flag == 6)
	{
		cout << "input blocksize and c\n";
		cin >> blockSize >> c;
		for (int i = 0; i < temss; i++)
		{
			Mat temm = imread(files[i]);
			cvtColor(temm, temm, COLOR_BGR2GRAY);
			Mat out = MyAdaptiveThreshold_Binary(temm, blockSize, 0, c);
			string outputDir = DirIndex[dataSet] + "Enhance";
			const char* imgName = strrchr(files[i].c_str(), '\\');
			outputDir = outputDir + imgName;
			imwrite(outputDir, out);
		}
	}
}
