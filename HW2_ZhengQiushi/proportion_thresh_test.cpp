#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv/cv.hpp>

using namespace std;
using namespace cv;

int PixelThreshold(Mat inputImage, double percentage) {//返回百分比所对应的像素阀值
    int p[256]={0};
    int size = inputImage.cols * inputImage.rows;//总像素数目
    Mat_<uchar>::iterator it = inputImage.begin<uchar>();//指向首元素
    Mat_<uchar>::iterator itend = inputImage.end<uchar>();//指向尾元素
    for (; it != itend; it++) {//所有元素按照0-255的像素值进入数组
        p[(*it)] ++;
    }
    int i=255;
    for (int j=size; j > size * (1 - percentage);j--) {//从高向低依次减
        if (p[i] > 0)
            p[i]--;
        else
            i--;
    }
    return i;
}

int main(){
    int thresholdImage;
    Mat srcImage = imread("//home//zheng//CLionProjects//untitled//1.jpeg");
    Mat grayImage,binImage;
    if(!srcImage.data){
        cout<<"not find!"<<endl;
        return 0;
    }
    imshow("original",srcImage);

    cvtColor(srcImage,grayImage,CV_BGR2GRAY);
    imshow("gray",grayImage);

    thresholdImage=PixelThreshold(grayImage,0.4);
    threshold(grayImage,binImage,thresholdImage,255,CV_THRESH_BINARY);

    imshow("result",binImage);
    waitKey(0);

}


