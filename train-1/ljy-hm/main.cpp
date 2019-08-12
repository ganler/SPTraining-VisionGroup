#include <iostream>
#include "qsort.hpp"
using namespace std;

template <typename Iter>
void OutputArr(Iter arr[], int arr_len)
{
	for (int i = 0; i < arr_len; i++)
	{
		cout << "test_arr[" << i << "]: " << arr[i] << endl;
	}
}

int main()
{
	double test_arr[6] = { 0, 3.8, 2.61 ,2.62, 4.23 ,4.23 };
	int test_arr_len = sizeof(test_arr) / sizeof(double);
	cout << "the test array before sorting:" << endl;
	OutputArr<double>(test_arr, test_arr_len);
	qsort<double>(test_arr, test_arr_len);
	cout << endl << "the test array after sorting:" << endl;
	OutputArr<double>(test_arr, test_arr_len);
	return 0;
}
