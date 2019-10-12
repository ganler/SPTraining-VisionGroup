What is Moments?
The spatial moments 𝙼𝚘𝚖𝚎𝚗𝚝𝚜::𝚖ji are computed as:
𝚖ji=∑x,y(𝚊𝚛𝚛𝚊𝚢(x,y)⋅x^j⋅y^i)

The central moments 𝙼𝚘𝚖𝚎𝚗𝚝𝚜::𝚖𝚞ji are computed as:
𝚖𝚞ji=∑x,y(𝚊𝚛𝚛𝚊𝚢(x,y)⋅(x−x¯)^j⋅(y−y¯)^i)

where (x¯,y¯) is the mass center:
x¯=𝚖10/𝚖00,y¯=𝚖01/𝚖00

Code:
// declare Mat variables, thr, gray and src
Mat thr, gray, src;
 
//1. Convert the Image to grayscale.
cvtColor( src, gray, COLOR_BGR2GRAY );
 
//2. Perform Binarization on the Image.
threshold( gray, thr, 100,255,THRESH_BINARY );
 
//3. Find the center of the image after calculating the moments.
Moments m = moments(thr,true);
Point p(m.m10/m.m00, m.m01/m.m00);
 
// coordinates of centroid
cout<< Mat(p)<< endl;
 
Code for multiple blobs:

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
