#pragma once

#include <string>
#include <vector>
#include <utility>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <dirent.h>            // POSIX.(As C++11 doesn't support filesystem)

/*首先从文件中读取正负样本，然后读取测试图片，调整图片大小与样本图片
尺寸一样将测试图片灰度化和特定阈值二值化(像素值置为1或0)，将测试图片
与样本中图片相同位置像素(1/0)比较，得出总分数，即可得出是否属于正样本
或负样本中图片*/

namespace sp
{

class template_classifier;
using classifier = template_classifier;

class template_classifier
{
public:
	using container_t = std::vector<cv::Mat>;
	// Constructorzz
	template_classifier(const std::string& g_loc, const std::string& b_loc)
	{  create_templates(g_loc, b_loc);  }
	template_classifier(const std::string& loc)//1不同的构造函数
	{
		if(loc.back() == '/' || loc.back() == '\\')
			create_templates(loc+"positive", loc+"negative");
		else
			create_templates(loc+"/positive", loc+"/negative");
	}
	inline void create_templates(const std::string& g_loc, const std::string& b_loc)
	{
		container_t ret;
		good_templates = make_templates_(g_loc);
		bad_templates  = make_templates_(b_loc);
	}
	inline int forward(cv::Mat mat) // noexcept
	{
	    prepare_(mat);
	    int match_id = 0;
	    int now_belief;
	    int max_belief = std::numeric_limits<int>::min();//4取int型最小值
	    int id = 0;
	    for(; id < good_templates.size(); ++id)
	    {
	        now_belief = compare_(mat, good_templates[id]);
	        // std::cout << id << " --- " << now_belief << '\n';
	        if(max_belief < now_belief)
	        {
	            max_belief = now_belief;
	            match_id = id;
	        }
	    }
	    if(max_belief < low_bound)
	        return id;
	    for(int i = 0; i < bad_templates.size(); ++id, ++i)
	    {
	        now_belief = compare_(mat, bad_templates[i]);
	        // std::cout << id << " --- " << now_belief << '\n';
	        if(max_belief < now_belief) // 直接返回
	            return id;
	    }
	    return match_id;
	}
	inline bool boolean_forward(cv::Mat& mat)
	{
		return forward(mat) < good_templates.size();
	}
	inline void debug_prepared_show(cv::Mat& x)
	{
		debug_prepare_(x);
		cv::imshow("debug", x);
	}
public: // Default values.
	double      thre_proportion = 0.25; // 比例阈值，取直方图中thre_proportion位置亮的像素作为thre
	int         low_bound       = 1000;
	cv::Size2i  fixed_sz        = {64, 64};
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
	    return std::max(i, 0);
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
    	cv::resize(mat, mat, fixed_sz);//3图片大小修改为64*64
    	cv::threshold(mat, mat, get_threshold_(mat), 1, cv::THRESH_BINARY);//二值化
	}
	// @@@ make_templates_
	inline container_t make_templates_(const std::string& where)
	{
		container_t ret;
		// std::cout << where.c_str() << std::endl;
		DIR* dir_ptr = opendir(where.c_str());
		dirent* dptr;
		while((dptr = readdir(dir_ptr)) != NULL)
		{
			if(dptr->d_name[0] == '.')
				continue;
			cv::Mat tem;
			if(where.back() == '/')
				tem = cv::imread(where+dptr->d_name, cv::IMREAD_GRAYSCALE);
			else//2读取图片
				tem = cv::imread(where+'/'+dptr->d_name, cv::IMREAD_GRAYSCALE);
			prepare_(tem);
			ret.push_back(tem);
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
		    	if(!l && !r)
		        	continue;
		    	same_cnt += (l && r) ? 3 : -1;
			}
		}
	    return same_cnt;
	}
private:
	container_t good_templates;
	container_t bad_templates;
}; // class template_classifier

} // namespace sp
