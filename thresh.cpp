#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <vector>

using namespace cv;
using namespace std;

int main()
     {
       Mat src;
       src=imread("kobe.jpeg",IMREAD_GRAYSCALE);
       imshow("kobe",src);
       const int iter_rows=src.isContinous() ? 1:src.rows;
       const int iter_cols=src.rows*src.cols/iter_rows;
       vector<uchar> image;
       for(int i=0;i<iter_rows;i++)
        {
          const auto row_ptr=src.ptr<uchar>(i);
          for(int j=0;j<iter_cols;j++)
           {
             uchar value=row_ptr[i*iter_cols+j];
             image.push_back(value);
           }
         }
           sort(image.begin(),image.end());
           int thresh=image[int(image.size()*0.14)];
           threshold(src,src,thresh,255,CV_THRESH_BINARY);
           imshow("kobe2",src);
           waitKey();
     }

