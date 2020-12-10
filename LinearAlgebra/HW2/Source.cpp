#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

using namespace std;
using namespace cv;

/*
Reference:
	霍夫直線檢測: https://ppt.cc/fSXfIx
	計算斜率: https://www.itread01.com/content/1547635163.html
	旋轉圖片: https://www.itread01.com/articles/1476043874.html
*/

// get longest line's slope
double getSlope(vector<Vec4i>& lines)
{
	double _max = 0, tmp;
	Vec4i V;

	for (auto& l : lines)
	{
		tmp = norm(Point(l[2], l[3]) - Point(l[0], l[1]));
		if (tmp > _max) _max = tmp, V = l;
	}

	return atan((double)(V[3] - V[1]) / (double)(V[2] - V[0])) * 180 / CV_PI;
}

int main(int argc, char* argv[])
{
	if (argc < 3) return -1;

	// read image
	Mat Image = imread(argv[1], -1);
	if (Image.empty()) return -1;

	// 轉成灰階，彩色圖片沒有這一步會錯誤
	Mat gray;
	cvtColor(Image, gray, CV_BGR2GRAY);

	// get canny matrix
	Mat canny;
	Canny(gray, canny, 500, 100, 3);

	// get hough lines
	vector<Vec4i> Lines;
	HoughLinesP(canny, Lines, 1, CV_PI / 180, 250, 200, 10);

	double slope = getSlope(Lines);
	slope += (slope > 0) ? -90 : 90;

	// get center and rotation matrix
	Size sz = Image.size();
	Point2f center(sz.width / 2., sz.height / 2.);
	Mat rotMat = getRotationMatrix2D(center, slope, 1.0);

	// rotate
	Mat result;
	warpAffine(Image, result, rotMat, sz);

	imwrite(argv[2], result);
}