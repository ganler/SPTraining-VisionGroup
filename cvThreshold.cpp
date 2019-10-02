#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    cv::VideoCapture cap(0);
    if(!cap.isOpened())
    {
        std::cout<<"can't open the camera";
        return -1;
    }
    while(true)
    {
        cv::Mat frame,gray_frame;
        cap >> frame;
        cv::imshow("befor threshold",frame);
        cv::cvtColor(frame,gray_frame,COLOR_BGR2GRAY);
        cv::imshow("gray",gray_frame);
        cv::threshold(frame,frame,100,255,THRESH_BINARY);
        cv::threshold(gray_frame,gray_frame,100,255,THRESH_BINARY);
        /*threshold的第五个参数还有：
         THRESH_BINARY  当前点值大于阈值时，取Maxval,也就是第四个参数，否则设置为0
         THRESH_BINARY_INV 当前点值大于阈值时，设置为0，否则设置为Maxval
         THRESH_TRUNC 当前点值大于阈值时，设置为阈值，否则不改变
         THRESH_TOZERO 当前点值大于阈值时，不改变，否则设置为0
         THRESH_TOZERO_INV  当前点值大于阈值时，设置为0，否则不改变*/
        cv::imshow("after threshold",frame);
        cv::imshow("gray after threshold",gray_frame);
        waitKey(1);
    }
    return 0;
}