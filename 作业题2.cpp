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
	cout << "�����������n" << endl;
	cin >> n;
	cout << "��������Ԫ��" << endl;
	vector <int> Array;
	int arraynumber;
	for (int i = 0; i < n; i++) {
		cin >> arraynumber;
		Array.push_back(arraynumber);
	}
	Find(Array);
	return 0;
}

