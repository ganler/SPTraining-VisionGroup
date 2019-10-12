#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;
int main()
{
    // declare Mat variables, thr, gray and src
    Mat thr, gray, src;
    src = imread("/home/ubuntu/CLionProjects/3809112_163326051000_2.jpg");
// convert image to grayscale
    cvtColor( src, gray, COLOR_BGR2GRAY );//转化为灰度图

// convert grayscale to binary image
    threshold( gray, thr, 100,255,THRESH_BINARY );//二值化

// find moments of the image
    Moments m = moments(thr,true);//获得影像时间
    Point p(m.m10/m.m00, m.m01/m.m00);//通过图像矩计算图形中心

// coordinates of centroid
    cout<< Mat(p)<< endl; //得到中心点

// show the image with a point mark at the centroid//圈出中心点
    circle(src, p, 5, Scalar(128,0,0), -1);
    imshow("Image with center",src);
    waitKey(0);
}