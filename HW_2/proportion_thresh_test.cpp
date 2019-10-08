#include <opencv2/opencv.hpp>
#include <string.h>
void proportion_thresh(cv::Mat &in, cv::Mat &out, double max_Val, double proportion)
{
    int histogram[256];
    int rows = in.rows;
    int cols = in.cols;
    int sum = rows * cols;
    memset(histogram, 0, sizeof(histogram));
    if (in.isContinuous())
    {
        rows = 1;
        cols = sum;
    }
    for (int i = 0; i < rows; i++)
    {
        uchar* row_ptr=in.ptr<uchar>(i);
        for (int j = 0; j < cols; j++)
        {
            histogram[*(row_ptr)]++;
            row_ptr++;
        }
    }
    int choose = proportion * sum, i = 255;
    for (; i >= 0; i--)
    {
        choose = choose - histogram[i];
        if (choose < 0)
            break;
    }
    std::cout<<i;
    threshold(in,out,i,max_Val,cv::THRESH_BINARY);
}
int main()
{
    auto mat=cv::imread("proportion.jpeg",cv::IMREAD_GRAYSCALE);
    proportion_thresh(mat,mat,100,0.2);
    imshow("12",mat);
    cv::waitKey(19000);
}