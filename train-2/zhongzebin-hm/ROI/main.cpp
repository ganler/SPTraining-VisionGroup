#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
    Mat src;
    src=imread("../warning.png");
    bool fromCenter = false;
    Rect2d r = selectROI(src, fromCenter);
    Mat cut=src(r);
    imshow("cut",cut);
    waitKey(0);
    return 0;
}