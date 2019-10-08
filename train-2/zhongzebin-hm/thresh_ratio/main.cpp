#include "thresh.h"
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
    Mat src,dst;
    src=imread("../warning.png");
    thresh T;
    dst=T.proportion_thresh(src,80);
    imshow("thresh",dst);
    waitKey(0);
    return 0;
}
