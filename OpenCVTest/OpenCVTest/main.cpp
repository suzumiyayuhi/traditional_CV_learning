#include"sharpening.h"
#include"blur.h"
#include"canny.h"
#include"hough.h"
#include"harris.h"
#include"sift.h"
#include<vector>
#include"resize.h"
#include<opencv2/features2d/features2d.hpp>
#include<chrono>
#include "main.h"

void PaperTest()
{
	//Mat srcImage = imread("images\\zi.png");
	//Mat srcImage = imread("images\\car_fog.png");
	Mat srcImage = imread("images\\sunflower.jpg");
	Mat grayImage = srcImage.clone();
	Mat imagePri[10];
	//cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	imshow("source grayImage", grayImage);

	grayImage.convertTo(grayImage, CV_32FC3);
	int cols = grayImage.cols;
	for (int i = 1; i < 11; i++)
	{
		float sigmaPara = i * 0.01 * cols;
		float gaussPara = 1 / (sigmaPara * powf(2 * CV_PI, 0.5)) * exp(-2 / 2 / pow(sigmaPara, 2));
		cout << gaussPara << endl;
		imagePri[i - 1] = grayImage * gaussPara;
	}
	for (int i = 0; i < 10; i++)
	{
		imagePri[i].convertTo(imagePri[i], CV_8UC3);
		//normalize(imagePri[i], imagePri[i], 255, NORM_MINMAX);
		imshow(to_string(i), imagePri[i] * 50);
	}
	waitKey();
	destroyAllWindows();
}

void temFunc()
{
	/*
	//sigma = ((ksize-1)*0.5 – 1)*0.3 + 0.8
	Mat srcImage = imread("images\\gray_sunflower.jpg");
	//Mat srcImage = imread("images\\coins.png");
	//Mat srcImage = imread("images\\car_fog_gray.jpg");
	//imshow("source image", srcImage);
	srcImage.convertTo(srcImage, CV_8UC1);
	imshow("src", srcImage);
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	srcImage.convertTo(srcImage, CV_32FC1);
	Mat tem = MyGaussDerivativeBlur(srcImage, 5, 3);
	Mat temRes = MyGaussBlur(srcImage, 5, 3);
	imshow("GaussDerivative", tem);
	imshow("Gauss", temRes);
	tem.convertTo(tem, CV_32FC1);
	waitKey();
	destroyAllWindows();
	*/

	/*
	Mat srcImage = imread("images\\coins.png");
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	srcImage.convertTo(srcImage, CV_8UC1);
	imshow("src", srcImage);
	srcImage.convertTo(srcImage, CV_32FC1);
	Mat tem = DOGFliter(srcImage, 3, 1, 1.01);
	imshow("tem", tem);
	waitKey();
	destroyAllWindows();*/

	/*
	float** temMask = CreateGaussDerivativeKernel(3, 3);
	for (int i = 0; i != 3; i++)
	{
		for (int j = 0; j != 3; j++)
		{
			cout << temMask[i][j] << " ";
		}
		cout << endl;
	}*/

	/*
	//Mat srcImage = imread("images\\coins.png");
	Mat srcImage = imread("images\\gray_sunflower.jpg");
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	srcImage.convertTo(srcImage, CV_32FC1);
	imshow("ddd", LOGFliter(srcImage, 8));
	waitKey();
	destroyAllWindows();*/

	/*隔点取样resize test
	//Mat srcImage = imread("images\\coins.png");
	Mat srcImage = imread("images\\gray_sunflower.jpg");
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	srcImage.convertTo(srcImage, CV_32FC1);
	Mat temImage = resizeHalf(srcImage);
	srcImage.convertTo(srcImage, CV_8UC1);
	temImage.convertTo(temImage, CV_8UC1);
	imshow("ddd1", srcImage);
	imshow("ddd2", temImage);
	waitKey();
	destroyAllWindows();*/
	Mat srcImage = imread("images\\sunflower_240p.jpg");
	int featureLevel = 2;
	const int row = srcImage.rows;
	const int col = srcImage.cols;
	const int O = log2(min(row, col)) - 3;
	const int S = featureLevel + 3;
	const float baseSigma = 1.52;//经验值
	const float K = pow(2.0, 1.0 / (float)featureLevel);
	Mat srcTemImage = srcImage;
	cvtColor(srcTemImage, srcTemImage, COLOR_BGR2GRAY);
	srcTemImage.convertTo(srcTemImage, CV_32FC1);
	Mat** MatsPri = new Mat * [O]();
	Mat** DOGMatsPri = new Mat * [O]();
	Mat** featureMats = new Mat * [O]();
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
			imshow("ss", temMat);
			waitKey();
			destroyAllWindows();
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
			imshow("DOG Pri", DOGMatsPri[i][j]);
			waitKey();
			destroyAllWindows();
		}
	}


}

