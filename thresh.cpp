#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;
class thresh
{
public:
Mat proportion_thresh(const MAT& src, double max_val, double proportion)
     {
       int rows=src.isContinous() ? 1:src.rows;//判断是否存在间断
       int cols=src.rows*src.cols/rows*src.channels.();
       vector<uchar> image;
       for(int i=0;i<rows;i++)
        {
          auto row_ptr=src.ptr<uchar>(i);
          for(int j=0;j<cols;j++)
           {
             uchar value=row_ptr[i*cols+j];
             image.push_back(value);
           }
         }
           sort(image.begin(),image.end());
           int thresh=image[int(image.size()*ratio/100)];
           threshold(src,src,thresh,255,CV_THRESH_BINARY);
           return src;
     }
    };
   int main()
     {
       auto mat=cv::imread("kobe.jpeg",cv::IMREAD_GRAYSCALE);
       resize(mat,mat ,{200,200});
       cvtcolor(mat,gray,CV_BGR2GRAY)
       imshow("gray",gray);
       proportion_thresh(mat,255,0.2);
       imwrite("kobe2.jpeg",mat);
       imshow("kobe2.jpeg",mat);
       waitkey();
     }






}
