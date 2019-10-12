What is a blob?
A blob is a group of connected pixels in an image that shares some common property.

What is the centroid of a shape?
In the context of image processing and computer vision, each shape is made of pixels, and the centroid is simply the weighted average of all the pixels constituting the shape.

Steps for finding Centroid of a Blob in OpenCV
To find the center of the blob, we will perform the following steps:-

1. Convert the Image to grayscale.

2. Perform Binarization on the Image.

3. Find the center of the image after calculating the moments.


#include <opencv2/opencv.hpp>
#include <iostream>


int main()
{
    using namespace std;
    using namespace cv;
    Mat a,b,c;

    //读取图像
    a=imread("../timg.jpeg");

    //转化为灰度图
    cvtColor(a, b, COLOR_BGR2GRAY);

    //二值化
    threshold(b,c,100,255,THRESH_BINARY);
    
    //计算二值化后的矩
    Moments m=moments(c,true);
    Point p(m.m10/m.m00,m.m01/m.m00);

    //显示出中心坐标
    cout<<Mat(p)<<endl;

    //在原图上显示出质心
    circle(a,p,5,Scalar(128,0,0),1);
    imshow("123",a);

    waitKey();
    return 0;
}
