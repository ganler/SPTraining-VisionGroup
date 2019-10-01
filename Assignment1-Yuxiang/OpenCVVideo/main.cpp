#include <opencv2/opencv.hpp>

int main() {
    cv::namedWindow("OpenCVVideo", CV_WINDOW_AUTOSIZE);
    cv::VideoCapture capture("../demo.mov");
    std::cout << capture.isOpened() << std::endl;

    while (true) {
        cv::Mat frame;
        capture >> frame;
        imshow("OpenCVVideo", frame);
        // If any key is pressed, returned value is that key. If not, -1.
        if (cv::waitKey(5) != -1) { break; };
    }
}

