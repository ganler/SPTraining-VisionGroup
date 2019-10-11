#include<opencv2/opencv.hpp>
#include<iostream>
int nums[256] = { 0 };  //定义一个数组用来计算各个像素值的数量，因为像素是0-255 所以数组大小为256 初始化为0
#define H 200     
#define W 200
template <typename Func>
inline void transform(cv::Mat& src, Func&& func)
{
	const std::size_t iter_rows = src.isContinuous() ? 1 : src.rows;
	const std::size_t iter_cols = src.rows*src.cols/iter_rows*src.channels();

	for (std::size_t i = 0; i < iter_rows; i++)
	{
		const auto row_ptr = src.ptr<uchar>(i);
		for (std::size_t j = 0; j < iter_cols; j++)
			func(row_ptr[i*iter_cols + j]);
	}
}
void func(uchar a)   //该函数用于计数
{
	nums[int(a)]++;           
}


int main()
{
	using namespace cv;
	int S = 0,x=255;    //x是像素值255  下面while循环递减
	auto mat = imread("GT.jpg", cv::IMREAD_GRAYSCALE);   //得到灰度图
	resize(mat, mat, { W,H });
	transform(mat, func);
	imshow("Test1", mat);   //show灰度图
	  
	while(1)
	{
		S = S + nums[x];           //S求和数量
		if (S >= 0.4*W*H)       //这边的0.4就是比例
			break;
		x--;
	}
	threshold(mat, mat, x, 255, cv::THRESH_BINARY);
	imshow("Test2", mat);
	
	waitKey();
	

	return 0;
}


