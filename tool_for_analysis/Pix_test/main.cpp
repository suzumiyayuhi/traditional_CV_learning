#include"base.h"

using namespace std;
using namespace cv;

const string BASE_DIR = "../../images\\";

const string BASE_DIR_04 = BASE_DIR + "04\\";
const string DIR_04_SRC_TRAIN = BASE_DIR_04 + "train\\";
const string DIR_04_SRC_VAL = BASE_DIR_04 + "val_fixed\\";
const string DIR_04_SRC_TRAIN_LABEL = BASE_DIR_04 + "label\\train\\";
const string DIR_04_SRC_VAL_LABEL = BASE_DIR_04 + "label\\val_fixed\\";

map<int, Scalar> dictScalar;
int CLASS_COUNT = 0;

void RegionTest(const char* srcStr)
{
	ClickRegionGrowDrawRec(srcStr);
}

Mat DrawRecForSingleImg(const char* srcStr)
{
	Mat srcImg = imread(srcStr);

	stack<Rect> Rects;
	Mat dstImg = srcImg.clone();
	Mat flagMat = Mat::zeros(srcImg.size(), CV_8UC1);
	int rows = srcImg.rows;
	int cols = srcImg.cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Scalar tem = srcImg.at<Vec3b>(i, j);
			if (tem != Scalar(0, 0, 128) || flagMat.at<uchar>(i, j) == 1)
				continue;
			Rects.push(GetRegionGrowRec(srcImg, Point2i(j, i), flagMat));
		}
	}
	while (!Rects.empty())
	{
		rectangle(dstImg, Rects.top(), Scalar(255, 255, 255));
		Rects.pop();
	}
	return dstImg;
}

stack<string> GenerateYOLORecDataForSingle(const char* srcStr)
{
	string strOut;
	stack<string> strStack;
	Mat srcImg = imread(srcStr);
	int ClassNumber = 0;
	stack<Rect> Rects;
	stack<int> ClassStack;
	Mat dstImg = srcImg.clone();
	Mat flagMat = Mat::zeros(srcImg.size(), CV_8UC1);
	int rows = srcImg.rows;
	int cols = srcImg.cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Scalar tem = srcImg.at<Vec3b>(i, j);
			if (tem == Scalar(0, 0, 0) || flagMat.at<uchar>(i, j) == 1)
				continue;
			bool temFlag = false;
			for (map<int, Scalar>::iterator it = dictScalar.begin(); it != dictScalar.end(); it++)
			{
				if (it->second == tem)
				{
					ClassNumber = it->first;
					temFlag = true;
					break;
				}
			}
			if (!temFlag)
			{
				ClassNumber = CLASS_COUNT;
				dictScalar.insert(pair<int, Scalar>(CLASS_COUNT, tem));
				//cout << CLASS_COUNT << "\t\t\t" << tem << endl;
				CLASS_COUNT++;
			}
			ClassStack.push(ClassNumber);
			Rects.push(GetRegionGrowRec(srcImg, Point2i(j, i), flagMat));
		}
	}
	while (!Rects.empty())
	{
		Rect temRect = Rects.top();
		ClassNumber = ClassStack.top();
		ClassStack.pop();
		Rects.pop();
		double centerX = (temRect.x + temRect.width) / 2.0;
		double centerY = (temRect.y + temRect.height) / 2.0;

		ostringstream os;
		os << ClassNumber << " " << centerX / cols << " " << centerY / rows
			<< " " << (double)temRect.width / (double)cols
			<< " " << (double)temRect.height / (double)rows << endl;
		strOut = os.str();
		strStack.push(strOut);
		//cout << strOut;
	}

	return strStack;
}

void GenerateYOLOData(string src)
{
	vector<string> files;
	glob(src + "*.png", files);
	for (int i = 0; i < files.size(); i++)
	{

		stack<string> strStack = GenerateYOLORecDataForSingle(files[i].c_str());
		string outputDir = src + "Enhance";
		const char* imgName = strrchr(files[i].c_str(), '\\');
		string imgName1 = imgName;
		imgName1 = imgName1.substr(0, imgName1.rfind("."));
		//const char* imgId = strrchr(imgName, '.');
		outputDir = outputDir + imgName1 + ".txt";
		ofstream ofs(outputDir, ios::app);
		while (!strStack.empty())
		{
			ofs << strStack.top();
			strStack.pop();
		}
		ofs.close();
	}
}

Mat ChangePatchCrackLabel(const char* srcStr)
{
	Mat srcImg = imread(srcStr);

	Mat dstImg = srcImg.clone();
	Mat flagMat = Mat::zeros(srcImg.size(), CV_8UC1);
	int rows = srcImg.rows;
	int cols = srcImg.cols;
	int count = 0;
	for (int i = 1; i < rows - 1; i++)
	{
		for (int j = 1; j < cols - 1; j++)
		{
			if (srcImg.at<Vec3b>(i, j) != Vec3b(0, 0, 128) || flagMat.at<uchar>(i, j) == 1)
				continue;
			if (srcImg.at<Vec3b>(i - 1, j) == Vec3b(128, 0, 128) ||
				srcImg.at<Vec3b>(i + 1, j) == Vec3b(128, 0, 128) ||
				srcImg.at<Vec3b>(i, j - 1) == Vec3b(128, 0, 128) ||
				srcImg.at<Vec3b>(i, j + 1) == Vec3b(128, 0, 128))
				count++;
			if (count > 20)
			{
				dstImg = RegionGrowChangePatchCrackLabel(dstImg, Point(j, i), flagMat);
				count = 0;
			}

		}
	}

	return dstImg;
}

void AddPatchCrackAsNewClass(string src)
{
	vector<string> files;
	glob(src + "*.png", files);
	for (int i = 0; i < files.size(); i++)
	{
		//Mat out = DrawRecForSingleImg(files[i].c_str());
		Mat out = ChangePatchCrackLabel(files[i].c_str());
		string outputDir = src + "Enhance";
		const char* imgName = strrchr(files[i].c_str(), '\\');
		outputDir = outputDir + imgName;
		imwrite(outputDir, out);
	}
}

int main(int argc, char** argv)
{
	//HMODULE hMod = LoadLibrary(L"opencv_world453.lib");
	//HMODULE hMod1 = LoadLibrary(L"opencv_world453d.lib");

	/*	*/
	if (argc > 1)
	{
		int flag;
		cin >> flag;
		if (flag == 0)
			RegionTest(argv[1]);
		else
		{
			imshow("dd", DrawRecForSingleImg(argv[1]));
			//imshow("dd", ChangePatchCrackLabel(argv[1]));

			waitKey();
		}
		//PaperTest(argv[1]);
	}
	else
	{
		//string src = DIR_04_SRC_TRAIN_LABEL;
		string src = DIR_04_SRC_VAL_LABEL;
		//AddPatchCrackAsNewClass(src);
		GenerateYOLOData(src);
	}

	//FreeLibrary(hMod);
	//FreeLibrary(hMod1);
	return 0;
}
