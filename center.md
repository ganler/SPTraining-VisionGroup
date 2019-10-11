multiple blobs
(1)use canny to detect edges
(2)find contour {findContour}
(3)get the moments//通过轮廓的尺寸确定
(4)get the centroid
(5)draw contours
(6)show the resultant image


src = imread( "../star1.jpg" ,1 );

/// Convert image to gray and blur it
cvtColor( src, src_gray, CV_BGR2GRAY );
blur( src_gray, src_gray, Size(3,3) );

namedWindow( "image", CV_WINDOW_AUTOSIZE );
imshow( "image", src );

Mat canny_output;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

//利用canny算法检测边缘
Canny( src_gray, canny_output, thresh, thresh*2, 3 );
namedWindow( "canny", CV_WINDOW_AUTOSIZE );
imshow( "canny", canny_output );
//查找轮廓
findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

//计算轮廓矩
vector<Moments> mu(contours.size() );
for( int i = 0; i < contours.size(); i++ )
    { mu[i] = moments( contours[i], false ); }

//计算轮廓的质心
vector<Point2f> mc( contours.size() );
for( int i = 0; i < contours.size(); i++ )
    { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }

//画轮廓及其质心
Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
for( int i = 0; i< contours.size(); i++ )
    {
    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    circle( drawing, mc[i], 4, color, -1, 8, 0 );
    }

namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
imshow( "Contours", drawing );

//打印轮廓面积和轮廓长度
printf("\t Info: Area and Contour Length \n");
for( int i = 0; i< contours.size(); i++ )
    {
    printf(" * Contour[%d] - Area (M_00) = %.2f - Area OpenCV: %.2f - Length: %.2f \n", i, mu[i].m00, contourArea(contours[i]), arcLength( contours[i], true ) );
    Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    circle( drawing, mc[i], 4, color, -1, 8, 0 );
    }
