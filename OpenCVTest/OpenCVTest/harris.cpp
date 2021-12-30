#include"harris.h"

Mat Harris(Mat srcImage,int kernelSize)
{
	/*Opencv测试对比
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	srcImage.convertTo(srcImage, CV_8UC1);
	Mat temImage;

	cornerHarris(srcImage, temImage, 3, 3, 0.01);
	for (int i = 1; i < temImage.rows - 1; i++)
	{
		for (int j = 1; j < temImage.cols - 1; j++)
		{
			//cout << temImage.at<float>(i, j) << " ";
			temImage.at<float>(i, j) *= 100;
			//if (temImage.at<float>(i, j) < 100)
				//temImage.at<float>(i, j) = 0;
		}
		//cout << endl;
	}
	//temImage.convertTo(temImage, CV_8UC1);

	imshow("harris", temImage);
	waitKey();
	destroyAllWindows();
	return temImage;
	*/
    cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	srcImage.convertTo(srcImage, CV_32FC1);
    
    float maskX[3][3] = { {1,0,-1},{2,0,-2},{1,0,-1} };
    float maskY[3][3] = { {1,2,1},{0,0,0},{-1,-2,-1} };
    int rows = srcImage.rows;
    int cols = srcImage.cols;
    Mat EdgeX, EdgeY, Edge, thetaImage, out;
    EdgeX.create(srcImage.size(), CV_32FC1);
    EdgeY.create(srcImage.size(), CV_32FC1);
    Edge.create(srcImage.size(), CV_32FC1);
    //out.zeros(srcImage.size(), CV_32FC1);
    out = srcImage;
    
    //sobel模版卷积
    for (int i = 1; i < rows - 1; i++)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            float temSumX = 0;
            float temSumY = 0;
            float temSum = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    temSumX += srcImage.at<float>(i + k - 1, j + l - 1) * maskX[k][l];
                    temSumY += srcImage.at<float>(i + k - 1, j + l - 1) * maskY[k][l];
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
            //thetaImage.at<float>(i, j) = atan(temSumX / temSumY);
        }
    }
    float **gaussMask = CreateGaussKernel(kernelSize, ((kernelSize - 1) * 0.5 - 1) * 0.3 + 0.8);
    for (int i = kernelSize / 2; i < rows - kernelSize / 2; i++)
    {
        for (int j = kernelSize / 2; j < cols - kernelSize; j++)
        {
            //建立临时矩阵计算M
            /*
            float** temMatrix = new float *[kernelSize];
            for (int i = 0; i < kernelSize; i++)
            {
                temMatrix[i] = new float[kernelSize]();
            }*/
            float temMatrix[2][2] = { 0,0,0,0 };
            for (int k = 0; k < kernelSize; k++)
            {
                for (int l = 0; l < kernelSize; l++)
                {
                    float IX = EdgeX.at<float>(i - kernelSize / 2 + k, j - kernelSize / 2 + l);
                    float IY = EdgeY.at<float>(i - kernelSize / 2 + k, j - kernelSize / 2 + l);
                    
                    temMatrix[0][0] += IX * IX;
                    temMatrix[0][1] += IX * IY;
                    temMatrix[1][0] += IX * IY;
                    temMatrix[1][1] += IY * IY;

                    for (int o = 0; o != 2; o++)
                    {
                        for (int p = 0; p != 2; p++)
                        {
                            temMatrix[o][p] *= gaussMask[k][l];
                        }
                    }

                }
            }
            float temDet = temMatrix[0][0] * temMatrix[1][1] - temMatrix[0][1] * temMatrix[1][0];
            float temTra = temMatrix[0][0] + temMatrix[1][1];
            float CK = 0.04;//经验值0.04-0.06
            float tem = temDet - CK * temTra * temTra;
            out.at<float>(i, j) = tem / 100000;
            //cout << out.at<float>(i, j) << endl;
        }
    }
    imshow("out", out);
    waitKey();
    destroyAllWindows();
    delete[]gaussMask;
    return out;
}