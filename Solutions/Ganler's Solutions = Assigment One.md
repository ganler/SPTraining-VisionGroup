# Ganler's Solutions => Assigment One

## Rotation

```c++
template<typename C>
		void rotate(C&& container, std::size_t k)
{   // Right Rotation => k;
		auto mid = container.end()-k%container.size();
 		std::reverse(container.begin(), mid);
  	std::reverse(mid, container.end());
  	std::reverse(container.begin(), container.end());
}
```

## Missing Number

```c++
int missingNumber(const vector<int>& nums) 
{ 
  	int ret; // 年轻人，想玩花板子就玩位运算啊，玩什么数列求和哇（滑稽
  	for(int i = 0; i < nums.size(); ++i)
    		ret ^= (nums[i]^(i+1));
  	return ret;
}
```

### Binary Search

```c++
template <typename Iter, typename T>
		bool binary_search(Iter beg, Iter end, const T& val)
{
  	auto term = end;
  	while(std::distance(beg, end) > 0)
      	if(Iter mid = beg + (end - beg) / 2; *mid < val) // C++17
          	beg = mid + 1;
      	else
          	end = mid;
  	return beg != term && *beg == val;
}   // 知乎上有一篇关于二分查找左开右闭的数学证明 ... 有兴趣可以看看
```

### 目前发现的其他问题

- 代码风格；
- `namespace`和ADL（`binary_search`）；
- 用`std::array<>`代替C style的数组（更加安全）；

> 其实我也不是很想和大家说太多和C++标准相关的detail，因为这东西无法速成。所以我尽量和大家讲一些直观上、实用的东西。