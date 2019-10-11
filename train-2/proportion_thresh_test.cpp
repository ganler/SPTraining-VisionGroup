#include<opencv2/opencv.hpp>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace cv;

void proportion_thresh(const cv::Mat& in, cv::Mat& out,double max_val,double proportion){
	std::vector<int> vec;
	const std::size_t iter_rows=in.isContinuous()? 1: in.rows;
	const std::size_t iter_cols=in.rows * in.cols / iter_rows * in.channels();
	for(std::size_t i=0; i<iter_rows; i++){
		const uchar *row_ptr=in.ptr<uchar>(i);
		for(std::size_t j=0;j<iter_cols;j++){
			vec.push_back(row_ptr[i*iter_cols+j]); 
		}
		sort(vec.begin(),vec.end());
		int all=in.rows * in.cols;
		int thresh=vec[all*proportion];
		std::cout<<thresh<<"\n";
		threshold(in,out,thresh,255,THRESH_BINARY);
	}
}

int main(){
	Mat image=imread("/home/ruolan/Desktop/1.jpg",0); //读图片的时候就单通道读了
	Mat image_out;
	proportion_thresh(image,image_out,255,0.1);
	imshow("test",image_out);
	waitKey(100);
	return 0;
}
