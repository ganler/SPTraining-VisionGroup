#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
namespace sp
{

float iou(const cv::Rect& lhs, const cv::Rect& rhs)
{
	const int lt_x = std::max(lhs.x, rhs.x);
	const int lt_y = std::max(lhs.y, rhs.y);
	const int rd_x = std::min(lhs.x + lhs.width, rhs.x + rhs.width);
	const int rd_y = std::min(lhs.y + lhs.height, rhs.y + rhs.height);
	
	const int inner_w = std::max(0, rd_x - lt_x + 1);
	const int inner_h = std::max(0, rd_y - lt_y + 1);
	const int inner_area = inner_h * inner_w;

	return static_cast<float>(inner_area) / (lhs.area() + rhs.area() - inner_area);
}

}

int main()
{   
	auto mat = cv::imread("test.jpg", cv::IMREAD_GRAYSCALE);
	cv::resize(mat, mat, {1280, 720});
	auto mser = cv::MSER::create(8,85,10000,0.1);
	/*修改MSER算法中初始设置的参数，使既减少
	BBOXES数量又不遗漏数字，且适用于不同图片*/
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Rect>               bboxes;

	mser->detectRegions(mat, contours, bboxes);
	std::cout << bboxes.size() << '\n';
	std::cin.get(); 

	std::vector<int> drawed_rects;
	drawed_rects.reserve(bboxes.size() / 4);

	int cnt = 0;
	if (!bboxes.empty())
	{
		++cnt;
		cv::rectangle(mat, bboxes.front(), {255, 0, 0});
		drawed_rects.push_back(0);
	}
	constexpr float thresh = 0.5;
	int prop=8;//设置矩形长宽比界限
	for (int i = 1; i < bboxes.size(); ++i)
	{
		bool skip = false;
		for (auto&& index : drawed_rects)
			if (skip = (sp::iou(bboxes[i], bboxes[index]) > thresh))
				break;
		if (skip)
			continue;
		if((bboxes[i].width/bboxes[i].height)>=prop||(bboxes[i].height/bboxes[i].width)>=prop)
		    continue;//超过长宽比就舍弃
		cv::rectangle(mat, bboxes[i], { 255, 0, 0 });
		drawed_rects.push_back(i);
		++cnt;
	}
	
	std::cout << cnt << '\n';
	std::cin.get();
	cv::imwrite("test_out.jpg", mat);
}