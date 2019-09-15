#pragma once
#include<cstddef>
#include<memory>
#define ERROR -1
#define RIGHT  1
namespace sp {
	template <typename T> class array2D {
		using value_type = T;
	public:
		array2D() = default;
		array2D(std::size_t l, std::size_t w)
			: m_data(new value_type[l*w]), m_height(l), m_width(w) {}
		value_type getelem(const std::size_t l, const std::size_t w)
		{
			return return_value(l, w);
		}
		void give_value(const T data,const std::size_t l,const std::size_t w) 
    //对特定位置的数组值进行赋值
		{
			give_element_value(data, l, w);
		}
		void arr_broaden(const std::size_t l, const std::size_t w)        //对数组进行扩容
		{
			array2D_broaden(l, w);                            
		}
		~array2D()
		{
			clear();
		}
		array2D(const array2D<T> &arr)
		{
			copy_construction(arr);
		}
		array2D<T> &operator=(const array2D<T> &arr)
		{
			copy_construction(arr);
			return *this;
		}
		array2D(array2D<T> &&arr)
		{
			move_construction(std::move(arr));
		}
		array2D<T> &operator=(array2D<T> &&arr)
		{
			move_construction(std::move(arr));
			return *this;
		}
	private:
		value_type *m_data = nullptr;
		std::size_t m_height = 0;
		std::size_t m_width = 0;
		value_type return_value(const std::size_t l, const std::size_t w)
		{
			return *(m_data + l * m_width + w);
		}
		void array2D_broaden(const std::size_t l, const std::size_t w)
		{
			value_type *data = nullptr;
			if (l > m_height && w>m_width) {
				data = new value_type[l*w];
				memcpy(data, m_data, sizeof(value_type)*m_height*m_width);
				m_height = l;
				m_width = w;
				delete[]m_data;
			}
			else if (l > m_height) {
				data = new value_type[l*m_width];
				memcpy(data, m_data, sizeof(value_type)*m_height*m_width);
				m_height = l;
				delete[]m_data;
			}
			else if (w > m_width) {
				data = new value_type[m_height*w];
				memcpy(data, m_data, sizeof(value_type)*m_height*m_width);
				m_width = w;
				delete[]m_data;
			}
			m_data = data;
		}
		int give_element_value(const T data, const std::size_t l, const std::size_t w)
		{
			if (l >= m_height || w >= m_width)
				return ERROR;
			*(m_data + l * m_width + w) = data;
			return RIGHT;
		}
		void clear()
		{
			if (m_data != nullptr) 
				delete[]m_data;
		}
		void copy_construction(const array2D<T> &arr)
		{
			clear();
			m_data = new value_type[(m_height = arr.m_height)*(m_width = arr.m_width)];
			std::memcpy(m_data, arr.m_data, sizeof(value_type)*arr.m_height*arr.m_width);
		}
		void move_construction(array2D<T> &&arr) noexcept
		{
			std::swap(m_data, arr.m_data);
			std::swap(m_width, arr.m_width);
			std::swap(m_height, arr.m_height);
		}
	};
}
