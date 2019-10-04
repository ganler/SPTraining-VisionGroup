#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
int main(){
	VideoCapture capture(0);
	namedWindow("threshold",CV_WINDOW_AUTOSIZE);
	while(true)
	{	
		Mat image;
		capture>>image;
		//imshow("threshold",image);
		threshold(image,image,150,255,THRESH_BINARY);
		imshow("threshold",image);
		waitKey(30);
	}
	return 0;

}


