#include<opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include<vector>
using namespace cv;
using namespace std;
void proportion_thresh(Mat &in,Mat &out,double max_val,double proportion)
{
  vector<int>values(256,0);
  int r=in.rows;
  int c=in.cols;
    for (int i=0;i<r;i++)
    {  
       uchar*data=in.ptr<uchar>(i);
        for (int j=0;j<c;j++)
        {
           values[*data]++;
           data++;
        }}
   double p=proportion*r*c;
   int k=0;
   for(;p>0;k++)
   p=p-values[k];
   threshold(in,out,k,max_val,THRESH_BINARY);
}
int main()
{
   Mat image; 
   Mat Gray;
   Mat output;
   image=imread("../c.png");
   cvtColor(image, Gray, COLOR_BGR2GRAY);
   imshow( "Gray",Gray);
   proportion_thresh(Gray,output,255,0.4);
   imshow("output",output);
   waitKey(0);
}
