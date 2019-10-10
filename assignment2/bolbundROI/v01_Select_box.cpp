//
// Created by ming on 2019/10/9.
//

#include <opencv2/opencv.hpp>
// selectROI is part of tracking API
#include <opencv2/tracking.hpp>

using namespace std;
using namespace cv;


int main (int argc, char **arv)
{
    // Read image
    Mat im = imread("/home/ming/git_yummy/SPTraining-VisionGroup/assignment2/bolbundROI/shape.png");

    // Select ROI
    Rect2d r = selectROI(im);

    // Crop image
    Mat imCrop = im(r);

    // Display Cropped Image
    imshow("Image", imCrop);
    imwrite("../one_shape.png",imCrop);
    waitKey(0);

    return 0;
}