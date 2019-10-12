#include <iostream>
#include <vector>

template<typename T>
void rotate(T &arr,int k)
{
	k=k%arr.size();
	std::cout<<arr.size()<<"\n";
	int cnt=0;
	for (int st=0;cnt<arr.size();st++)
	{
		int cur=st;
		auto save=arr[st];
		do
		{
			int next=(cur+k)%arr.size();
			auto tmp=arr[next];
			arr[next]=save;
			save=tmp;
			cur=next;
			cnt++;
		}while (cur!=st);
	}
}

int main()
{
	int n,k;
	std::vector<int> arr;
	std::cout<<"Please input n,k:\n";
	std::cin>>n>>k;
	std::cout<<"Please input numbers:\n";
	while (n--)
	{
		int tmp;
		std::cin>>tmp;
		arr.push_back(tmp);
	}
	rotate(arr,k);
	for (auto it=arr.begin();it!=arr.end();it++)
		std::cout<<(*it)<<" ";
	std::cout<<"\n";
	return 0;
}