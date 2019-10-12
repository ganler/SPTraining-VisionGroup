#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <array>

using namespace cv;
using namespace std;

void proportion_thresh(const cv::Mat& in,cv:: Mat& out,double max_val,double proportion)
{
	out=in.clone();
	int total=in.rows*in.cols;
	int top=int(total*proportion);
	array<int,260> count={0};
	const std::size_t iter_rows=in.isContinuous()?1:in.rows;
	const std::size_t iter_cols=in.rows*in.cols/iter_rows;
	for (std::size_t i=0;i<iter_rows;i++)
	{
		const auto row_ptr=in.ptr<uchar>(i);
		for (std::size_t j=0;j<iter_cols;j++)
			count[row_ptr[j]]++;
	}
	int sum=0;
	int threshold;
	for (std::size_t i=255;i>=0;i--)
	{
		sum+=count[i];
		if (sum>=top)
		{
			threshold=i;
			break;
		}
	}
	for (std::size_t i=0;i<iter_rows;i++)
	{
		const auto row_ptr=out.ptr<uchar>(i);
		for (std::size_t j=0;j<iter_cols;j++)
			row_ptr[j]=row_ptr[j]>=threshold?max_val:0;
	}
}

int main()
{
	cv::Mat mat=cv::imread("homu.jpeg",cv::IMREAD_GRAYSCALE);
	cv::imshow("homu_before",mat);
	waitKey(0);
	proportion_thresh(mat,mat,255,0.2);
	imshow("homu_after",mat);
	waitKey(0);
	return 0;
}