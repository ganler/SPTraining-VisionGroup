#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>

int main()
{
	//declare Mat variables,thr,gray and src
	cv::Mat gray,src;

	src=cv::imread("../multiple_blob.png");

	//convert image to grayscale
	cv::cvtColor(src,gray,cv::COLOR_BGR2GRAY);

	cv::Mat canny_output;
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	//detect edge using canny
	cv::Canny(gray,canny_output,50,150,3);

	//find contours
	cv::findContours(canny_output,contours,hierarchy,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE,cv::Point(0,0));

	//get the moments
	std::vector<cv::Moments> mu(contours.size());
	for (int i=0;i<contours.size();i++)
	{
		mu[i]=cv::moments(contours[i],false);
	}

	//get the controid of figures.
	std::vector<cv::Point2f> mc(contours.size());
	for (int i=0;i<contours.size();i++)
	{
		mc[i]=cv::Point2f(mu[i].m10/mu[i].m00,mu[i].m01/mu[i].m00);
	}

	//draw contours
	cv::Mat drawing(canny_output.size(),CV_8UC3,cv::Scalar(255,255,255));
	for (int i=0;i<contours.size();i++)
	{
		cv::Scalar color=cv::Scalar(167,151,0);		//B G R values
		cv::drawContours(drawing,contours,i,cv::Scalar(0,0,200),2,8,hierarchy,0,cv::Point());
		cv::circle(drawing,mc[i],4,color,-1,8,0);
	}

	//show the resultant image
	cv::namedWindow("Contours",cv::WINDOW_AUTOSIZE);
	cv::imshow("Contours",drawing);
	cv::waitKey(0);
	return 0;
}