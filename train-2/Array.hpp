#pragma once
#include <cstddef>
#include <memory>
template<typename T>
class array
{
public:
    //构造函数
    array()=default;
    array(std::size_t n,std::size_t m):rows(n),cols(m)
    {
        data=new T*[n];
        for(int i=0;i<n;i++)
            data[i]=new T[m];
    }
    //析构函数
    ~array(){clear();}
    //复制构造函数
    array(const array& arr){copy_construction(arr);}
    //赋值构造函数
    array& operator = (const array&arr){copy_construction(arr);}
    //移动构造函数
    array(array&& arr){move_construction(arr);}
    //移动赋值函数
    array(array&& arr){move_construction(arr);}
private:
    inline void clear()
    {
        for(int i=0;i<rows;i++)
            if(data[i]!=nullptr) delete []data[i];
        if(data!=nullptr)
            delete []data;
    }
    inline void copy_construction(const array& arr)
    {
        clear();
        data=new T*[rows=arr.rows];
        cols=arr.cols;
        for(int i=0;i<rows;i++)
            data[i]=new T[cols];
        std::memcpy(data,arr.data,sizeof(T)*arr.rows*arr.cols);
    }
    inline void move_construction(const array&& arr)
    {
        std::swap(data,arr.data);
        std::swap(rows,arr.rows);
        std::swap(cols,arr.cols);
    }
private:
    T** data=nullptr;
    std::size_t rows=0;
    std::size_t cols=0;
};
