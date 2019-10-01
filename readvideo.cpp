#include<opencv2/opencv.hpp>
using namespace cv;
int main()
{
    Mat frame;
    VideoCapture video;
    video.open("../test.mp4");
    while (video.isOpened())
    {
        video >>frame;
        threshold(frame,frame,100,255,CV_THRESH_BINARY);
        imshow("test",frame);
        waitKey(30);
    }
    return 0;
}