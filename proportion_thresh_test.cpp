#include<opencv2/opencv.hpp>
#include<iostream>
int nums[256] = { 0 };  //����һ���������������������ֵ����������Ϊ������0-255 ���������СΪ256 ��ʼ��Ϊ0
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
void func(uchar a)   //�ú������ڼ���
{
	nums[int(a)]++;           
}


int main()
{
	using namespace cv;
	int S = 0,x=255;    //x������ֵ255  ����whileѭ���ݼ�
	auto mat = imread("GT.jpg", cv::IMREAD_GRAYSCALE);   //�õ��Ҷ�ͼ
	resize(mat, mat, { W,H });
	transform(mat, func);
	imshow("Test1", mat);   //show�Ҷ�ͼ
	  
	while(1)
	{
		S = S + nums[x];           //S�������
		if (S >= 0.4*W*H)       //��ߵ�0.4���Ǳ���
			break;
		x--;
	}
	threshold(mat, mat, x, 255, cv::THRESH_BINARY);
	imshow("Test2", mat);
	
	waitKey();
	

	return 0;
}


