

#include <opencv2/opencv.hpp>
// selectROI is part of tracking API
#include <opencv2/tracking.hpp>
 
using namespace std;
using namespace cv;
 
 
int main (int argc, char **arv)
{
    // Read image
    Mat im = imread("image.jpg");
     
    // Select ROI
    Rect2d r = selectROI(im);
     
    // Crop image
    Mat imCrop = im(r);
     
    // Display Cropped Image
    imshow("Image", imCrop);
    waitKey(0);
     
    return 0;
}


selectROI(["windowName"],inputImage,[fromCenter_or_fromTopLeftToBottomRight],[showCrosshair_orNot])

Bug Alert : As per the instructions, you can drag a rectangle, and then press ENTER and drag another rectangle. However, there appears to be a bug in the implementation in OpenCV 3.2. You have to hit ENTER twice after the first rectangle. For all subsequent rectangles, you should hit ENTER once.
