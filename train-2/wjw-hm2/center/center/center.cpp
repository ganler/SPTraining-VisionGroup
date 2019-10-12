#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
int main()
{
	//declare Mat variables,thr,gray and src
	cv::Mat thr,gray,src;

	src=cv::imread("../homu.jpeg");

	//convert image to grayscale
	cv::cvtColor(src,gray,cv::COLOR_BGR2GRAY);

	//convert grayscale to binary image
	cv::threshold(gray,thr,100,255,cv::THRESH_BINARY);

	//find moments of the image
	cv::Moments m=cv::moments(thr,true); //tcv::moments(InputArray array,bool binaryImage=false)
	cv::Point p(m.m10/m.m00,m.m01/m.m00);

	//coordinates of centroid
	std::cout<<cv::Mat(p)<<std::endl;

	//show the image with a point mark at the centroid
	cv::circle(src,p,5,cv::Scalar(128,0,0),-1);
	imshow("Image with center",src);
	cv::waitKey(0);

}