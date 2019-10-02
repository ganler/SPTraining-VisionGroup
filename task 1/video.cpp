#include<opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
int main()
{
   Mat image; 
   Mat inimage;
   Mat Gray;
   VideoCapture bunny("../big_buck_bunny.mp4");
   
    while(bunny.isOpened())
    {
        bunny>>image;
        cvtColor(image, Gray, CV_BGR2GRAY,1);
        threshold(Gray,inimage,150,255,THRESH_BINARY);
        imshow("test",inimage);
        waitKey(20);}
    }

