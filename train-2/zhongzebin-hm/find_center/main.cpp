#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
    Mat src,org;
    src=imread("../timg.jpeg");
    src.copyTo(org);
    cvtColor(src,src,COLOR_BGR2GRAY);
    threshold(src,src,100,255,THRESH_BINARY);
    Moments m = moments(src,true);
    Point p(m.m10/m.m00, m.m01/m.m00);
    circle(org, p, 5, Scalar(128,0,0), -1);
    imshow("center",org);
    waitKey(0);
}
