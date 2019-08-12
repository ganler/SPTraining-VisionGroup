#pragma once

template <typename Iter>
void qsort_recursive(Iter arr[], int beg, int end)
{
	if (beg >= end)
	{
		return;
	}
	Iter mid = arr[end];
	int right = end - 1;
	int left = beg;
	while (left < right)
	{ 
		while (arr[left] < mid && left < right)
		{
			left++;
		}
		while (arr[right] >= mid && left < right)
		{
			right--;
		}
		std::swap(arr[left], arr[right]);
	}
	if (arr[left] >= arr[end])
	{
		std::swap(arr[left], arr[end]);
	}
	else
	{
		left++;
	}
	qsort_recursive(arr, beg, left - 1);
	qsort_recursive(arr, left + 1, end);
}

template <typename Iter>
void qsort(Iter arr[], int arr_len)
{
	qsort_recursive(arr, 0, arr_len - 1);
}
