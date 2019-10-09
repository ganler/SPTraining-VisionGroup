#include<iostream>
#include<stddef.h>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
void proportion_thresh(const cv::Mat& in ,cv::Mat& out,double max_val,double proportion)
{
    
    Mat tmp=in.reshape(1,1).clone();
    cv::sort(tmp, tmp, SORT_EVERY_ROW + SORT_DESCENDING);
    int num=(in.rows-1)*(in.cols-1)*proportion;
    double thresh=tmp.at<uchar>(num);  
    threshold(in,out,thresh,max_val,cv::THRESH_BINARY); 
    return ;
}
int main()
{
    Mat src=imread("test.jpg",cv::IMREAD_GRAYSCALE);    
    proportion_thresh(src,src,255,0.2);
    imshow("proportion_thresh-test",src);
    waitKey(0);
    return 0;
}
