#include <opencv2/opencv.hpp>
#include <algorithm>

void proportion_thresh(const cv::Mat &in, cv::Mat &out, double max_val, double proportion) {
    std::vector<uchar> data;
    data.reserve(in.size().area());

    const std::size_t iter_rows = in.isContinuous() ? 1 : in.rows;
    const std::size_t iter_cols = in.rows * in.cols / iter_rows * in.channels();
    for (int i = 0; i < iter_rows; ++i) {
        const auto rowPtr = in.ptr<uchar>(i);
        for (int j = 0; j < iter_cols; ++j) {
            data.push_back(rowPtr[i * iter_cols + j]);
        }
    }

    std::sort(data.begin(), data.end(), [](uchar lhs, uchar rhs) {
        return lhs > rhs;
    });

    threshold(in, out, data[static_cast<std::size_t>(in.size().area() * proportion)],
              max_val, cv::THRESH_BINARY);
}

int main() {
    auto mat = cv::imread("../test.jpg", cv::IMREAD_GRAYSCALE);
    cv::resize(mat, mat, {300, 300});

    proportion_thresh(mat, mat, 255, 0.8);
    cv::imshow("test", mat);

    cv::waitKey();
}
