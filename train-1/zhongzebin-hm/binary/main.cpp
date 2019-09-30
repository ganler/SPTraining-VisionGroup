#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
    VideoCapture cap;
    cap.open("../project_video.mp4");
    Mat frame;
    cap>>frame;
    while(!frame.empty())
    {
cout<<"2"<<endl;
        Mat gray;
        Mat binary;
        cvtColor(frame,gray,COLOR_BGR2GRAY);
        threshold(gray,binary,int(255/2),255,CV_THRESH_BINARY);
        imshow("video",binary);
        waitKey(10);
        cap>>frame;
    }
    cout<<"1"<<endl;
    return 0;
}
