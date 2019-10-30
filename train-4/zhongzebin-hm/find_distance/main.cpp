#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "classifier.hpp"
#include <math.h>
namespace sp
{

float iou(const cv::Rect& lhs, const cv::Rect& rhs)
{
	//筛选出了两个矩形框的交集
	const int lt_x = std::max(lhs.x, rhs.x);
	const int lt_y = std::max(lhs.y, rhs.y);
	const int rd_x = std::min(lhs.x + lhs.width, rhs.x + rhs.width);
	const int rd_y = std::min(lhs.y + lhs.height, rhs.y + rhs.height);
	
	const int inner_w = std::max(0, rd_x - lt_x + 1);
	const int inner_h = std::max(0, rd_y - lt_y + 1);
	const int inner_area = inner_h * inner_w;

	return static_cast<float>(inner_area) / (lhs.area() + rhs.area() - inner_area);
}

bool left_or_right(cv::Mat temp)
{
	const int iter_rows=temp.isContinuous() ? 1:temp.rows;
        const int iter_cols=temp.rows*temp.cols/iter_rows*temp.channels();
	int left=0,right=0;
	for(int i=0;i<iter_rows;i++)
        {
            const auto row_ptr=temp.ptr<uchar>(i);
            for(int j=0;j<iter_cols;j++)
            {
                uchar value=row_ptr[i*iter_cols+j];
		if(i<iter_rows/3)
		{
		        if(j<iter_cols/3)
				left+=value;
			if(j>iter_cols/3*2)
				right+=value;
		}
		if(i>iter_rows/3*2)
		{
		        if(j<iter_cols/3)
				right+=value;
			if(j>iter_cols/3*2)
				left+=value;
		}
            }
        }
	return left>right;
}
double find_distance(std::vector<double> dis_pixel)
{
	sort(dis_pixel.begin(),dis_pixel.end());
	double min=(dis_pixel[0]+dis_pixel[1])/2;
	double length=55;
	double real_distance=length*2784/min;
	return real_distance/1452*1000;//基于1m标定对数据矫正
}

}

