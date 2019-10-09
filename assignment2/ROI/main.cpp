#include <iostream>
#include <opencv2/opencv.hpp>
// selectROI is part of tracking API
#include <opencv2/tracking.hpp>

using namespace std;
using namespace cv;


int main (int argc, char **arv)
{
    // Read image
    Mat im = imread("/home/ming/test.jpg");

    // Select ROI
    Rect2d r = selectROI(im);

    // Crop image
    Mat imCrop = im(r);

    bool fromCenter = false;
    Rect2d r = selectROI(im, fromCenter);

//    bool fromCenter = false;
    Rect2d r = selectROI("Image", im, fromCenter);

    bool showCrosshair = false;
//    bool fromCenter = false;
    Rect2d r = selectROI("Image", im, fromCenter, showCrosshair);

    // Specify a vector of rectangles (ROI)
    vector<Rect2d> rects;
//    bool fromCenter = false;
// The selected rectangles are in
    selectROI("Image", im, rects, fromCenter);

    // Display Cropped Image
    imshow("Image", imCrop);
    waitKey(0);

    return 0;
}
