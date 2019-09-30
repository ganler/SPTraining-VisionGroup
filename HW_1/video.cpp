#include "opencv2/opencv.hpp"
using namespace cv;
int main()
{
    VideoCapture cap;
    Mat image;
    cap.open("video.flv");
    while(cap.isOpened())
    {
        cap>>image;
        threshold(image,image,150,255,THRESH_BINARY);
        imshow("Jinitaimei",image);
        waitKey(30);
    }

}