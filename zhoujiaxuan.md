仔细看了图像质点位置计算与ROI感兴趣位置计算两篇链接文章，运行了相关代码，代码量不是很大，计算图像质点的方法与高数课上的积分求物体质心一样，感觉ROI选取感兴趣区域和物体追踪相关，对于代码中出现的各种opencv函数不是很了解，于是又去看了看opencv3入门书上的部分相关内容，书上内容也不多（没看完）。在网上搜索了ROI等相关内容，发现大多与物体的质心追踪法有关，通过ROI等知识圈定物体矩形区域，通过对区域计算质点并以质点来标记物体的位置，由于在比赛运动中可能出现被追踪物体部分被遮挡，这样通过部分来预测整体所在矩形区域并计算质点可以有标识物体，追踪物体。感觉这些算法代码中全是opencv的内部函数，啥也不会，还有不少物体追踪方面知识需要学习，由于只看了很少的一部分，这只是我非常浅的了解。

以下是求质点的代码与ROI拉取感兴趣区域代码：



\#include <opencv2/opencv.hpp>

\#include <iostream>

\#include <stdio.h>

\#include <stdlib.h>

 

using namespace cv;

using namespace std;

 

 

int main()

{

String img_path = "1.jpg";

Mat src, gray, thr;

src = imread(img_path);

 

// convert image to grayscale 获取灰度图

cvtColor(src, gray, COLOR_BGR2GRAY);

 

// convert grayscale to binary image 二值化

threshold(gray, thr, 0, 255, THRESH_OTSU);

 

// find moments of the image 提取二值图像矩，true表示图像二值化了

Moments m = moments(thr, true);

Point p(m.m10 / m.m00, m.m01 / m.m00);

 

// coordinates of centroid 质心坐标

cout << Mat(p) << endl;

 

// show the image with a point mark at the centroid 画出质心

circle(src, p, 5, Scalar(128, 0, 0), -1);

imshow("show", src);

waitKey(0);

return 0;

}





\#include <opencv2/opencv.hpp>

// selectROI is part of tracking API

\#include <opencv2/video/tracking.hpp>

 

using namespace std;

using namespace cv;

 

 

int main (int argc, char **arv)

{

​    // Read image

​    Mat im = imread("1.jpg");

​     

​    // Select ROI

bool showCrosshair = false; 

bool fromCenter = false; 

Rect2d r = selectROI("Image", im, fromCenter, showCrosshair);

​    // Crop image

​    Mat imCrop = im(r);

​    // Display Cropped Image

​    imshow("Image", imCrop);

​    waitKey(0);

​     

​    return 0;

}

 