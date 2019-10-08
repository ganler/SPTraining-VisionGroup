## Key Word

Bounding Box

ROI

## Function to Use

cv::Rect cv::selectROI(const cv::String &windowName, cv::InputArray img, bool showCrosshair = true, bool fromCenter = false)

## Select ROI

```c++
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main (int argc, char **arv)
{
    // Read image
    Mat im = imread("../图片/timg (2).jpeg");
     
    // Select ROI
    bool fromSenter=false;
    Rect2d r = selectROI(im,fromSenter);
     
    // Crop image
    Mat imCrop = im(r);
     
    // Display Cropped Image
    imshow("Image", imCrop);
    waitKey(0);
     
    return 0;
}
```

![](/home/jachinlin/SPTraining-VisionGroup/HW_2/Single ROI.png)

