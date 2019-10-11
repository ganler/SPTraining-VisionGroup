
# center
## 代码如下

```
#include<opencv2/highgui.hpp>
#include<opencv2/core.hpp>
#include<opencv2/opencv.hpp>
#include<iostream>
int main()
{
	using namespace cv;
	// declare Mat variables, thr, gray and src
	Mat mat;
	mat = imread  ("GT.jpg", cv::IMREAD_GRAYSCALE);
	// convert image to grayscale
	resize(mat, mat, { 1000,1000 });
	// convert grayscale to binary image
	threshold(mat, mat, 160, 255, THRESH_BINARY);

	// find moments of the image
	Moments m = moments(mat, true);
	Point p(m.m10 / m.m00, m.m01 / m.m00);

	// coordinates of centroid
	std::cout << Mat(p) << '/n';

	// show the image with a point mark at the centroid
	circle(mat, p, 5, Scalar(128, 0, 0), -1);
	imshow("Image with center", mat);
	waitKey();
	return 0;
}
```

大物没学好，力矩什么的不太会