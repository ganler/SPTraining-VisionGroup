# ROI
## 代码如下
```
#include <opencv2/opencv.hpp>
// selectROI is part of tracking API
#include <opencv2/video.hpp>

using namespace std;
using namespace cv;


int main(int argc, char **arv)
{
	// Read image
	Mat im = imread("GT.jpg");
	resize(im, im, { 500,500 });
	// Select ROI
	bool fromCenter = false;
	Rect2d r = selectROI("Image", im, fromCenter);

	// Crop image
	Mat imCrop = im(r);

	// Display Cropped Image
	imshow("NEWImage", imCrop);
	waitKey(0);

	return 0;
}


```

还可以，不太难


