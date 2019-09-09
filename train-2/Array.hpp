#pragma once
#include <cstddef>
#include <memory>
template<typename T>
class Array
{
public:
    //构造函数
    array()=default;
    array(std::size_t n):size(n),data(new T[n]){}
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
        if(data!=nullptr)
            delete []data;
    }
    inline void copy_construction(const array& arr)
    {
        clear();
        data=new T[size=arr.size];
        std::memcpy(data,arr.data,sizeof(T)*arr.size)
    }
    inline void move_construction(const array&& arr)
    {
        std::swap(data,arr.data);
        std::swap(size,arr.size);
    }
private:
    T* data=nullptr;
    std::size_t size=0;
};