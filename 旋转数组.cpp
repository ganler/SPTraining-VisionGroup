#include<iostream>
#include<vector>
using namespace std;
void rotate(vector <int> Array, int k) {
	int length= Array.size();
	k = k % length;
	int temp = 0;
	//vector <int> ::iterator i;
	if ((length % 2 == 0) && (length / 2 == k)) {
		for ( int i = 0; i < k; i++) { 
			temp = Array[i];            
			Array[i] = Array[length - k + i];            
			Array[length - k + i] = temp; 
		}
	}
	else if (length / 2 >= k) {
		for (int i = 0; i < k; i++) {
			temp = Array[i];
			Array[i] = Array[length - k + i];
			Array[length - k + i] = temp;
		}
		for (int j = 0; j < k; j++) {
			for (int i = length - 1; i > k; i--) {
				temp = Array[i - 1];
				Array[i - 1] = Array[i];
				Array[i] = temp;
			}
		}
	}
	else {
		for (int i = 0; i < length - k; i++) {
			temp = Array[i];
			Array[i] =Array[k + i];
			Array[k + i] = temp;
		}
		for (int j = 0; j < length - 2 * (length - k); j++) {
			for (int i = k - 1; i > 0; i--) {
				temp = Array[i - 1];
				Array[i - 1] = Array[i];
				Array[i] = temp;
			}
		}
	}
	for (int i=0; i < length; i++) {
		cout << Array[i] << '\t';
	}
					//cout << Array[0] << Array[1];		
}
int main(){
   int n;
   cout << "输入数组个数n"<<endl;
   cin >> n;
   cout << "输入数组元素" << endl;
   vector <int> Array;
   int arraynumber;
   for (int i = 0; i < n; i++) {
	   cin >> arraynumber;
	   Array.push_back(arraynumber);
   }
   int k;
   cout << "输入k" << endl;
   cin >> k;
   rotate( Array, k);

}