void temHarrisTest()
{
	Mat srcImage = imread("images\\circles.png");
	Harris(srcImage, 3);
	/**/
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
}

void temSiftTest()
{
	/**/
	//Mat srcImage = imread("images\\gray_sunflower.jpg");
	//Mat srcImage = imread("images\\coins.png");
	//Mat srcImage = imread("images\\coins_240p.jpg");
	Mat srcImage = imread("images\\sunflower_240p_gray.jpg");
	Mat resultImage = srcImage;
	mySift(srcImage, resultImage, 2);
}

void temmmm()
{
	Mat img = imread("images//1.bmp");
	imshow("原始图", img);
	Mat DstPic, edge, grayImage;

	//创建与src同类型和同大小的矩阵
	DstPic.create(img.size(), img.type());

	//将原始图转化为灰度图
	cvtColor(img, grayImage, COLOR_BGR2GRAY);

	//先使用3*3内核来降噪
	blur(grayImage, edge, Size(3, 3));

	//运行canny算子
	Canny(edge, edge, 3, 9, 3);

	imshow("边缘提取效果", edge);
	waitKey(0);
	Mat cdst, cdst2;
	vector<Vec2f> lines;
	HoughLines(edge, lines, 1, CV_PI / 180, 100);
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);
		line(cdst2, pt1, pt2, Scalar(255, 255, 255), 1, LINE_AA);
	}
	for (int i = 0; i != lines.size(); i++)
	{
		cout << lines[i];
	}
	cdst.convertTo(cdst, CV_8UC1);
	cdst2.convertTo(cdst2, CV_8UC1);
	imshow("detected lines", cdst);
	imshow("detected lines2", cdst2);
	waitKey(0);
	destroyAllWindows();
}

