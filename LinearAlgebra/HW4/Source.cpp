#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

using namespace std;
using namespace cv;

/*
reference:
findContours ( �M����� ): https://ppt.cc/fchOEx
contourArea ( �p��������n ): https://ppt.cc/fqIYtx
approxPolyDP ( �G����t ): https://ppt.cc/f0FApx
minAreaRect ( �̨���� ): https://ppt.cc/f45Axx
*/

/* ���w�Ѽ�
GaussianBlur(matrix, matrix, Size(5, 5), 0);
Canny(matrix, out_ matrix, 35, 125);
findContours(matrix, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
approxPolyDP(contours, contours_poly, 3, true);
*/

// ���o���n�̤j������
vector<Point> GetBiggestContours(vector<vector<Point>>& contours);
double Distance(Point2f& l, Point2f& r);

int main(int argc, char* argv[])
{
    Mat img = imread(argv[1]);

    // ��Ƕ�
    Mat gray;
    cvtColor(img, gray, CV_BGR2GRAY);

    // �����ҽk
    Mat Gauss;
    GaussianBlur(gray, Gauss, Size(5, 5), 0);

    Mat canny;
    Canny(Gauss, canny, 35, 125);

    // �����
    vector<vector<Point>> contours; // contours (n.) ����; �~��; ���u
    findContours(canny, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

    // ���o���n�̤j������
    auto MaxContours = GetBiggestContours(contours);

    // �G����t
    vector<Point> contours_poly;
    approxPolyDP(MaxContours, contours_poly, 3, true);

    // ���o�̨����
    auto rect = minAreaRect(contours_poly);
    Point2f boxPoints[4];
    rect.points(boxPoints);

    // �����e��
    auto width = Distance(boxPoints[0], boxPoints[3]);

    //// �J�Z -> 3752.24
    //auto fl = (width * 1500) / 210;

    auto l = (210 * 3752.24) / width;

    cout << l << '\n';
}

// ���o���n�̤j������
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