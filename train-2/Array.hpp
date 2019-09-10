#pragma once
#include <cstddef>
#include <memory>
#include <cstring>
template<typename T>
class Array
{
public:
    //构造函数
    Array()=default;
    Array(std::size_t n,std::size_t m):rows(n),cols(m)
    {
        data=new T*[n];
        for(int i=0;i<n;i++)
            data[i]=new T[m];
    }
    //析构函数
    ~Array(){clear();}
    //复制构造函数
    Array(const Array& arr){copy_construction(arr);}
    //赋值构造函数
    Array& operator = (const Array&arr){copy_construction(arr);}
    //移动构造函数
    Array(Array&& arr){move_construction(arr);}
    //移动赋值函数
    Array& operator = (Array&& arr){move_construction(arr);}
private:
    inline void clear()
    {
        for(int i=0;i<rows;i++)
            if(data[i]!=nullptr) delete []data[i];
        if(data!=nullptr)
            delete []data;
    }
    
    inline void copy_construction(const Array& arr)
    {
        clear();
        data=new T*[rows=arr.rows];
        cols=arr.cols;
        for(int i=0;i<rows;i++)
            data[i]=new T[cols];
        std::memcpy(data,arr.data,sizeof(T)*arr.rows*arr.cols);
    }
    
    inline void move_construction(const Array&& arr)
    {
        if(this!=&arr)
        {
            clear();
            data=arr.data;
            arr.data=nullptr;
            rows=arr.rows;
            cols=arr.cols;
        }
        return *this;
    }
    
public:
    T** data=nullptr;
    std::size_t rows=0;
    std::size_t cols=0;
};
