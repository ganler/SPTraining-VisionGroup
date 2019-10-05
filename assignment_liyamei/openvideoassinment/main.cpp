#include<opencv2/opencv.hpp>
#include<iostream>
 
using namespace std;
using namespace cv;
 
int main(int argc,char **argv)
{

	cv::VideoCapture capture("/home/ming/git_yummy/l3/l2/test.avi");

    cv::Mat frame;
    while(1)
    {
        capture >> frame;
        if(frame.empty())
            break;
        cv::imshow("video",frame);

        char c=(char)waitKey(25);
        if(c==27)
            break;
    }
    capture.release();
    // Closes all the frames
    destroyAllWindows();
	return 0;

    /*打开一张图片
    Mat image = imread("/home/ming/git_yummy/l3/l2/test.jpg");
    imshow("123",image);
    waitKey(0);
    return 0;
    */
}
