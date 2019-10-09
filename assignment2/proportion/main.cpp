#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>
#include "stddef.h"
using namespace std;
using namespace cv;

void proportion_thresh(cv::Mat &in,cv::Mat &out,double max_val,double proportion)
{
    //resize(in,in,{500, 400});//zoom in
    uchar* row_ptr;
    int iter_rows = in.isContinuous() ? 1 : in.cols;
    int iter_cols = in.cols * in.rows/iter_rows;
    for (int i = 0;i<iter_rows;++i)
    {
        row_ptr = in.ptr<uchar>(i);
        for (int j = 0; j < iter_cols; ++j)
        {
             row_ptr[i * iter_cols + j] = in.ptr<uchar>(i)[j];
        }
    }
    vector<uchar>a(row_ptr,row_ptr+in.cols * in.rows);
    sort(a.begin(),a.end());
    int b=a[proportion* in.cols * in.rows];
    cout<<"b="<<b<<endl;
    threshold(in,out,b,max_val,cv::THRESH_BINARY);
}
int main()
{
    auto mat = imread(
            "/home/ming/test.jpg",
            cv::IMREAD_GRAYSCALE);
    imshow("test1",mat);
    proportion_thresh(mat,mat,255,0.4);
    cv::imwrite("test2.jpg",mat);
    imshow("test2",mat);
    waitKey();
    return 0;
}


















