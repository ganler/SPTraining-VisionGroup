## Key Word

Bob

Center

C++

## What is a bob

A group of connected pixels in an image that shares some common property.

## What is the centroid of a shape?

The weighted average of all the pixels constituting the shape.

## Single Blob

```c++
#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
    Mat thr, gray, src;
    src = imread("../图片/timg.jpeg");
    cvtColor(src, gray, COLOR_BGR2GRAY);
    threshold(gray, thr, 100, 255, THRESH_BINARY);
    Moments m = moments(thr, true);
    Point p(m.m10 / m.m00, m.m01 / m.m00);
    std::cout << Mat(p) << std::endl;
    circle(src, p, 5, Scalar(128, 0, 0), -1);
    imshow("Image with center", src);
    waitKey(0);
}
```

![](/home/jachinlin/SPTraining-VisionGroup/HW_2/single.jpg)

## Multiple Blobs

```c++
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
    Mat thr, gray, src;
    Mat canny_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    src=imread("../图片/timg (1).jpeg");
    cvtColor(src, gray, COLOR_BGR2GRAY);
    Canny(gray, canny_output, 50, 150, 3);
    findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    vector<Moments> mu(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        mu[i] = moments(contours[i], false);
    }
    vector<Point2f> mc(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
    }
    Mat drawing(canny_output.size(), CV_8UC3, Scalar(255, 255, 255));
    for (int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(167, 151, 0); // B G R values
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
        circle(drawing, mc[i], 4, color, -1, 8, 0);
    }
    namedWindow("Contours", WINDOW_AUTOSIZE);
    imshow("Contours", drawing);
    waitKey(0);
}

```

![](/home/jachinlin/SPTraining-VisionGroup/HW_2/Multiple.jpg)