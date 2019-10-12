#Submission1

## Code

### fork

```bash
#bash
git clone https://github.com/Homura2333/SPTraining-VisionGroup
```

### install googletest

```bash
#bash
git clone https://github.com/google/googletest.git
cd googletest
mkdir mybuild
cd mybuild
cmake ..
sudo make
sudo make install
```

### intall folly

```shell
#bash
git clone https://github.com/facebook/folly.git
```

```bash
#install dependency libs according to README.md
sudo apt-get install \
    g++ \
    cmake \
    libboost-all-dev \
    libevent-dev \
    libdouble-conversion-dev \
    libgoogle-glog-dev \
    libgflags-dev \
    libiberty-dev \
    liblz4-dev \
    liblzma-dev \
    libsnappy-dev \
    make \
    zlib1g-dev \
    binutils-dev \
    libjemalloc-dev \
    libssl-dev \
    pkg-config
```

```bash
cd folly
mkdir mybuild
cd mybuild
cmake ..
sudo make
sudo make install
```

### OpenCV

```bash
#bash
mkdir opencv
cd opencv
touch video.cpp
touch CMakeLists.txt
```

```cmake
#CMakeLists.txt
cmake_minimum_required (VERSION 2.8)
project (video)
find_package(OpenCV REQUIRED)
add_executable(video video.cpp)
target_link_libraries(video ${OpenCV_LIBS})
```

```cpp
//video.cpp
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>  
#include "opencv2/videoio.hpp"

using namespace cv;
 
int main()
{
    VideoCapture capture(0);
    VideoWriter writer("video_original.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25.0, Size(640, 480));
    Mat frame;
    Mat edges;
 
    while (capture.isOpened())
    {
        capture >> frame;
        writer << frame;
        imshow("video_original", frame);
        if (cvWaitKey(20) >= 0)		//按回车键停止录制
        {
        	capture.release();
            break;
        }
    }

    VideoCapture readcap;
    readcap.open("video_original.avi");
    while (1)
    {
    	readcap>>frame;
    	if (frame.empty())
    		break;
    	cvtColor(frame,edges,CV_BGR2GRAY);		//灰度化
   		threshold(edges, edges, 120, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);   //二值化
    	imshow("video_binarization",edges);
    	if (waitKey(20)>=0)
    		break;
    }
    readcap.release();
    return 0;
}
```

```bash
#bash
mkdir build && cd build
cmake .. && make
./video
```

### LeetCode

#### 189

```cpp
//LeetCode189.cpp
#include <iostream>
#include <vector>

template<typename T>
void rotate(T &arr,int k)
{
	k=k%arr.size();
	std::cout<<arr.size()<<"\n";
	int cnt=0;
	for (int st=0;cnt<arr.size();st++)
	{
		int cur=st;
		auto save=arr[st];
		do
		{
			int next=(cur+k)%arr.size();
			auto tmp=arr[next];
			arr[next]=save;
			save=tmp;
			cur=next;
			cnt++;
		}while (cur!=st);
	}
}

int main()
{
	int n,k;
	std::vector<int> arr;
	std::cout<<"Please input n,k:\n";
	std::cin>>n>>k;
	std::cout<<"Please input numbers:\n";
	while (n--)
	{
		int tmp;
		std::cin>>tmp;
		arr.push_back(tmp);
	}
	rotate(arr,k);
	for (auto it=arr.begin();it!=arr.end();it++)
		std::cout<<(*it)<<" ";
	std::cout<<"\n";
	return 0;
}
```

#### 268

```cpp
//LeetCode268.cpp
#include <iostream>
#include <vector>

int find(std::vector<int> vec)
{
	int sum=0;
	for (int i=0;i<vec.size()+1;i++)
		sum+=i;
	for (auto&& x:vec)
		sum-=x;
	return sum;
}
int main()
{
	int n;
	std::vector<int> vec;
	std::cout<<"Please input n:\n";
	std::cin>>n;
	std::cout<<"Please input numbers:\n";
	while (n--)
	{
		int tmp;
		std::cin>>tmp;
		vec.push_back(tmp);
	}
	std::cout<<find(vec)<<"\n";
	return 0;
}
```

### binary search

```cpp
template<typename Iter,typename T>
bool binary_search(Iter beg,Iter end,T&& val)
{
	while (beg<=end)
	{
		Iter mid=beg+(end-beg)/2;	
		if (val==*(mid))
			return true;
		if (val>*(mid))
			beg=mid+1;
		else
			end=mid-1;
	}
	return false;
}
```

## Questions
在openCV的那个作业中，之前尝试了和保存原视频一样的方式保存二值化后的视频，但是保存完后无法双击点开该视频，会提示“无法解码多工传送的流”，这是为什么？

