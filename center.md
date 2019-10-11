#include<opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
int main()
{
   Mat image; 
   Mat Gray;
   Mat the;
   Mat output;
   vector<vector<Point> > contours;
   vector<Vec4i> hierarchy;
   image=imread("../photo.jepg");
   //gray
   cvtColor(image, Gray, COLOR_BGR2GRAY);
   //binary image
   threshold(Gray,the,150,255,THRESH_BINARY);
   
   // detect edges using canny 边界索取
   Canny(Gray, output, 50, 150, 3 );
   
   // find contours 找出图形轮廓
   findContours( output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
 
   // get the moments 找到图形的质心
   vector<Moments> mu(contours.size());
   for( int i = 0; i<contours.size(); i++ )
   { mu[i] = moments( contours[i], false ); }
 
   // get the centroid of figures.  算力矩 二值化之后的图像矩
   vector<Point2f> mc(contours.size());
   for( int i = 0; i<contours.size(); i++)
   { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }
 
 
   // draw contours  画质心
   Mat drawing(output.size(), CV_8UC3, Scalar(255,255,255));
   for( int i = 0; i<contours.size(); i++ )
   {Scalar color = Scalar(167,151,0); // B G R values
    drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
    circle( drawing, mc[i], 4, color, -1, 8, 0 );}
 
   // show the resultant image
    namedWindow( "Contours", WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
    waitKey(0);
}

