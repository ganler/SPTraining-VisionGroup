 //(1)namespace局部命名空间可以有效避免项目协作时因函数等命名相同造成冲突
 /*(2)具体操作应该打包成函数，而且不能随意在函数过程中给变量赋值，如比例等，
 这样修改比较麻烦*/
 /*(3).at(j,i)访问制定行与列，但由于像素存储按行存储，而且存在行与行之间有距离
 与无距离两种情况，所以用.ptr(uchar)(i)访问每行首地址更准确*/
 //(4).at(j+1,i+1)是我错误的认为像素坐标是从（1，1）开始
 //(5)程序中定义过多变量，而且程序写的冗长，多是使用最基本的C++语句
 //看书不是太多，自己需要多看多学多用
#pragma once
#include <opencv2/opencv.hpp>
namespace  zjx
 {
     void prop_thre(cv::Mat& src_in,cv::Mat&src_out,double proproportion )
    {
    int  image1[256]={0},threshold_val=255;
    uint32_t iter_rows =src_in.isContinuous() ? 1 : src_in.rows;
    uint32_t iter_cols=src_in.rows*src_in.cols/iter_rows;

    for(size_t i=0;i<iter_rows;i++)
    {  auto row_ptr=src_in.ptr<uchar>(i);
        for(std::size_t j=0;j<iter_cols;++j)
                {++image1[*row_ptr++];}
    }
    int   num=iter_rows*iter_cols* proproportion;
    while(num>0)
            num-=image1[--threshold_val];
    
    threshold(src_in,src_out,threshold_val,255,cv::THRESH_BINARY);
    imshow("thre_im",src_out);
    cv::waitKey(0);
    }
 }

 
