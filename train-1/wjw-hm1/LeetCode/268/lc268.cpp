#include <iostream>
#include <vector>

int find(std::vector<int> vec)
{
	int sum=0;
	for (int i=0;i<vec.size()+1;i++)
		sum+=i;
	for (auto&& x:vec)
		sum-=x;
	return sum;
}
int main()
{
	int n;
	std::vector<int> vec;
	std::cout<<"Please input n:\n";
	std::cin>>n;
	std::cout<<"Please input numbers:\n";
	while (n--)
	{
		int tmp;
		std::cin>>tmp;
		vec.push_back(tmp);
	}
	std::cout<<find(vec)<<"\n";
	return 0;
}