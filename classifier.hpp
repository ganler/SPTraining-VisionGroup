#pragma once

#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <sys/types.h>
#include <opencv2/opencv.hpp>
#include <dirent.h> 
namespace sp
{
    class template_classifier;
    using classifier=template_classifier;
    class template_classifier
    {
        public:
            using container_t = std::vector<cv::Mat>;
            //加载图片
            template_classifier(const std::string &g_loc,const std::string&b_loc)
            {
                create_templates(g_loc,b_loc);
            }
            template_classifier(const std::string& loc)
            {
                if(loc.back() == '/' || loc.back() == '\\')
			        create_templates(loc+"positive", loc+"negative");
		        else
			        create_templates(loc+"/positive", loc+"/negative");
            }

            inline void create_templates(const std::string &g_loc,const std::string&b_loc)
            {
                container_t ret;
		        good_templates = make_templates_(g_loc);
	        	bad_templates  = make_templates_(b_loc);
            }
            
            double thresholding=0.25;
            cv::Size2i fixed_sz={64,64};
            int low_bound=1000;
            

        private:
            container_t good_templates;
            container_t bad_templates;
            
            inline void prepare_(cv::Mat& mat)
            {
                cv::resize(mat,mat,fixed_sz);
                cv::threshold(mat,mat,get_threshold_(mat),1,cv::THRESH_BINARY);
            }

            inline int get_threshold_(cv::Mat& mat)
            {
                int histogram[256];
                memset(histogram, 0, sizeof(histogram));
                int rows=mat.rows;
                int cols=mat.cols;
                int sum=rows*cols;
                if(mat.isContinuous())
                {
                    rows=1;
                    cols=sum;
                }
                for(int i=0;i<rows;i++)
                {
                    uchar* row_ptr=mat.ptr<uchar>(i);
                    for(int j=0;j<cols;j++)
                    {
                        histogram[*(row_ptr)]++;
                        row_ptr++;
                    }
                }
                int choose=thresholding*sum,i=255;
                for(;i>=0;i--)
                {
                    choose=choose-histogram[i];
                    if(choose<0) break;
                }
                return std::max(i,0);
            }

            inline int compare_(cv::Mat& tem,cv::Mat& true_sample)
            {
                int rows=fixed_sz.height;
                int cols=fixed_sz.width;
                int sum=rows*cols;
                int score=0;
                if(tem.isContinuous()&&true_sample.isContinuous())
                {
                    rows=1;
                    cols=sum;
                }
                for(int i=0;i<rows;i++)
                {
                    uchar* tem_ptr=tem.ptr<uchar>(i);
                    uchar* sample_ptr=true_sample.ptr<uchar>(i);
                    for(int j=0;j<cols;j++)
                    {
                        bool tem=*tem_ptr++,sample=*sample_ptr++;
                        if(!tem&&!sample) continue;
                        if(tem&&sample) score+=3;
                        else score-=1;
                    }
                }
                return score;
            }
            
            inline container_t make_templates_(const std::string& dir)
            {
                container_t ret;
                DIR* dir_ptr=opendir(dir.c_str());
                dirent* dptr;
                while((dptr=readdir(dir_ptr))!=NULL)
                {
                    if(dptr->d_name[0]=='.') continue;
                    cv::Mat tem;
                    if(dir.back()=='/')
                        tem=cv::imread(dir+dptr->d_name,cv::IMREAD_GRAYSCALE);
                    else
                        tem=cv::imread(dir+'/'+dptr->d_name,cv::IMREAD_GRAYSCALE);
                    prepare_(tem);
                    ret.push_back(tem);
                }
                std::cout << "@@@ " << dir << " ~ " << ret.size() << " file reading finished.\n";
		        return ret;
            }



        public:
            inline int forward(cv::Mat& mat)
            {
                prepare_(mat);
                int match_id=0;
                int now_score;
                int max_score=std::numeric_limits<int>::min();
                int id=0;
                for(;id<good_templates.size();id++)
                {
                    now_score=compare_(mat,good_templates[id]);
                    if(now_score>max_score)
                    {
                        max_score=now_score;
                        match_id=id;                       
                    }
                }
                if(max_score<low_bound) return id;
                for(int i=0;i<bad_templates.size();i++,id++)
                {
                    now_score=compare_(mat,bad_templates[i]);
                    if(now_score>max_score) return id;
                }
                return match_id;

            }

            inline bool boolean_forward(cv::Mat& mat)
            {
                return forward(mat)<good_templates.size();
            }
    };
}