#include"sift.h"


void mySift(Mat srcImage, Mat& resultImage, int featureLevel)
{
	//建立高斯金字塔
	const int row = srcImage.rows;
	const int col = srcImage.cols;
	const int O = log2(min(row, col)) - 3;
	const int S = featureLevel + 3;
	const float baseSigma = 1.52;//经验值
	const float K = pow(2.0, 1.0 / (float)featureLevel);
	Mat srcTemImage = srcImage;
	cvtColor(srcTemImage, srcTemImage, COLOR_BGR2GRAY);
	srcTemImage.convertTo(srcTemImage, CV_32FC1);
	Mat **MatsPri = new Mat*[O]();
	Mat **DOGMatsPri = new Mat*[O]();
	Mat **featureMats = new Mat*[O]();
	for (int i = 0; i < O; i++)
		MatsPri[i] = new Mat[S]();
	for (int i = 0; i < O; i++)
		DOGMatsPri[i] = new Mat[S - 1]();
	for (int i = 0; i < O; i++)
		featureMats[i] = new Mat[featureLevel]();


	for (int j = 0; j < O; j++)
	{
		Mat* temMats = new Mat[S]();
		float temSigma = baseSigma * pow(2, j);
		for (int temk = 0; temk < S; temk++)
		{
			int temKernelSize = (20 * temSigma - 16) / 3 + 2;
			//cout << temSigma << " " << temKernelSize << " ";
			Mat temMat = MyGaussBlur(srcTemImage, temKernelSize, temSigma);
			temMat.convertTo(temMat, CV_32FC1);
			temMats[temk] = temMat;
			//cout << temMat.rows << " " << temMat.cols << endl;
			temSigma = temSigma * pow(K, (float)(temk + 1));
			//cout << K << " " << temk << endl;
		}
		
		MatsPri[j] = temMats;
		srcTemImage = resizeHalf(srcTemImage);
	}

	for (int i = 0; i < O; i++)
	{
		for (int j = 0; j < S - 1; j++)
		{
			DOGMatsPri[i][j] = MatsPri[i][j + 1] - MatsPri[i][j];
		}
	}
	int temScale = 1;
	for (int i = 0; i < O; i++)
	{
		int temRow = DOGMatsPri[i][1].rows;
		int temCol = DOGMatsPri[i][1].cols;
		float img_scale = 1.0 / (255 * 1);
		float deriv_scale = img_scale * 0.5;
		float second_deriv_scale = img_scale;
		float cross_deriv_scale = img_scale * 0.25;
		for (int j = 1; j < S - 2; j++)
		{
			featureMats[i][j - 1].create(Size(temCol, temRow), CV_32FC1);
			for (int k = 1; k < temRow - 1; k++)
			{
				for (int l = 1; l < temCol - 1; l++)
				{
					float temMax = abs(DOGMatsPri[i][j].at<float>(k, l));
					int temX = l;
					int temY = k;
					float temSigma = pow(baseSigma, j / S);
					if (abs(temMax) > 0.5 * 0.04 / featureLevel)//0.04经验值
					{
						
						for (int zz = 0; zz < 3; zz++)
						{
							for (int xx = 0; xx < 3; xx++)
							{
								for (int yy = 0; yy < 3; yy++)
								{
									temMax = fmax(temMax, DOGMatsPri[i][j - 1 + zz].at<float>(k - 1 + yy, l - 1 + xx));
								}
							}
						}
					}
					//三维插值处理
					if (temMax == DOGMatsPri[i][j].at<float>(k, l))
					{
						//还没有除以变化步长
						//Mat temEdgeX = getPartial(DOGMatsPri[i][j], 0);
						Mat temXHat;
						int count = 5;//标准迭代5次
						bool flag = false;
						float px = (DOGMatsPri[i][j].at<float>(k, l + 1) - DOGMatsPri[i][j].at<float>(k, l - 1)) * deriv_scale;
						float py = (DOGMatsPri[i][j].at<float>(k + 1, l) - DOGMatsPri[i][j].at<float>(k - 1, l)) * deriv_scale;
						float ps = (DOGMatsPri[i][j + 1].at<float>(k, l) - DOGMatsPri[i][j - 1].at<float>(k, l)) * deriv_scale;
						Mat pfpx = (Mat_<float>(3, 1) << px, py, ps);
						int rr = k, cc = l, ss = j;
						while (count--)
						{
							if (rr<1 || rr>temRow-2 || cc<1 || cc>temCol-2 || ss<0 || ss> S-2)
							{
								break;
							}
							float pxx = (DOGMatsPri[i][j].at<float>(rr, cc + 1) + DOGMatsPri[i][j].at<float>(rr, cc - 1)
								- 2 * DOGMatsPri[i][j].at<float>(rr, cc)) * second_deriv_scale;
							float pyy = (DOGMatsPri[i][j].at<float>(rr + 1, cc) + DOGMatsPri[i][j].at<float>(rr - 1, cc)
								- 2 * DOGMatsPri[i][j].at<float>(rr, cc)) * second_deriv_scale;
							float pss = (DOGMatsPri[i][j + 1].at<float>(rr, cc) + DOGMatsPri[i][j - 1].at<float>(rr, cc)
								- 2 * DOGMatsPri[i][j].at<float>(rr, cc)) * second_deriv_scale;
							float pxy = (DOGMatsPri[i][j].at<float>(rr + 1, cc + 1) - DOGMatsPri[i][j].at<float>(rr + 1, cc - 1)
								- DOGMatsPri[i][j].at<float>(rr - 1, cc + 1) + DOGMatsPri[i][j].at<float>(rr - 1, cc - 1))
								* cross_deriv_scale;
							float pxs = (DOGMatsPri[i][j + 1].at<float>(rr + 1, cc) - DOGMatsPri[i][j - 1].at<float>(rr + 1, cc)
								- DOGMatsPri[i][j + 1].at<float>(rr - 1, cc) + DOGMatsPri[i][j - 1].at<float>(rr - 1, cc))
								* cross_deriv_scale;
							float psy = (DOGMatsPri[i][j + 1].at<float>(rr, cc + 1) - DOGMatsPri[i][j + 1].at<float>(rr, cc - 1)
								- DOGMatsPri[i][j - 1].at<float>(rr, cc + 1) + DOGMatsPri[i][j - 1].at<float>(rr, cc - 1))
								* cross_deriv_scale;
							Mat pfpxx = (Mat_<float>(3, 3) <<
								pxx, pxy, pxs,
								pxy, pyy, psy,
								pxs, psy, pss);
							invert(pfpxx, pfpxx);
							temXHat = pfpxx * pfpx;
							if (temXHat.at<float>(0) < 0.5 && temXHat.at<float>(1) < 0.5 && temXHat.at<float>(2) < 0.5)
							{
								flag = true;
								break;
							}
							rr += -round(temXHat.at<float>(1));
							cc += -round(temXHat.at<float>(0));
							ss += -round(temXHat.at<float>(2));
								
						}
						if (flag)
						{
							float x = temXHat.at<float>(0);
							float y = temXHat.at<float>(1);
							float sigma = temXHat.at<float>(2);
							float temmmm = 0.5 * (x * px + y * py + sigma * ps);
							featureMats[i][j - 1].at<float>(k, l) = abs(DOGMatsPri[i][j].at<float>(k, l) + temmmm);
							//cout << DOGMatsPri[i][j].at<float>(k, l) << " " << temmmm << endl;
						}
						else
						{
							featureMats[i][j - 1].at<float>(k, l) = 0.;
						}
						//featureMats[i][j - 1].at<float>(k, l) = temMax;
					}
					else
					{
						featureMats[i][j - 1].at<float>(k, l) = 0.;
					}
						
				}
			}
			
		}
	}

	//测试查看关键点
	/*
	for (int i = 0; i < O; i++)
	{
		for (int j = 1; j < S - 2; j++)
		{
			
			Mat jhn = featureMats[i][j-1];
			jhn = jhn;
			imshow("0,0", jhn);
			waitKey();
			destroyAllWindows();
		}
	}
	*/

	///确定关键点方向

	
}