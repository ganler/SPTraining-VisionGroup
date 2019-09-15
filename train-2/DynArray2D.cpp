// DynArray2D.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "DYN_ARRAY_2D.hpp"
#include <iostream>
using namespace std;
int main()
{
	dynArray2D<double> ls(3, 2);
	for (int i = 0; i < 6; i++)
		ls.push(i);

	ls.push(6);
	cout << ls.row << endl;
	for (int i = 0; i < 7; i++)
		cout << *(ls.begin() + i) << " " << ls.begin() + i << endl;
	cout << endl;

	ls.change(2, 1, 2);
	for (int i = 0; i < 8; i++)
		cout << *(ls.begin() + i) << " " << ls.begin() + i << endl;
	cout << endl;

	cout << *ls.begin() << " " << *ls.end() << endl;
	ls.erase(1, 1);
	for (int i = 0; i < 8; i++)
		cout << *(ls.begin() + i) << " " << ls.begin() + i << endl;
	cout << endl;


	ls.clear();
	for (int i = 0; i < 8; i++)
		cout << *(ls.begin() + i) << " " << ls.begin() + i << endl;
	cout << endl;



	dynArray2D<double> lsa(2, 2);
	lsa.push(1);
	ls = std::move(lsa);
	for (int i = 0; i < ls.size; i++)
		cout << *(ls.begin() + i) << " " << ls.begin() + i << endl;
	cout << endl;

	getchar();

	

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
