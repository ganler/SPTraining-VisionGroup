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


