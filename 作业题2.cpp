#include<iostream>
#include<vector>
using namespace std;
void Find(vector <int> Array) {
	int length = Array.size();
	int k = ((1+length)*length)/2;
	vector <int> ::iterator i;
	for (i = Array.begin(); i != Array.end(); i++) {
		k = k - *i;
	}
	cout << k;		
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
	Find(Array);
	return 0;
}

