#include"resize.h"

Mat resizeHalf(Mat srcImage)
{
	int row = srcImage.rows;
	int col = srcImage.cols;
	Mat out = Mat::zeros(Size(col / 2 + 1, row / 2 + 1), CV_32FC1);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (i % 2 == 0 && j % 2 ==0)
			{
				out.at<float>(i / 2, j / 2) = srcImage.at<float>(i, j);
			}
		}
	}
	return out;
}