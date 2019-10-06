#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>  
#include "opencv2/videoio.hpp"

using namespace cv;
 
int main()
{
    VideoCapture capture(0);
    VideoWriter writer("video_original.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(640, 480));
    Mat frame;
    Mat edges;
 
    while (capture.isOpened())
    {
        capture >> frame;
        writer << frame;
        imshow("video_original", frame);
        if (cvWaitKey(20) >= 0)		//按回车键停止录制
        {
        	capture.release();
            break;
        }
    }

    VideoCapture readcap;
    readcap.open("video_original.avi");
    while (1)
    {
    	readcap>>frame;
    	if (frame.empty())
    		break;
    	cvtColor(frame,edges,CV_BGR2GRAY);		//灰度化
   		threshold(edges, edges, 120, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);   //二值化
    	imshow("video_binarization",edges);
    	if (waitKey(20)>=0)
    		break;
    }
    readcap.release();
    return 0;
}