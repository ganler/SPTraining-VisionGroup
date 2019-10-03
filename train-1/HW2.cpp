#include <opencv2/opencv.hpp>
using namespace cv;

#include <iostream>
using namespace std;


int main(int argc,char** argv) {
    VideoCapture cap;    //创建存储视频文件或者设备的对象
    cap.open(argv[1]);    //打开视频文件或者视频设备
    if (!cap.isOpened())
    {
        cout << "could not open the VideoCapture !" << endl;
        system("pause");
        return -1;
    }

    const char* windowsName1 = "Original";
    const char* windowsName2 = "Binary";
    int k = -1;
    while (true)
    {
        Mat frame,result;//读入帧和灰度图像
        bool ok = cap.read(frame);
        if (!ok)    //判断视频文件是否读取结束
            break;
        cvtColor(frame,result,CV_BGR2GRAY);//图像灰度化
        threshold(result, result, 100, 255, CV_THRESH_BINARY);//图像二值化

        imshow(windowsName1, frame);    //从视频对象中获取图片显示到窗口
        imshow(windowsName2, result);

        k = waitKey(33);    //每33毫秒一张图片
        if (k == 27) break;    //按下退出键：Esc
    }

    waitKey(-1);
    return 0;


}
