#pragma once
#include <string>
#include <vector>
#include <utility>
#include <iostream>

#include <opencv2/opencv.hpp>
#include "dirent.h"            
#undef min
#undef max
namespace sp
{

	class template_classifier;
	using classifier = template_classifier;

	class template_classifier
	{
	public:
		using container_t = std::vector<cv::Mat>;
		template_classifier(const std::string& g_loc, const std::string& b_loc)
		{
			create_templates(g_loc, b_loc);
		}
		template_classifier(const std::string& loc)
		{
			if (loc.back() == '/' || loc.back() == '\\')
				create_templates(loc + "positive", loc + "negative");
			else
				create_templates(loc + "/positive", loc + "/negative");
		}
		inline void create_templates(const std::string& g_loc, const std::string& b_loc)
		{
			//container_t ret;
			good_templates = make_templates_(g_loc);
			bad_templates = make_templates_(b_loc);
		}
		inline int forward(cv::Mat mat) 
		{
			prepare_(mat);
			int match_id = 0;
			int now_belief;
			int max_belief = std::numeric_limits<int>::min();
			int id = 0;
			for (; id < good_templates.size(); ++id)
			{
				now_belief = compare_(mat, good_templates[id]);
				if (max_belief < now_belief)
				{
					max_belief = now_belief;
					match_id = id;
				}
			}
			if (max_belief < low_bound)
				return id;
			for (int i = 0; i < bad_templates.size(); ++id, ++i)
			{
				now_belief = compare_(mat, bad_templates[i]);
				if (max_belief < now_belief)
					return id;
			}
			return match_id;
		}
		inline bool boolean_forward(cv::Mat& mat)
		{
			return forward(mat) < good_templates.size();
		}
	public: 
		double      thre_proportion = 0.25; 
		int         low_bound = 1000;
		cv::Size2i  fixed_sz = { 64, 64 };
	private:
		inline int         get_threshold_(cv::Mat& mat)
		{
			uint32_t iter_rows = mat.rows;
			uint32_t iter_cols = mat.cols;
			auto sum_pixel = iter_rows * iter_cols;
			if (mat.isContinuous())
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
			while ((left -= histogram[i--]) > 0);
			return std::max(i, 0);
		}
		inline void        prepare_(cv::Mat& mat)
		{
			cv::resize(mat, mat, fixed_sz);
			cv::threshold(mat, mat, get_threshold_(mat), 1, cv::THRESH_BINARY);
		}
		inline container_t make_templates_(const std::string& where)
		{
			container_t ret;
			DIR* dir_ptr = opendir(where.c_str());
			dirent* dptr;
			while ((dptr = readdir(dir_ptr)) != NULL)
			{
				if (dptr->d_name[0] == '.')
					continue;
				cv::Mat tem;
				if (where.back() == '/')
					tem = cv::imread(where + dptr->d_name, cv::IMREAD_GRAYSCALE);
				else
					tem = cv::imread(where + '/' + dptr->d_name, cv::IMREAD_GRAYSCALE);
				prepare_(tem);
				ret.push_back(tem);
			}
			std::cout << "@@@ " << where << " ~ " << ret.size() << " file reading finished.\n";
			return ret;
		}
		inline int        compare_(cv::Mat& tem, cv::Mat& true_sample)
		{
			uint32_t iter_rows = fixed_sz.height;
			uint32_t iter_cols = fixed_sz.width;
			auto sum_pixel = iter_rows * iter_cols;
			if (tem.isContinuous() && true_sample.isContinuous())
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
					if (!l && !r)
						continue;
					same_cnt += (l && r) ? 3 : -1;
				}
			}
			return same_cnt;
		}
	private:
		container_t good_templates;
		container_t bad_templates;
	}; 



}