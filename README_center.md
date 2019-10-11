# Find the Center of a Blob (Centroid)

[TOC]

在中学，我们学习了几何的中各种平面图形。找到标准平面图形的中心(几何中心)比较容易，如圆形，方形，三角形，椭圆形等。中心是几何名词，质心是物理名词。质心是针对实物体而言的，而几何中心是针对抽象几何体而言的，对于密度均匀标准形状的物体，质心和几何中心重合。

但是当要找到任意形状的质心时，就不那么容易了。

# 1.名词解释

## （1）blob

blob在机器视觉中是指图像中的具有相似颜色、纹理等特征所组成的一块连通区域。。在这篇文章中，我们的目标是在Python和C ++中使用OpenCV找到blob的中心。

## （2）质心

一个平面图形的质心是平面图形所有点的算术平均值（即平均值）。假设一个平面图形由n个点xi组成，那么质心由下式给出

![20190316154046561](/home/lisihang/桌面/20190316154046561.png)

在图像处理和计算机视觉领域中，每个平面图形由像素点构成，并且质心坐标为构成平面图形的所有像素点坐标的加权平均。

## （3）图像矩

在OpenCV，我们用blob来称呼平面图形。我们可以在OpenCV中使用图像矩找到blob的中心。图像矩是图像像素值的加权平均值，借助它我们可以找到图像的一些特定属性，如半径，面积，质心等。为了找到图像的质心，我们通常将其二值化然后找到它的质心。质心由下式给出： 

![20190316154046569](/home/lisihang/桌面/20190316154046569.png)

![20190316154046581](/home/lisihang/桌面/20190316154046581.png)

Cx是质心的x坐标，Cy是质心的y坐标。M表示图像几何矩。注意M00可能等于0

# 2.opencv-cpp找到Blob质心的步骤

要找到blob的质心，我们将执行以下步骤： -

1.将图像转换为灰度图。

2.对图像执行二值化。

3.计算图像矩后找到图像的中心。

~~~c++
#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
 
using namespace cv;
using namespace std;
 
 
int main()
{
	String img_path = "./image/circle.png";
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

~~~

效果如下图：

![20190316154210444](/home/lisihang/桌面/20190316154210444.png)

# 3.参考

https://blog.csdn.net/luohenyj/article/details/88599334

https://www.learnopencv.com/find-center-of-blob-centroid-using-opencv-cpp-python/

