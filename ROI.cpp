#include <iostream>

#include <opencv2/opencv.hpp>
// selectROI is part of tracking API


using namespace std;
using namespace cv;


int main (int argc, char **arv)
{
    // Read image
    Mat im = imread("/home/ubuntu/CLionProjects/3809112_163326051000_2.jpg");

    // Select ROI
    Rect2d r = selectROI(im); // 选择矩形区域

    // Crop image
    Mat imCrop = im(r);// 画出矩形区域

    // Display Cropped Image
    imshow("Image", imCrop);// 展示有矩形的图片
    waitKey(0);

    return 0;
}