int main()
{   
	//读入装甲板模型
	cf::classifier classifier("../armor");
	auto mat = cv::imread("../pic5_Calibration.jpg", cv::IMREAD_GRAYSCALE);
	auto gray = cv::imread("../pic5_Calibration.jpg", cv::IMREAD_GRAYSCALE);
	auto org=cv::imread("../pic5_Calibration.jpg");
	std::cout<<"rows:"+std::to_string(mat.rows)<<'\n';
	std::cout<<"cols:"+std::to_string(mat.cols)<<'\n';
	cv::resize(mat, mat, {1280, 720});//存储灰度图像(阈值化后）
	cv::resize(org, org, {1280, 720});//存储彩色图像
	cv::resize(gray, gray, {1280, 720});//存储灰度图像（阈值化前）
	//对图像中像素值小于180的赋值为0
	const int iter_rows=mat.isContinuous() ? 1:mat.rows;
        const int iter_cols=mat.rows*mat.cols/iter_rows*mat.channels();
	for(int i=0;i<iter_rows;i++)
        {
            const auto row_ptr=mat.ptr<uchar>(i);
            for(int j=0;j<iter_cols;j++)
            {
                uchar value=row_ptr[i*iter_cols+j];
                if(value<180)
			row_ptr[i*iter_cols+j]=0;
            }
        }
	//使用mser进行聚类，得到聚类后的矩形框区域
	auto mser = cv::MSER::create();
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Rect>               bboxes;

	mser->detectRegions(mat, contours, bboxes);
	std::cout << bboxes.size() << '\n';


	std::vector<int> drawed_rects;
	drawed_rects.reserve(bboxes.size() / 4);//reserve增加了容器的capacity,但size不变。capacity代表容器能存储的最大空间

	int cnt = 0;
	if (!bboxes.empty())//如果检测到了矩形框
	{
		++cnt;
		//cv::rectangle(org, bboxes.front(), {0, 0, 255},3);//画上第一个检测到的矩形框
		drawed_rects.push_back(0);
	}

	constexpr float thresh = 0.5;
	for (int i = 1; i < bboxes.size(); ++i)
	{
		bool skip = false;
		for (auto&& index : drawed_rects)//遍历drawed_rects里所有的元素，index即为元素内容
		{//应当要大框，舍弃小框
			//bool judge=!(bboxes[i].contains(bboxes[index].tl()) && bboxes[i].contains(bboxes[index].br()));
			if (skip = (sp::iou(bboxes[i], bboxes[index]) > thresh) )
			{
				break;
			}
			if(bboxes[i].width>bboxes[i].height)//如果宽大于高，skip为true并跳出循环
			{
				skip=true;
				break;
			}
		}
		if (skip)//skip为true，进行下一个矩形框查找
			continue;
		//cv::rectangle(org, bboxes[i], { 0, 0, 255 },3);//画出当前矩形框
		drawed_rects.push_back(i);//记录矩形框的index
		++cnt;
	}
	//将所有检测到的矩形框两两组合成待检测区域
	std::vector<cv::Rect> detect;
	int count=0;
	/*for(int i=1;i<2;i++)
		for(int j=3;j<4;j++)*/
	for(int i=0;i<drawed_rects.size()-1;i++)
		for(int j=i+1;j<drawed_rects.size();j++)
		{
			cv::Point a,b,c,d;//拿到一组灯条的四个顶点
			//如果一个矩形区域左上方比右上方亮，则视为灯条左倾，取tl和br;反之，视为右倾，取tr和bl;左倾则f=true，反之f=false
			bool f=sp::left_or_right(mat(bboxes[drawed_rects[i]]));
			if(f)
			{
				a=bboxes[drawed_rects[i]].tl();
				b=bboxes[drawed_rects[i]].br();
				//cv::rectangle(org, bboxes[drawed_rects[i]], { 0, 0, 255 },2);
			}
			else
			{
				a.x=bboxes[drawed_rects[i]].br().x;
				a.y=bboxes[drawed_rects[i]].tl().y;
				b.x=bboxes[drawed_rects[i]].tl().x;
				b.y=bboxes[drawed_rects[i]].br().y;
				//cv::rectangle(org, bboxes[drawed_rects[i]], { 255, 0, 0 },2);
			}
			f=sp::left_or_right(mat(bboxes[drawed_rects[j]]));
			if(f)
			{
				c=bboxes[drawed_rects[j]].tl();
				d=bboxes[drawed_rects[j]].br();
				//cv::rectangle(org, bboxes[drawed_rects[j]], { 0, 0, 255 },2);
			}
			else
			{
				c.x=bboxes[drawed_rects[j]].br().x;
				c.y=bboxes[drawed_rects[j]].tl().y;
				d.x=bboxes[drawed_rects[j]].tl().x;
				d.y=bboxes[drawed_rects[j]].br().y;
				//cv::rectangle(org, bboxes[drawed_rects[i]], { 255, 0, 0 },2);
			}
			/*cv::Mat show;
			org.copyTo(show);
			cv::rectangle(show, bboxes[i], { 0, 0, 255 },3);
			cv::rectangle(show, bboxes[j], { 255, 0, 0 },3);
			cv::circle(show,a,5,{ 0, 0, 255 },-1);
			cv::circle(show,b,5,{ 0, 0, 255 },-1);
			cv::circle(show,c,5,{ 255, 0, 0 },-1);
			cv::circle(show,d,5,{ 255, 0, 0 },-1);
			std::cout<<"current i:"+std::to_string(i)<<'\n';
			std::cout<<"current j:"+std::to_string(j)<<'\n';
			cv::imshow("test",show);
			cv::waitKey(0);*/
			std::vector<cv::Point> contour;
			contour.push_back(a);
			contour.push_back(b);
			contour.push_back(c);
			contour.push_back(d);
			cv::RotatedRect rect = minAreaRect(contour);//求最小外接矩形
			cv::Point2f vertices[4];
			rect.points(vertices);//外接矩形的4个顶点
			/*for (int i = 0; i < 4; i++)//画矩形
				line(org, vertices[i], vertices[(i + 1) % 4], {0,0,255});*/
			cv::Point2f center = rect.center;//外接矩形中心点坐标
			//std::cout<<"angle:"+std::to_string(rect.angle)<<'\n';
			cv::Mat rot_mat = cv::getRotationMatrix2D(center, rect.angle>-45?rect.angle:(-90-rect.angle), 1.0);//求旋转矩阵
			cv::Mat rot_image;
			cv::Size dst_sz(gray.size());
			cv::warpAffine(gray, rot_image, rot_mat, dst_sz);//旋转变换
			if(rect.angle>-45)
			{
				if(center.x - (rect.size.width / 2)>=0 && center.x - (rect.size.width / 2)+rect.size.width<=rot_image.cols && center.y - (rect.size.height/2)-rect.size.height/2>=0 && center.y - (rect.size.height/2)+rect.size.height*2<=rot_image.rows)
				{
					cv::Mat result = rot_image(cv::Rect(center.x - (rect.size.width / 2), center.y - (rect.size.height/2)-rect.size.height/2, rect.size.width, rect.size.height*2));//提取ROI
					
					if(result.cols<result.rows*3 && classifier.boolean_forward(result))
					{
						count++;
						cv::imwrite("../detect/"+std::to_string(count)+".jpg",result);
						std::vector<double> dis_pixel;
						for (int i = 0; i < 4; i++)//画矩形
						{
							line(org, vertices[i], vertices[(i + 1) % 4], {0,0,255});
							//计算矩形每个边的像素长度（放缩回原图）
							dis_pixel.push_back(sqrt(pow(4.167*(vertices[i].x-vertices[(i + 1) % 4].x),2)+pow(3.513*(vertices[i].y-vertices[(i + 1) % 4].y),2)));
						}
						//计算灯条距离
						//std::cout<<"distance:"+std::to_string(sp::find_distance(dis_pixel))<<'\n';
						cv::putText(org,"distance:"+std::to_string(sp::find_distance(dis_pixel)),vertices[0],cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1, 8);
					}
				}
			}
			else
			{
				if(center.x - (rect.size.height / 2)>=0 && center.x - (rect.size.height / 2)+rect.size.height<=rot_image.cols && center.y - (rect.size.width/2)-rect.size.width/2>=0 && center.y - (rect.size.width/2)+rect.size.width*2<=rot_image.rows)
				{
					cv::Mat result = rot_image(cv::Rect(center.x - (rect.size.height / 2), center.y - (rect.size.width/2)-rect.size.width/2, rect.size.height, rect.size.width*2));//提取ROI
					
					if(result.cols<result.rows*3 && classifier.boolean_forward(result))
					{
						count++;
						cv::imwrite("../detect/"+std::to_string(count)+".jpg",result);
						std::vector<double> dis_pixel;
						for (int i = 0; i < 4; i++)//画矩形
						{
							line(org, vertices[i], vertices[(i + 1) % 4], {0,0,255});
							//计算矩形每个边的像素长度（放缩回原图）
							dis_pixel.push_back(sqrt(pow(4.167*(vertices[i].x-vertices[(i + 1) % 4].x),2)+pow(3.513*(vertices[i].y-vertices[(i + 1) % 4].y),2)));
						}
						//计算灯条距离
						//std::cout<<"min:"+std::to_string(sp::find_distance(dis_pixel))<<'\n';
						cv::putText(org,"distance:"+std::to_string(sp::find_distance(dis_pixel)),vertices[0],cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1, 8);
					}
				}
			}
		}
	std::cout<<bboxes[drawed_rects[0]].tl()<<'\n';
	std::cout << cnt << '\n';
	std::cout<<drawed_rects.size()<<'\n';
	cv::imwrite("../ans.jpg", org);
	cv::imwrite("../gray.jpg",mat);
}
