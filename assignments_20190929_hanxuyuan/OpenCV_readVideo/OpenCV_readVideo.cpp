#include "opencv2/opencv.hpp"

using namespace cv;

int main()
{
    VideoCapture cap("/home/hanxuyuan/Videos/201910021336330.mp4");
    Mat mat;
    for(;;)
    {
        cap >> mat;
        threshold(mat, mat, 150, 255, CV_THRESH_BINARY);
        imshow("Video", mat);
        if(waitKey(10) >= 0)
            break;
    }
    return 0;
}
