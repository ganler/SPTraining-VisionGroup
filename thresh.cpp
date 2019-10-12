#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;
void proportion_thresh(const cv::Mat& in ,cv::Mat& out,double max_val ,double proportion)
{

    vector<uchar> pic;
    cv::Mat image;

    cvtColor(in,image,CV_BGR2GRAY);
    const int iter_rows = image.isContinuous() ? 1:image.rows;
    const int iter_cols = image.rows*image.cols/iter_rows*image.channels();
    for (int row = 0; row < iter_rows; row++)      //行
    {
        for (int col = 0; col < iter_cols; col++)  //列
            {

                uchar value = image.at<uchar>(row,col);
                pic.push_back(value) ;
            }
    }
    sort(pic.begin(),pic.end());
    int thresh = pic[int(pic.size()*proportion)];
    threshold(image,out,thresh,max_val,CV_THRESH_BINARY);
    cv::imshow("out",out);
    waitKey(0);


}
int main()
{
    Mat in,out;
    in = imread("/home/ubuntu/CLionProjects/3809112_163326051000_2.jpg");
    proportion_thresh(in,out,255,0.4);
}

