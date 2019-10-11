#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main (int argc, char **arv)
{
    // Read image读取
    Mat im = imread("../photo.jepg");
    
    // Select ROI 选取矩形区域
    Rect2d r = selectROI(im);
    
    // Crop image 图像的裁剪 
    Mat imCrop = im(r);
    
    // Display Image (enter)
    imshow("Image", imCrop);
    waitKey(0);
    
    return 0;
}
