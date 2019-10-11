# Opencv----ROI(region of interest)

在图像处理领域，常常需要设置感兴趣区域来专注或者简化工作过程，也就是从图像中选择一个图像区域，这个区域是图像分析所关注的重点。我们圈定这个区域，以便进行进一步的处理。

定义ROI区域有两种办法：

1. 使用表示矩形区域Rect。它指定的左上角坐标（构造函数的前两个参数）和矩形的长宽（构造函数的后两个函数），来定义一个矩形区域：

   ~~~c++
   Mat imageROI;
   imageROI = image(Rect(500,250,loge.cols,loge.rows))
   ~~~

   

2. 另一种定义ROI的方式是指定感兴趣行或者列的范围（Range）。Range是从起始索引到终止索引（不包括）的一段连续序列。

   `imageROI = image(Range(250,250+logeImage.rows),Range(200,200+logeImage.cols));`

   

下面通过一个图像掩膜（mask），直接将插入处的像素设置为logo图像的像素值，这样效果会很逼真

~~~c++
#include <opencv2/opencv.hpp>
using namespace cv;
 
 
#define WINDOW_NAME "图像掩膜混合效果"
 
 
//ROI_AddImage()函数，利用感兴趣区域RIO实现图像叠加
int main() {
	//读入图像
	Mat srcImage1 = imread("dota.jpg");
	Mat logoImage = imread("dota_logo.jpg");
	if (!srcImage1.data) {
		printf("读取srcImage1错误！\n"); 
		return -1;//或exit(1);使程序完全退出，返回到操作系统
	}
	if (!logoImage.data) {
		printf("读取logoImage错误！\n");
		return -1;
	}
	//定义一个Mat类型并给其设定ROI区域
	Mat imageROI = srcImage1(Rect(560, 240, logoImage.cols, logoImage.rows));
	//加载掩膜（必须是灰度图）
 
 
	Mat mask = imread("dota_logo.jpg", 0);
	//Mat mask = logoImage.clone();
	//Mat mask(imageROI.rows, imageROI.cols, imageROI.depth(), Scalar(1));
 
 
	//将掩膜复制到ROI
	logoImage.copyTo(imageROI, mask);//mask可以实现蒙板的功能
	//显示结果
	namedWindow(WINDOW_NAME);
	imshow(WINDOW_NAME, srcImage1);
	waitKey(0);
	return 0;
}

~~~

下面是使用mask与否的区别:

<1>使用mask即：执行logoImage.copyTo(imageROI, mask); 

运行结果：

![20180714162705507](/home/lisihang/桌面/20180714162705507.png)

<2>不使用mask即：执行logoImage.copyTo(imageROI); 直接将logo像素复制到ROI区域

运行结果：

![20180714163730710](/home/lisihang/桌面/20180714163730710.png)

