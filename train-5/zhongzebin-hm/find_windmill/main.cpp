#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
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

std::vector<int> sort_index(std::vector<int> index, std::vector<int> area)
{
	for(int i=0;i<index.size()-1;i++)
		for(int j=i+1;j<index.size();j++)
		{
			if(area[i]>area[j])
			{
				int t=area[i];
				area[i]=area[j];
				area[j]=t;
				t=index[i];
				index[i]=index[j];
				index[j]=t;
			}
		}
	return index;
}

cv::Point center(cv::Rect rect)
{
	cv::Point tl=rect.tl();
	cv::Point br=rect.br();
	cv::Point c;
	c.x=int((tl.x+br.x)/2);
	c.y=int((tl.y+br.y)/2);
	return c;
}

cv::Mat polyfit(std::vector<cv::Point> &chain, int n)
{
	cv::Mat y(chain.size(), 1, CV_32F, cv::Scalar::all(0));
	cv::Mat phy(chain.size(), n, CV_32F, cv::Scalar::all(0));
	for (int i = 0; i < phy.rows; i++)
	{
		float* pr = phy.ptr<float>(i);
		for (int j = 0; j < phy.cols; j++)
		{
			pr[j] = pow(chain[i].x, j);
		}
		y.at<float>(i) = chain[i].y;
	}
	cv::Mat phy_t = phy.t();
	cv::Mat phyMULphy_t = phy.t()*phy;
	cv::Mat phyMphyInv = phyMULphy_t.inv();
	cv::Mat a = phyMphyInv * phy_t;
	a = a * y;
	return a;
}

cv::Mat draw_line(cv::Mat org,float a,float b)
{
	cv::Point begin,end;
	begin.x=0;
	begin.y=int(b);
	int end_y=int((org.cols-1)*a+b);
	if(org.rows>end_y)
	{
		end.x=org.cols-1;
		end.y=end_y;
	}
	else
	{
		end.y=org.rows-1;
		end.x=int((end.y-b)/a);
	}
	cv::line(org, begin, end, {255,0,0});
	return org;
}

double distance(float a,float b,cv::Point c)
{
	double dis=(a*c.x+b-c.y)/sqrt(a*a+1);
	return abs(dis);
}

}


int main()
{   
	/*cv::VideoCapture cap;
	cap.open("../10.avi");
	cv::Mat img;
	int count=0;
	while(1)
	{
		cap>>img;
		if(img.empty()) break;
		count++;
		if(count==2480) {cv::imwrite("../test2.jpg",img);break;}
		//std::cout<<count<<'\n';
		//cv::imshow("windmill",img);
		//cv::waitKey(40);
	}*/

	cv::Mat mat,gray;
	std::vector<cv::Mat> channels;
	auto org=cv::imread("../test2.jpg");
	cv::split(org,channels);
	gray=channels.at(2);
	mat=channels.at(2);
	cv::Mat blue=channels.at(0);
	cv::Mat green=channels.at(1);
	std::cout<<"rows:"+std::to_string(mat.rows)<<'\n';
	std::cout<<"cols:"+std::to_string(mat.cols)<<'\n';
	cv::resize(mat, mat, {1280, 720});//存储灰度图像(阈值化后）
	cv::resize(org, org, {1280, 720});//存储彩色图像
	cv::resize(gray, gray, {1280, 720});//存储灰度图像（阈值化前）
	cv::resize(blue, blue, {1280, 720});
	cv::resize(green, green, {1280, 720});
	//对图像中红色通道小于180或蓝绿通道均大于50赋值为0
	const int iter_rows=mat.isContinuous() ? 1:mat.rows;
        const int iter_cols=mat.rows*mat.cols/iter_rows*mat.channels();
	for(int i=0;i<iter_rows;i++)
        {
            const auto row_ptr=mat.ptr<uchar>(i);
	    const auto row_ptr_b=blue.ptr<uchar>(i);
	    const auto row_ptr_g=green.ptr<uchar>(i);
            for(int j=0;j<iter_cols;j++)
            {
                uchar value=row_ptr[i*iter_cols+j];
		uchar value_b=row_ptr_b[i*iter_cols+j];
		uchar value_g=row_ptr_g[i*iter_cols+j];
                if(value<180 || (value_b>50 && value_g>50))
			row_ptr[i*iter_cols+j]=0;
            }
        }
	//cv::imshow("gray",mat);
	//cv::waitKey(0);

	//使用mser进行聚类，得到聚类后的矩形框区域
	auto mser = cv::MSER::create();
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Rect>               bboxes;

	mser->detectRegions(mat, contours, bboxes);
	std::cout << bboxes.size() << '\n';


	std::vector<int> drawed_rects;
	drawed_rects.reserve(bboxes.size() / 4);//reserve增加了容器的capacity,但size不变。capacity代表容器能存储的最大空间
	int area;
	std::vector<int> drawed_area;//存储每个合格的矩形框的面积
	if (!bboxes.empty())//如果检测到了矩形框
	{
		//cv::rectangle(org, bboxes.front(), {255, 0, 0},3);//画上第一个检测到的矩形框
		area=bboxes.front().area();
		drawed_area.push_back(area);
		drawed_rects.push_back(0);
	}

	constexpr float thresh = 0.2;
	for (int i = 1; i < bboxes.size(); ++i)
	{
		bool skip = false;
		for (auto&& index : drawed_rects)//遍历drawed_rects里所有的元素，index即为元素内容
		{
			if (skip = (sp::iou(bboxes[i], bboxes[index]) > thresh) )
			{
				break;
			}
		}
		if (skip)//skip为true，进行下一个矩形框查找
			continue;
		//cv::rectangle(org, bboxes[i], { 255, 0, 0 },3);//画出当前矩形框
		area=bboxes[i].area();
		drawed_area.push_back(area);
		drawed_rects.push_back(i);//记录矩形框的index
	}
	//排序并获得面积最小的前7个矩形框，并将其中心点存储
	std::vector<int> sort_bboxes=sp::sort_index(drawed_rects,drawed_area);
	std::vector<cv::Point> c_list;
	for(int i=0;i<7;i++)
	{
		cv::Point c=sp::center(bboxes[sort_bboxes[i]]);
		c_list.push_back(c);
	}
	//for(int i=0;i<c_list.size();i++)
		//cv::circle(org,c_list[i],3,{ 255, 0, 0 },-1);
	//对矩形中心点列表一次拟合,拟合得到结果是y=ax+b
	cv::Mat mm=sp::polyfit(c_list,2);
	float b=mm.ptr<float>(0)[0];
	float a=mm.ptr<float>(1)[0];
	//画线
	//org=sp::draw_line(org,a,b);
	int mid=bboxes[sort_bboxes[6]].area()+200;
	int min_dis=10000;
	int flag;
	for(int i=sort_bboxes.size()-1;bboxes[sort_bboxes[i]].area()>mid;i--)
	{
		//cv::rectangle(org, bboxes[sort_bboxes[i]], { 255, 0, 0 },3);
		cv::Point c=sp::center(bboxes[sort_bboxes[i]]);
		double dis=sp::distance(a,b,c);
		if(dis<min_dis)
		{
			min_dis=dis;
			flag=i;
		}
		//std::cout<<"distance:"<<dis<<'\n';
	}
	cv::rectangle(org, bboxes[sort_bboxes[flag]], { 255, 0, 0 },3);
	cv::imwrite("../detect.jpg",org);

}
