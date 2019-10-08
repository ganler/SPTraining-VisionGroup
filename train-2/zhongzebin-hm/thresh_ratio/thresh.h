//
// Created by zhongzebin on 2019/10/7.
//
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;
#ifndef HOMEWORK1_TIMER_H
#define HOMEWORK1_TIMER_H
class thresh
{
public:
    Mat proportion_thresh(Mat src,int ratio)
    {
        cvtColor(src,src,COLOR_BGR2GRAY);
        const int iter_rows=src.isContinuous() ? 1:src.rows;
        const int iter_cols=src.rows*src.cols/iter_rows*src.channels();
        vector<uchar> pixels;
        for(int i=0;i<iter_rows;i++)
        {
            const auto row_ptr=src.ptr<uchar>(i);
            for(int j=0;j<iter_cols;j++)
            {
                uchar value=row_ptr[i*iter_cols+j];
                pixels.push_back(value);
            }
        }
        sort(pixels.begin(),pixels.end());
        int thresh=pixels[int(pixels.size()*ratio/100)];
        threshold(src,src,thresh,255,CV_THRESH_BINARY);
        return src;
    }
};
#endif //HOMEWORK1_TIMER_H
