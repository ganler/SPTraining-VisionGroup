//
// Created by lisihang on 2019/10/9.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

namespace sp
{
    void proportion_thresh(cv::Mat& gray_in, cv::Mat& out, double max_val, double proportion)
    {
        int row = gray_in.rows;
        int col = gray_in.cols;
        int grosse = row * col,num(0),z(0),pixel[256]={0};
        for(int i = 0; i < row; i++){
            const uchar* data = gray_in.ptr<uchar>(i);
            for(int j =0;j < col;j++)
                pixel[data[j]] = pixel[data[j]] + 1;
        }
        for(;num<=grosse * proportion;z++)
            num = num + pixel[z];
        std::cout<<z;
        for(int i = 0; i < row; i++){
            const uchar* data = gray_in.ptr<uchar>(i);
            for(int j =0;j < col;j++){
                if(int(data[j]) > z)
                    gray_in.at<uchar>(i,j) = max_val;
                else
                    gray_in.at<uchar>(i,j) = 0;
            }
        }
        out = gray_in;
    }
}

int main()
{
    Mat frame = imread("../1.png",0) ;
    Mat frame_out;
    sp::proportion_thresh(frame,frame_out,255,0.8);
    imshow("after",frame_out);
    waitKey(0);
    return 0;
}