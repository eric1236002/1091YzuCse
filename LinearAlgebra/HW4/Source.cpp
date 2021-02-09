#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

using namespace std;
using namespace cv;

/*
reference:
findContours ( 尋找輪廓 ): https://ppt.cc/fchOEx
contourArea ( 計算輪廓面積 ): https://ppt.cc/fqIYtx
approxPolyDP ( 逼近邊緣 ): https://ppt.cc/f0FApx
minAreaRect ( 最佳邊框 ): https://ppt.cc/f45Axx
*/

/* 指定參數
GaussianBlur(matrix, matrix, Size(5, 5), 0);
Canny(matrix, out_ matrix, 35, 125);
findContours(matrix, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
approxPolyDP(contours, contours_poly, 3, true);
*/

// 取得面積最大的輪廓
vector<Point> GetBiggestContours(vector<vector<Point>>& contours);
double Distance(Point2f& l, Point2f& r);

int main(int argc, char* argv[])
{
    Mat img = imread(argv[1]);

    // 轉灰階
    Mat gray;
    cvtColor(img, gray, CV_BGR2GRAY);

    // 高斯模糊
    Mat Gauss;
    GaussianBlur(gray, Gauss, Size(5, 5), 0);

    Mat canny;
    Canny(Gauss, canny, 35, 125);

    // 找輪廓
    vector<vector<Point>> contours; // contours (n.) 輪廓; 外型; 曲線
    findContours(canny, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

    // 取得面積最大的輪廓
    auto MaxContours = GetBiggestContours(contours);

    // 逼近邊緣
    vector<Point> contours_poly;
    approxPolyDP(MaxContours, contours_poly, 3, true);

    // 取得最佳邊框
    auto rect = minAreaRect(contours_poly);
    Point2f boxPoints[4];
    rect.points(boxPoints);

    // 像素寬度
    auto width = Distance(boxPoints[0], boxPoints[3]);

    //// 焦距 -> 3752.24
    //auto fl = (width * 1500) / 210;

    auto l = (210 * 3752.24) / width;

    cout << l << '\n';
}

// 取得面積最大的輪廓
vector<Point> GetBiggestContours(vector<vector<Point>>& contours)
{
    vector<Point> biggest;
    double _max = 0;
    for (auto& v : contours)
    {
        auto tmp = contourArea(v);
        if (tmp > _max) _max = tmp, biggest = v;
    }
    return biggest;
}

double Distance(Point2f& l, Point2f& r)
{
    double dx = r.x - l.x;
    double dy = r.y - l.y;
    return sqrt(dx * dx + dy * dy);
}