#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap;
    cap.open(0);
    if(!cap.isOpened())
    {
        cout<<"cap open failed"<<endl;
    }
    while(1)
    {
        Mat src,gray,bin;
        cap>>src;
        imshow("src",src);
        cvtColor(src,gray,COLOR_BGR2GRAY);
        threshold(gray,bin,100,255,THRESH_BINARY);
        imshow("bin",bin);

        if(waitKey(33)>=0)
        {
            break;
        }
    }
    return 0;
}    