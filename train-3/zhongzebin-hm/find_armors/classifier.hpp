#pragma once

#include <string>
#include <vector>
#include <utility>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <dirent.h>            // POSIX.(As C++11 doesn't support filesystem)

namespace cf
{

class template_classifier;
using classifier = template_classifier;

class template_classifier
{
public:
	using container_t = std::vector<cv::Mat>;//container_t表示图像容器
	// Constructor，构造函数
	template_classifier(const std::string& g_loc, const std::string& b_loc)//其中loc代表地址
	{  create_templates(g_loc, b_loc);  }
	template_classifier(const std::string& loc)
	{
		if(loc.back() == '/' || loc.back() == '\\')//判断地址字符串最后是否加了/，没加的话加上
			create_templates(loc+"positive", loc+"negative");
		else
			create_templates(loc+"/positive", loc+"/negative");
	}
	inline void create_templates(const std::string& g_loc, const std::string& b_loc)//内联函数相当于直接将代码粘贴到调用处，减少查找函数的时间
	{
		container_t ret;
		good_templates = make_templates_(g_loc);//返回正样本
		bad_templates  = make_templates_(b_loc);//返回负样本
		/*good_templates_debug=good_templates;
		bad_templates_debug=bad_templates;
		for(int i=0;i<good_templates_debug.size();i++)
		{
			auto mat=good_templates_debug[i];
			uint32_t iter_rows = mat.rows;
		        uint32_t iter_cols = mat.cols;
		        auto sum_pixel = iter_rows * iter_cols;
		        if(mat.isContinuous())
		        {	
			        iter_cols = sum_pixel;
			        iter_rows = 1;
		        }
			for (uint32_t i = 0; i < iter_rows; ++i)
	    		{
	        		const auto row_ptr=mat.ptr<uchar>(i);
	        		for (uint32_t j = 0; j < iter_cols; ++j)
				{
	            			uchar value=row_ptr[i*iter_cols+j];
					if(value==1) row_ptr[i*iter_cols+j]=255;
				}
	    		}
			cv::imwrite("../change/"+std::to_string(i)+".png", good_templates_debug[i]);
		}*/
	}
	inline int forward(cv::Mat mat) // noexcept
	{
	    prepare_(mat);
	    int match_id = 0;
	    int now_belief;
	    int max_belief = std::numeric_limits<int>::min();//int型最小值
	    int id = 0;
	    for(; id < good_templates.size(); ++id)//遍历所有的正样本
	    {
	        now_belief = compare_(mat, good_templates[id]);//比较输入图像和正样本，返回当前置信度
	        // std::cout << id << " --- " << now_belief << '\n';
	        if(max_belief < now_belief)//求得对应置信度最大的正样本
	        {
	            max_belief = now_belief;
	            match_id = id;
	        }
	    }
	    if(max_belief < low_bound)//如果最大置信度小于阈值，返回当前id(对应最后的正样本id+1)
	        return id;
	    for(int i = 0; i < bad_templates.size(); ++id, ++i)//遍历所有的负样本
	    {
	        now_belief = compare_(mat, bad_templates[i]);
	        // std::cout << id << " --- " << now_belief << '\n';
	        if(max_belief < now_belief) // 如果当前置信度大于最大置信度，返回最后的正样本id+1
	            return id;
	    }
	    return match_id;//返回匹配的正样本id
	}
	inline bool boolean_forward(cv::Mat& mat)
	{
		return forward(mat) < good_templates.size();//如果成功找到对应的正样本，返回1
	}
	inline void debug_prepared_show(cv::Mat& x)
	{
		debug_prepare_(x);
		cv::imshow("debug", x);
	}
public: // Default values.
	double      thre_proportion = 0.25; // 比例阈值，取直方图中thre_proportion位置亮的像素作为thre，把前0.25亮的元素取1，其余取0
	int         low_bound       = 1000;//最小置信阈值
	cv::Size2i  fixed_sz        = {64, 64};//所有读入的图像都放缩到fixed_sz大小
private:
	// @@@ get_threshold: 按获取一个cv::Mat的阈值
	inline int         get_threshold_(cv::Mat& mat)
	{
	    uint32_t iter_rows = mat.rows;
	    uint32_t iter_cols = mat.cols;
	    auto sum_pixel = iter_rows * iter_cols;
	    if(mat.isContinuous())
	    {
	        iter_cols = sum_pixel;
	        iter_rows = 1;
	    }
	    int histogram[256];
	    memset(histogram, 0, sizeof(histogram));
	    for (uint32_t i = 0; i < iter_rows; ++i)
	    {
	        const uchar* lhs = mat.ptr<uchar>(i);
	        for (uint32_t j = 0; j < iter_cols; ++j)
	            ++histogram[*lhs++];
	    }
	    auto left = thre_proportion * sum_pixel;
	    int i = 255;
	    while((left -= histogram[i--]) > 0);
	    if(std::max(i,0)>5)
	    return std::max(i, 0);
	    else return 255;
	}
	inline void        debug_prepare_(cv::Mat& mat)
	{
		// std::cout << dst_sz << std::endl;
    	cv::resize(mat, mat, fixed_sz);
    	cv::threshold(mat, mat, get_threshold_(mat), 255, cv::THRESH_BINARY);
	}
	// @@@ prepare_
	inline void        prepare_(cv::Mat& mat)
	{
		// std::cout << dst_sz << std::endl;
    	cv::resize(mat, mat, fixed_sz);//放缩图像
    	cv::threshold(mat, mat, get_threshold_(mat), 1, cv::THRESH_BINARY);//二值化图像，前0.25亮取1，反之取0
        }
	// @@@ make_templates_
	inline container_t make_templates_(const std::string& where)
	{
		container_t ret;
		// std::cout << where.c_str() << std::endl;
		DIR* dir_ptr = opendir(where.c_str());//.c_str()返回指向该字符串的指针，形式为char*,dir_ptr为该文件夹目录
		dirent* dptr;
		while((dptr = readdir(dir_ptr)) != NULL)//将dir_ptr目录下的文件信息依次传入dptr中
		{
			if(dptr->d_name[0] == '.')//如果文件名第一位为.则进行下一个
				continue;
			cv::Mat tem;
			if(where.back() == '/')//判断where最后一位是否为/，不是的话就加上
				tem = cv::imread(where+dptr->d_name, cv::IMREAD_GRAYSCALE);
			else
				tem = cv::imread(where+'/'+dptr->d_name, cv::IMREAD_GRAYSCALE);//图像读入tem中
			prepare_(tem);
			ret.push_back(tem);//将变换后的图像放入ret中
		}
		std::cout << "@@@ " << where << " ~ " << ret.size() << " file reading finished.\n";
		return ret;
	}
	// @@@ compare_
	inline int        compare_(cv::Mat& tem, cv::Mat& true_sample)
	{
		uint32_t iter_rows = fixed_sz.height;
	    uint32_t iter_cols = fixed_sz.width;
	    auto sum_pixel = iter_rows * iter_cols;
		if(tem.isContinuous() && true_sample.isContinuous())
	   	{
			iter_cols = sum_pixel;
			iter_rows = 1;
		}
		int same_cnt = 0;
		for (uint32_t i = 0; i < iter_rows; ++i)
		{
			const uchar* lhs = tem.ptr<uchar>(i);
			const uchar* rhs = true_sample.ptr<uchar>(i);
			for (uint32_t j = 0; j < iter_cols; ++j)
			{
		    	bool l = *lhs++, r = *rhs++;
		    	if(!l && !r)//如果l,r都为0，same_cnt不变
		        	continue;
		    	same_cnt += (l && r) ? 3 : -1;//如果l,r都为1，same_cnt+3;如果l,r一个为0一个为1，same_cnt-1
			}
		}
	    return same_cnt;
	}
private:
	container_t good_templates;
	container_t bad_templates;
	//container_t good_templates_debug;
	//container_t bad_templates_debug;
}; // class template_classifier



} // namespace sp
