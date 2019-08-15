#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include <time.h>
using namespace std;

const int test_array_num = 10;

template <typename T>
void my_qsort(T data[], int first, int last)
{
//first和last为排序区间的长度，left和right分别为左指针和右指针
//以每个区间第一个数作为该区间的参考值
	int left = first + 1;
	int right = last;
	T target = data[first];

	while (left <= right)
	{
		while (data[left] < target)
		{
			left++;
		}
		while (data[right] > target)
		{
			right--;
		}

		if (left < right)
		{
		//此时左指针指的数比右指针指的数大
			swap(data[left], data[right]);
			left++;
			right--;
		}
		else
		{
		//此时left、right指向同一个数，此时这个数必定等于target
			break;
		}
	}

	//因为是与数组的第一个交换，所以是与data[right]互换
	swap(data[right], data[first]);
	//此后right指向分界线

	if (first < right - 1)
	{
		my_qsort(data, first, right - 1);
	}
	if (right + 1 < last)
	{
		my_qsort(data, right + 1, last);
	}
}

template <typename T>
void print_array(T data[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

int main()
{
	int test_array[test_array_num];
	srand((unsigned int)time(nullptr));
	for (int i = 0; i < test_array_num; i++)
	{
		test_array[i] = rand() % 100;
	}

	cout << "before sort:" << endl;
	print_array(test_array, test_array_num);

	my_qsort(test_array, 0, test_array_num - 1);

	cout << "after sort:" << endl;
	print_array(test_array, test_array_num);

	return 0;
}