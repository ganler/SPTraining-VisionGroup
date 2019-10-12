#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
//#include <opencv2/tracking.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat im=imread("../homu.jpg");
	//select ROI
	bool fromCenter=false;
	bool showCrosshair=false;
	Rect r=selectROI("homura",im,showCrosshair,fromCenter);
	//Crop and DIsplay Cropped Image
	Mat imCrop=im(r);
	imshow("Image",imCrop);
	waitKey(0);
	return 0;
}