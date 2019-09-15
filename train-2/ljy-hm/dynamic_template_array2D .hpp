#pragma once

#include <cstddef>
#include <memory>

const int kDynamicMemoryFailed = -1;

namespace sp
{
	template <class iter>
	class DynamicTemplateArray2D
	{
	public:
		using value_type = iter;
		//Constructor
		DynamicTemplateArray2D() = default;
		DynamicTemplateArray2D(std::size_t r, std::size_t c = 1)
		{
			m_r_size_ = r;
			m_c_size_ = c;
			m_data_ = new(std::nothrow)value_type * [r];
			if (NULL == m_data_)
			{
				std::cout << "Dynamic 2D array memory application failed." << std::endl;
				std::exit(kDynamicMemoryFailed);
			}
			for (auto i = 0; i < c; i++)
			{
				m_data_[i] = new(std::nothrow)value_type[c];
				if (NULL == m_data_)
				{
					std::cout << "Dynamic 2D array memory application failed." << std::endl;
					std::exit(kDynamicMemoryFailed);
				}
			}
		}
		//Deconstructor
		~DynamicTemplateArray2D()
		{
			clear();
		}
		//Copy Constructor
		DynamicTemplateArray2D(const DynamicTemplateArray2D& arr)
		{
			CopyConstructor(arr);
		}
		//Copy Assignment
		DynamicTemplateArray2D& operator=(const DynamicTemplateArray2D& arr)
		{
			CopyConstructor(arr);
		}
		//Move Constructor
		DynamicTemplateArray2D(const DynamicTemplateArray2D&& arr)noexcept
		{
			MoveConstructor(arr);
		}
		//Move Assignment
		DynamicTemplateArray2D& operator=(const DynamicTemplateArray2D&& arr)noexcept
		{
			MoveConstructor(arr);
		}
	private:
		void MoveConstructor(const DynamicTemplateArray2D& arr)noexcept
		{
			for (auto i = 0; i < m_r_size_; i++)
			{
				std::swap(m_data_[i], arr.m_data_[i]);
			}
			std::swap(m_r_size_, arr.m_r_size_);
			std::swap(m_c_size_, arr.m_c_size_);
		}
		void CopyConstructor(const DynamicTemplateArray2D& arr)
		{
			clear();
			m_r_size_ = arr.m_r_size_;
			m_c_size_ = arr.m_c_size_;
			m_data_ = new(std::nothrow)value_type * [m_r_size_];
			if (NULL == m_data_)
			{
				std::cout << "Dynamic 2D array memory application failed." << std::endl;
				std::exit(kDynamicMemoryFailed);
			}
			for (auto i = 0; i < m_c_size_; i++)
			{
				m_data_[i] = new(std::nothrow)value_type[m_c_size_];
				if (NULL == m_data_)
				{
					std::cout << "Dynamic 2D array memory application failed." << std::endl;
					std::exit(kDynamicMemoryFailed);
				}
			}
			for (auto i = 0; i < m_r_size_; i++)
			{
				std::memcpy(m_data_[i], arr.m_data_[i], sizeof(value_type) * arr.m_c_size_);
			}
		}
		void clear()noexcept
		{
			delete[] m_data_;
		}
		iter** m_data_ = nullptr;
		std::size_t m_r_size_ = 0;
		std::size_t m_c_size_ = 0;
	};
}
