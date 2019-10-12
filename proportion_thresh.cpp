#include <opencv2/opencv.hpp>

namespace sp
{
    void proportion_thresh(const cv::Mat& in,cv::Mat& out,double max_val,double proportion);
}

int main()
{
    using namespace cv;
    Mat picture=imread("../timg (1).jpeg",IMREAD_GRAYSCALE);
    sp::proportion_thresh(picture,picture,255,0.1);
    imshow("proportion_thresh",picture);
    waitKey();
    return 0;
}

namespace sp
{
    void proportion_thresh(const cv::Mat& in,cv::Mat& out,double max_val,double proportion)
    {
        using namespace cv;
        int n[256]={0},sum=0,value;
        for (int i=0;i<in.rows;++i)
        {
            const auto pr=in.ptr<uchar>(i);
            for (int j=0;j<in.cols;++j)
            {
                n[pr[j]]+=1;
            }
        }
        for (value=255;sum<proportion*in.rows*in.cols;--value)
            sum+=n[value];
        threshold(in,out,value,max_val,THRESH_BINARY);
    }
}