void orbTest()
{
	Mat img1 = imread("images\\orb1.jpg");
	Mat img2 = imread("images\\orb2.jpg");

	vector<KeyPoint> keypoints_1, keypoints_2;
	Mat descriptors_1, descriptors_2;
	Ptr<FeatureDetector> detector = ORB::create();
	Ptr<DescriptorExtractor> descriptor = ORB::create();
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
	detector->detect(img1, keypoints_1);
	detector->detect(img2, keypoints_2);

	descriptor->compute(img1, keypoints_1, descriptors_1);
	descriptor->compute(img2, keypoints_2, descriptors_2);
	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
	chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	cout << "extract ORB cost = " << time_used.count() << " seconds. " << endl;

	Mat outimg1, outimg2;
	drawKeypoints(img1, keypoints_1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(img2, keypoints_2, outimg2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	imshow("ORB features1", outimg1);
	imshow("ORB features2", outimg2);

	vector<DMatch> matches;
	t1 = chrono::steady_clock::now();
	matcher->match(descriptors_1, descriptors_2, matches);
	t2 = chrono::steady_clock::now();
	time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	cout << "match ORB cost = " << time_used.count() << " seconds. " << endl;

	auto min_max = minmax_element(matches.begin(), matches.end(),
		[](const DMatch& m1, const DMatch& m2)
		{
			return m1.distance < m2.distance;
		});
	double min_dist = min_max.first->distance;
	double max_dist = min_max.second->distance;

	printf("-- Max dist : %f \n", max_dist);
	printf("-- Min dist : %f \n", min_dist);

	std::vector<DMatch> good_matches;
	for (int i = 0; i < descriptors_1.rows; i++)
	{
		if (matches[i].distance <= max(2 * min_dist, 30.0))
		{
			good_matches.push_back(matches[i]);
		}
	}

	Mat img_match;
	Mat img_goodmatch;
	drawMatches(img1, keypoints_1, img2, keypoints_2, matches, img_match);
	drawMatches(img1, keypoints_1, img2, keypoints_2, good_matches, img_goodmatch);
	imshow("all matches", img_match);
	imshow("good matches", img_goodmatch);
	waitKey();
}

int main(int argc, char* argv[])
{
	/*Canny Test
//  Mat srcImage = imread("images\\gray_sunflower.jpg");
	Mat srcImage = imread("images\\coins.png");
//  Mat srcImage = imread("images\\car_fog_gray.jpg");
//  imshow("source image", srcImage);
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	srcImage.convertTo(srcImage, CV_32FC1);

	Mat tem = MyGaussBlur(srcImage, 3, 1);
	imshow("gauss", tem);

	Mat dstImage;
	Mat thetaImage;
	dstImage.create(srcImage.size(), CV_8UC1);
	thetaImage.create(srcImage.size(), CV_32FC1);
	tem.convertTo(tem, CV_32FC1);

	Prewitt(tem, dstImage, thetaImage);
//    Sobel(tem, dstImage, thetaImage);
	imshow("dstImage", dstImage);
//    imshow("thetaImage", thetaImage);

	Mat nmsImage = NMS(dstImage, thetaImage, thetaImage);
	nmsImage.convertTo(nmsImage, CV_8UC1);
	imshow("Nms Image", nmsImage);

	nmsImage.convertTo(nmsImage, CV_32FC1);
	Mat resultImage = doubleThreshold(nmsImage, thetaImage, 10, 25);
	resultImage.convertTo(resultImage, CV_8UC1);
	imshow("result Image", resultImage);
	waitKey(0);
	destroyAllWindows();
 */



 //Canny整合至单函数
 /*
 Mat srcImage = imread("images\\gray_sunflower.jpg");
 //Mat srcImage = imread("images\\coins.png");
 Mat thetaImage;
 thetaImage.create(srcImage.size(), CV_32FC1);
 Mat res = myCanny(srcImage, thetaImage, 3, 3, 20, 90);    //双阈值实现4参数
 //Mat res = myCanny(srcImage, thetaImage, 3, 3, 15, 45); //双阈值实现3，NMS实现2
 res.convertTo(res, CV_8UC1);
 imshow("result Image", res);
 waitKey(0);
 destroyAllWindows();*/

 //Hough Test openCV实现
 /*
 //Mat srcImage = imread("images\\gray_sunflower.jpg");
 //Mat srcImage = imread("images\\coins.png");
 //Mat srcImage = imread("images\\car_fog_gray.jpg");
 Mat srcImage = imread("images\\shape.png");
 //imshow("source image", srcImage);
 Mat thetaImage;
 thetaImage.create(srcImage.size(), CV_32FC1);
 Mat temHoug = myCanny(srcImage, thetaImage, 3, 3, 20, 45);
 temHoug.convertTo(temHoug, CV_8UC1);
 imshow("result Image", temHoug);


 Mat cdst, cdst2;
 cdst = srcImage.clone();
 cdst2 = temHoug.clone();
 vector<Vec2f> lines;
 HoughLines(temHoug, lines, 1, CV_PI / 180, 100);
 for (size_t i = 0; i < lines.size(); i++)
 {
	 float rho = lines[i][0], theta = lines[i][1];
	 Point pt1, pt2;
	 double a = cos(theta), b = sin(theta);
	 double x0 = a * rho, y0 = b * rho;
	 pt1.x = cvRound(x0 + 1000 * (-b));
	 pt1.y = cvRound(y0 + 1000 * (a));
	 pt2.x = cvRound(x0 - 1000 * (-b));
	 pt2.y = cvRound(y0 - 1000 * (a));
	 line(cdst, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);
	 line(cdst2, pt1, pt2, Scalar(255, 255, 255), 1, LINE_AA);
 }
 for (int i = 0; i != lines.size(); i++)
 {
	 cout << lines[i];
 }
 cdst.convertTo(cdst, CV_8UC1);
 cdst2.convertTo(cdst2, CV_8UC1);
 imshow("detected lines", cdst);
 imshow("detected lines2", cdst2);
 waitKey(0);
 destroyAllWindows();
*/

//hough,线段
//NMS实现2，DT实现3
/*
//Mat srcImage = imread("images\\gray_sunflower.jpg");
//Mat srcImage = imread("images\\coins.png");
	Mat srcImage = imread("images\\shape.png");
	//Mat srcImage = imread("images\\chess_table.jpg");
	//imshow("source image", srcImage);
	Mat thetaImage;
	thetaImage.create(srcImage.size(), CV_32FC1);
	myHough(srcImage, thetaImage, 3, 3, 20, 100, 100, 0);
*/

//hough自行实现,针对小图硬币
//NMS实现3，DT实现4，ok
/*
//Mat srcImage = imread("images\\gray_sunflower.jpg");
//Mat srcImage = imread("images\\coins.png");
Mat srcImage = imread("images\\coins_240p.jpg");
//Mat srcImage = imread("images\\car_fog_gray.jpg");
//Mat srcImage = imread("images\\shape.png");
//imshow("source image", srcImage);
Mat thetaImage;
thetaImage.create(srcImage.size(), CV_32FC1);
myHough(srcImage, thetaImage, 3, 3, 40, 100, 17, 1);
*/
//hough自行实现,优化版,对大硬币
/*
//Mat srcImage = imread("images\\circle.png");
Mat srcImage = imread("images\\coins.png");
//Mat srcImage = imread("images\\coins_240p.jpg");
//Mat srcImage = imread("images\\car_fog_gray.jpg");
//Mat srcImage = imread("images\\shape.png");
//imshow("source image", srcImage);
Mat thetaImage;
thetaImage.create(srcImage.size(), CV_32FC1);
myHough(srcImage, thetaImage, 3, 3, 25, 45, 20, 1);
*/

//hough自行实现,优化版,对单一几何
/*
//Mat srcImage = imread("images\\circle.png");
Mat srcImage = imread("images\\circles.png");
//Mat srcImage = imread("images\\coins.png");
//Mat srcImage = imread("images\\coins_240p.jpg");
//Mat srcImage = imread("images\\car_fog_gray.jpg");
//Mat srcImage = imread("images\\shape.png");
//imshow("source image", srcImage);
Mat thetaImage;
thetaImage.create(srcImage.size(), CV_32FC1);
myHough(srcImage, thetaImage, 3, 3, 40, 100, 60, 1);*/

/*hough自行实现,优化版,瓶盖图
Mat srcImage = imread("images\\real_circles.jpg");
Size sz = srcImage.size();
sz.height *= 0.3; sz.width *= 0.3;
resize(srcImage, srcImage, sz);
//Mat srcImage = imread("images\\coins.png");
//Mat srcImage = imread("images\\coins_240p.jpg");
//Mat srcImage = imread("images\\car_fog_gray.jpg");
//Mat srcImage = imread("images\\shape.png");
//imshow("source image", srcImage);
Mat thetaImage;
imshow("srcImg", srcImage);
thetaImage.create(srcImage.size(), CV_32FC1);
myHough(srcImage, thetaImage, 3, 3, 40, 100, 31, 1);
*/

/*
//Mat srcImage = imread("images\\gray_sunflower.jpg");
//Mat srcImage = imread("images\\coins.png");
Mat srcImage = imread("images\\car_fog_gray.jpg");
//imshow("source image", srcImage);
cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
srcImage.convertTo(srcImage, CV_8UC1);
imshow("srcImage", srcImage);
srcImage.convertTo(srcImage, CV_32FC1);
Mat dstImage = LaplaceFliter(srcImage);
dstImage.convertTo(dstImage, CV_8UC1);
imshow("LaplaceFliter", dstImage);
//dstImage = LOGFliter(srcImage);
Mat dstImage1 = LOGFliter(srcImage);
dstImage1.convertTo(dstImage1, CV_8UC1);
imshow("Logfliter", dstImage1);
waitKey();
destroyAllWindows();
*/

//temFunc();
//temHarrisTest();
//temSiftTest();

/*
//Mat srcImage = imread("images\\gray_sunflower.jpg");
	Mat srcImage = imread("images\\coins.png");
	//Mat srcImage = imread("images\\chess_table.jpg");
	Mat tem = srcImage.clone();
	imshow("s", tem);
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	//srcImage.convertTo(srcImage, CV_32FC1);
	vector<KeyPoint>KeyPoints;
	auto fast = FastFeatureDetector::create();
	fast->detect(srcImage, KeyPoints);
	drawKeypoints(tem, KeyPoints, tem, Scalar(0, 0, 255));
	imshow("sss", tem);
	waitKey();
	destroyAllWindows();
*/
//PaperTest();
//orbTest();

//傅里叶频域图可视化
/*
	bool retflag;
	int retval = NewFunction(argv, retflag);
	if (retflag) return retval;
*/
	Mat srcImg = Mat::zeros(Size(300, 300), CV_8UC3);
	cvtColor(srcImg, srcImg, COLOR_BGR2GRAY);
	srcImg.convertTo(srcImg, CV_8UC1);
	for (int i = 50; i < 250; i++)
	{
		srcImg.at<uchar>(i, 100) = 250;
	}
	srcImg.convertTo(srcImg, CV_32FC1);

	Mat dstImg;
	Mat thetaImg = srcImg.zeros(srcImg.size(), CV_32FC1);
	Sobel(srcImg, dstImg, thetaImg);
	srcImg.convertTo(srcImg, CV_8UC1);
	imshow("dss", dstImg);
	imshow("ff", srcImg);
	waitKey();


	return 0;
}

int NewFunction(char* argv[], bool& retflag)
{
	retflag = true;
	cv::Mat src = cv::imread(argv[1]);
	cvtColor(src, src, COLOR_BGR2GRAY);
	if (!src.data)
	{
		std::cout << "Image Load Fail!!!" << "\n";
		return 1;
	}
	cv::imshow("SRC", src);

	//扩充图像尺寸到最佳尺寸，边界用0填充
	int r = cv::getOptimalDFTSize(src.rows);
	int c = cv::getOptimalDFTSize(src.cols);
	cv::Mat padded;
	cv::copyMakeBorder(src, padded, 0, r - src.rows, 0, c - src.cols,
		cv::BORDER_CONSTANT, cv::Scalar::all(0));

	//为傅里叶变换的结果（复数，包含实部和虚部，所以需要创建一个二维的数组）分配存储空间,
	//需要用至少float型来存储
	//最后将二维数组合并为二通道--傅里叶变换需要
	cv::Mat dst1[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F) };
	cv::Mat dst2;
	cv::merge(dst1, 2, dst2);

	//傅里叶变换,结果依旧存储在dst2中
	cv::dft(dst2, dst2);

	//将复数换算成幅值
	cv::split(dst2, dst1);//把二通道图像分解为二维数组，保存到dst1中,dst1[0]中存放的为实部
	cv::magnitude(dst1[0], dst1[1], dst1[0]);//结果存放在dst1[0]中
	cv::Mat magnitudeImage = dst1[0];


	//对数尺度缩放以便于显示
	//计算log(1 + sqrt(Re(DFT(dst2))**2 + Im(DFT(dst2))**2))
	magnitudeImage += cv::Scalar::all(1);
	cv::log(magnitudeImage, magnitudeImage);


	//剪切和重分布幅度图象限
	//若有奇数行或奇数列，进行频谱裁剪
	magnitudeImage = magnitudeImage(cv::Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));//任何一个数&-2的结果一定是偶数

																										//重新排列傅里叶图像的象限，使原点位于图像中心
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	cv::Mat q0(magnitudeImage(cv::Rect(0, 0, cx, cy)));
	cv::Mat q1(magnitudeImage(cv::Rect(cx, 0, cx, cy)));
	cv::Mat q2(magnitudeImage(cv::Rect(0, cy, cx, cy)));
	cv::Mat q3(magnitudeImage(cv::Rect(cx, cy, cx, cy)));

	cv::Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);


	//将幅度值归一化到0~1之间，这是因为magnitudeImage中的数据类型是浮点型，这时用imshow()来显示函数，会将像素值乘于255，因此需要归一化到0~1之间
cv:normalize(magnitudeImage, magnitudeImage, 0, 1, cv::NORM_MINMAX);

	//显示最后的频谱
	cv::imshow("spectrum magnitude", magnitudeImage);

	cv::waitKey();
	retflag = false;
	return {};
}
