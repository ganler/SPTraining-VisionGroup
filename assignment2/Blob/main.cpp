#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>
#include "stddef.h"
using namespace std;
using namespace cv;

int main()
{
//    std::cout << "Hello, World!" << std::endl;
  /*
    Mat thr,gray,src;
    src=imread("/home/ming/test.jpg");
    cvtColor(src,gray,COLOR_BGR2GRAY);
    threshold(gray,thr,100,255,THRESH_BINARY);
    Moments m=moments(thr,true);
    Point p(m.m10/m.m00,m.m01/m.m00);
    cout<<Mat(p)<<endl;
    circle(src,p,5,Scalar(128,0,0),-1);
    imshow("Image with center",src);
    waitKey(0);
    */
    Mat thr, gray, src;
    src=imread("/home/ming/test.jpg");
    cvtColor(src,gray,COLOR_BGR2GRAY);

    Mat canny_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

// detect edges using canny
    Canny( gray, canny_output, 50, 150, 3 );

// find contours
    findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

// get the moments
    vector<Moments> mu(contours.size());
    for( int i = 0; i<contours.size(); i++ )
    { mu[i] = moments( contours[i], false ); }

// get the centroid of figures.
    vector<Point2f> mc(contours.size());
    for( int i = 0; i<contours.size(); i++)
    { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }


// draw contours
    Mat drawing(canny_output.size(), CV_8UC3, Scalar(255,255,255));
    for( int i = 0; i<contours.size(); i++ )
    {
        Scalar color = Scalar(167,151,0); // B G R values
        drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
        circle( drawing, mc[i], 4, color, -1, 8, 0 );
    }

// show the resultant image
    namedWindow( "Contours", WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
    waitKey(0);
    return 0;
}