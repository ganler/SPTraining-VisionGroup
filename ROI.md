We can use selectROI to select a bounding box or a rectangular region of interest (ROI) in an image in OpenCV. 
SelectROI is part of the tracking API.


#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
 
int main ()
{
    using namespace std;
    using namespace cv;

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
