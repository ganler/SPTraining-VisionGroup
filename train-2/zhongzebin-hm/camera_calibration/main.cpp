#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main()
{
    Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
    Mat distCoeffs = Mat::zeros(8, 1, CV_64F);
    Mat cal[20];//黑白棋盘图像
    vector<Point2f> corners;//每幅图角点
    vector<vector<Point3f>> objectlist(1);//世界坐标系下的棋盘角点
    vector<vector<Point2f>> cornerslist;//所有图中角点
    int i = 0, j = 0;
    bool found;//是否找到角点
    //根据格子大小生成世界坐标系下角点的坐标，z=0
    for (i = 0; i < 6; ++i)
        for (j = 0; j < 9; ++j)
        {
            objectlist[0].push_back(Point3f(j * 30, i * 30, 0));
        }
    //读取棋盘图像
    cal[0] = imread("../calibration pictures/calibration1.jpg");
    cal[1] = imread("../calibration pictures/calibration2.jpg");
    cal[2] = imread("../calibration pictures/calibration3.jpg");
    cal[3] = imread("../calibration pictures/calibration4.jpg");
    cal[4] = imread("../calibration pictures/calibration5.jpg");
    cal[5] = imread("../calibration pictures/calibration6.jpg");
    cal[6] = imread("../calibration pictures/calibration7.jpg");
    cal[7] = imread("../calibration pictures/calibration8.jpg");
    cal[8] = imread("../calibration pictures/calibration9.jpg");
    cal[9] = imread("../calibration pictures/calibration10.jpg");
    cal[10] = imread("../calibration pictures/calibration11.jpg");
    cal[11] = imread("../calibration pictures/calibration12.jpg");
    cal[12] = imread("../calibration pictures/calibration13.jpg");
    cal[13] = imread("../calibration pictures/calibration14.jpg");
    cal[14] = imread("../calibration pictures/calibration15.jpg");
    cal[15] = imread("../calibration pictures/calibration16.jpg");
    cal[16] = imread("../calibration pictures/calibration17.jpg");
    cal[17] = imread("../calibration pictures/calibration18.jpg");
    cal[18] = imread("../calibration pictures/calibration19.jpg");
    cal[19] = imread("../calibration pictures/calibration20.jpg");
    //对每个棋盘图像进行处理
    for (i = 0; i < 20; i++)
    {
        cvtColor(cal[i], cal[i], COLOR_BGR2GRAY);
        //角点检测
        found = findChessboardCorners(cal[i], Size(9, 6), corners, CALIB_CB_ADAPTIVE_THRESH);//输入，（每行角点数，每列角点数），输出角点坐标，检测方式
        if (found)
        {
            //亚像素级别角点提取
            cornerSubPix(cal[i], corners, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));//输入，角点坐标，检测窗口的一半，死点窗口一半，检测方式
            //将从每个图像中找到的角点存入角点列表
            cornerslist.push_back(corners);
        }
    }
    //准备相机标定参数
    objectlist.resize(cornerslist.size(), objectlist[0]);
    vector<Mat> rves, tvecs;
    //进行相机标定
    calibrateCamera(objectlist, cornerslist, cal[0].size(), cameraMatrix, distCoeffs, rves, tvecs);//世界坐标系中的点，像素坐标系中的点，格子大小，相机内参，矫正参数，旋转向量，位移向量
    //图像矫正
    Mat dist;
    undistort(cal[0],dist,cameraMatrix,distCoeffs);
    imshow("校正前",cal[0]);
    imshow("校正后",dist);
    waitKey(0);
    return 0;
}