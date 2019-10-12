#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
int main( )
{
    Mat Image,BinaryImage;
    Image=imread("1.jpg",cv::IMREAD_GRAYSCALE);
    int  Image1[256]={0};
    uchar ThresholdVal;
    int num=0;
    for(int i=0;i<Image.cols;i++)
          for(int j=0;j<Image.rows;j++)
          {
              Image1[Image.at<uchar>(j+1,i+1)]++;//将像素值作为数组下标，记录同像素数量
          }
    for(int i=255;i>=0;i--)
             {num+=Image1[i];
             if(num>=int(Image.rows*Image.cols*(0.14)))
                      {ThresholdVal=i+1;
                      break;
                      }
             }

     threshold(Image,BinaryImage,ThresholdVal,255,THRESH_BINARY);
    imshow("imgae",BinaryImage);
    waitKey(0);
}