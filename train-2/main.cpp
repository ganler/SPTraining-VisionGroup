#include <chrono>
#include <future>  // Use std::async => MultiThreading

#include "classifier.hpp"

class timer
{
public:
	using clk_t = std::chrono::high_resolution_clock;
    timer() : t(clk_t::now()) {}
    void reset(){  t = clk_t::now(); }

    double milli_cnt() const
    {
        return std::chrono::duration<double, std::milli>(clk_t::now() - t).count();
    }

private:
    clk_t::time_point t;
}; // class timer

std::vector<cv::Mat> get_test_src(const std::string& where)
{
	std::vector<cv::Mat> ret;
	DIR* dir_ptr = opendir(where.c_str());
	dirent* dptr;
	while((dptr = readdir(dir_ptr)) != NULL)
	{
		if(dptr->d_name[0] == '.')
			continue;
		ret.push_back(cv::imread(where+'/'+dptr->d_name, cv::IMREAD_GRAYSCALE));
	}
	return ret;
}

auto goods = get_test_src("../data/positive");
auto bads  = get_test_src("../data/negative");
int total = goods.size() + bads.size();
int goods_right = 0;
int bads_right  = 0;
int hardware_asyncs=std::thread::hardware_concurrency();
int block_size=(goods.size()+bads.size())/(hardware_asyncs-1);//减去主线程

int func_goods(sp::classifier& classifier,int i)
{
    int sum=0;
    if((i+1)*block_size>goods.size())
    {
        for(int j=i*block_size;j<goods.size();j++)
            sum+=classifier.boolean_forward(goods[j]);
        return sum;
    }
    for(int j=i*block_size;j<(i+1)*block_size;j++)
        sum+=classifier.boolean_forward(goods[j]);
    return sum;
}

int func_bads(sp::classifier& classifier,int i)
{
    int sum=0;
    if((i+1)*block_size>bads.size())
    {
        for(int j=i*block_size;j<bads.size();j++)
            sum+=!classifier.boolean_forward(bads[j]); 
        return sum;
    }
    for(int j=i*block_size;j<(i+1)*block_size;j++)
        sum+=!classifier.boolean_forward(bads[j]);
    return sum;
}


int main()
{
	sp::classifier classifier("../armor");
	// classifier.debug_prepared_show(cv::imread("../armor/positive/T2.png", cv::IMREAD_GRAYSCALE));
	// cv::waitKey();
	// @@@ test time.
	timer t;
    std::vector<std::future<int>> asyncs(hardware_asyncs-1);
    if(hardware_asyncs==0) hardware_asyncs=8;
    for(int i=0;i<hardware_asyncs-1;i++)
    {
        if(i<=(hardware_asyncs-1)/2) asyncs[i]=std::async(func_goods,std::ref(classifier),i);
        else asyncs[i]=std::async(func_bads,std::ref(classifier),i-(hardware_asyncs-1)/2-1);
    }

    bads_right+=func_bads(classifier,(hardware_asyncs-1)/2);//主线程中运行
    for(int i=0;i<hardware_asyncs-1;i++)//获得结果
    {
        if(i<=(hardware_asyncs-1)/2) goods_right+=asyncs[i].get();
        else bads_right+=asyncs[i].get();
    }

	std::cout << "Average bench time: " << t.milli_cnt() / total << " ms\n";

	std::cout << "goods right: " << goods_right << " / " << goods.size() << " ~ " << static_cast<double>(goods_right) / goods.size() * 100 << " %\n";
	std::cout << "bads  right: " << bads_right  << " / " << bads.size()  << " ~ " << static_cast<double>(bads_right )  / bads.size() * 100<< " %\n";
	std::cout << "Total accuracy: " << static_cast<double>(goods_right + bads_right) / total * 100 << " %\n";

}
