#include<iostream>
#include<vector>
using namespace std;

template <typename Iter, typename T>
bool binary_search(Iter beg, Iter end, const T& target) {
	auto  term = end; 
	end--;
	Iter mid;
	while (std::distance(beg, end) > 0) {
		mid = beg + ((end - beg) >> 1);
		cout << *beg << " " << *mid << " " << *end << endl;
		if (*mid < target)
			beg = mid + 1;
		else
			end = mid;
	}
	if ( *beg == target) cout << *beg;
	return *beg == target;
}
int main() {
	int n;
	cout << "输入数组个数n" << endl;
	cin >> n;
	cout << "输入数组元素" << endl;
	vector <int> Array;
	int arraynumber;
	for (int i = 0; i < n; i++) {
		cin >> arraynumber;
		Array.push_back(arraynumber);
	}
	int target;
	cout << "输入target" << endl;
	cin >> target;
	vector <int> ::iterator beg;
	beg = Array.begin();
	vector <int> ::iterator end;
	end = Array.end();
	binary_search(beg, end, target);
}