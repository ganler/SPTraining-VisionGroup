#include <opencv2/highgui/highgui.hpp>   
#include <opencv2/imgproc/imgproc.hpp>   
#include <opencv2/core/core.hpp>  
#include<stdc-predef.h>
#include<opencv2/opencv.hpp>
#include<vector>
#include<iostream>
      
using namespace cv; 

int Flip(Mat &img)
{
   int counter[256]={0};
   int t,Thres=0;
   int s=0;
   Mat_<uchar>::iterator it=img.begin<uchar>();
   Mat_<uchar>::iterator itend=img.end<uchar>();
   itend--;  //通过end成员函数得到的迭代器已超出集合，所以在这里自减
   for(;it!=itend;it++)
    {
       t=int(*it);
       counter[t]=counter[t]+1;
    } 
    for(int i=0;i<=255;i++){
        s=s+counter[i];
    }
    s=s*0.4;
    for(int i=0;i<=255;i++){
        s=s-counter[i];
        if(s<=0) {
            Thres=i;
            break;
            }
    }
    return Thres;
}
      
 int main(int argc, char** argv)  
    {  
        Mat frame,binary,binaryinv;  
        frame=imread("1.jpeg");
            imshow("原图像", frame);
            
            cv::cvtColor(frame,binary,COLOR_BGR2GRAY);//将原图转换为灰度图

            int rows=binary.rows;
            int cols=binary.cols;
            //unsigned s=abs(rows*cols*0.4);
            //int Thres=0;
            /*for(int i=0; i<rows; i++){
               for(int j=0; j<cols/2; j++){
                  
                }
            }*/
            //Flip(binary);
            cv::threshold(binary,binary,Flip(binary),255,THRESH_BINARY);//大于阈值的部分被置为255，小于部分被置为0 
            cv::imshow("binary",binary);
            
            waitKey(6000);
 
        return 0;  
}
