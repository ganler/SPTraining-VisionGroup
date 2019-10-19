# Plan for this week

## Learning

### Errors

一般这边说的错误有2类：编译期错误和运行期错误；

我们思考一下我们从源文件到可执行文件的flow:

- 写代码
- 编译成可执行文件（凉了~编译期错误=>明显的错误）
- 执行可执行文件（凉了~运行期错误=>`有异常机制 ? 明显的错误 : 看不懂的错误;`）

#### 怎么处理编译期（静态）错误

编译期错误有：

- 词法上的：你输入了不识别的符号，那么别用这个符号就好；
- 语法上的：你违法了C++的语法规则，比如`struct`&`class`后不加`;`
- 类型相关：类型不匹配，报错会告诉你哪些地方没匹配上，认真读读注释就好，解决方案一般是写正确类型，如果（一般是你开始模板元编程了）出现不好处理的类型约束情况，需要用到`type_traits`；

如何处理我说了，当你写一个库的时候，需要自己增加静态报错（请自行理解静态和动态的区别）的话，可以用`static_assert`：

```c++
#include <type_traits>
template <typename T>
void lyxnb(T v)
{
    static_assert(std::is_same<T, int>::value, "T is not int !!!");
}

int main()
{
    lyxnb(1.);
}
 // 然后你看到了这样的报错
/*

/Users/ganler-mac/CLionProjects/CXX_TEST/main.cpp:5:5: error: static_assert failed due to requirement 'std::is_same<double, int>::value' "T is not int !!!"
    static_assert(std::is_same<T, int>::value, "T is not int !!!");
    ^             ~~~~~~~~~~~~~~~~~~~~~~~~~~~
/Users/ganler-mac/CLionProjects/CXX_TEST/main.cpp:10:5: note: in instantiation of function template specialization 'lyxnb<double>' requested here
    lyxnb(1.);
    ^
```

最后你如果gcc的编译信息看不懂，那么就用clang吧；

#### 怎么处理运行期（动态）错误

有哪些错误：

- 解引用nullptr
- 数组越界（或者指针瞎指）
- double free
- diy异常
- assert失败
- 你干了线程不安全的事情
- `Process finished with exit code XXXX`

其中segmentation fault（其实就是违规访问到了当前段区之外的地方(或者说是访问到了不可以访问的地方，即受系统保护的地方或则不存在的地方)，详见任一本OS的书的分段部分），有这些常见的例子：

- 栈数组太大（栈空间有限） ~ 栈不够用堆（申请动态内存）就行（为什么堆看上去可以没有大小限制我只能说你需要看看OS的书（stackoverflow很容易造成segmentation fault）
- 指针数组越界（<u>对于STL的话，可以用`.at()`代替索引</u>，这样越界的时候会用异常报错，可读性杠杠的，但会有性能开销）

> Stack overflow is [a] cause, segmentation fault is the result.
>
> ------
>
> At least on x86 and ARM, the "stack" is a piece of memory reserved for placing local variables and return addresses of function calls. When the stack is exhausted, the memory outside of the reserved area will be accessed. But the app did not ask the kernel for this memory, thus a SegFault will be generated for memory protection.
>
> Ref: https://stackoverflow.com/questions/2685413/what-is-the-difference-between-a-segmentation-fault-and-a-stack-overflow

**确定错误**：看报错信息，如果你不用异常啥的可能啥信息都看不到，这个时候你需要设置断点进行debug（使用IDE自带的工具或者gdb,lldb之类的）

##### assert和异常

[link](https://www.zhihu.com/question/24461924)

##### 遇到看不懂的bug或信息不够的话就打断点吧 ~ 

学一学GDB；（不是什么时候都有IDE用的）

- [https://wiki.ubuntu.org.cn/%E7%94%A8GDB%E8%B0%83%E8%AF%95%E7%A8%8B%E5%BA%8F](https://wiki.ubuntu.org.cn/用GDB调试程序)
- https://oi.men.ci/gnu-debugger/



---



### 写一些东西帮助debug

你写代码，写着写着就崩了，我也很难受，因为我不懂怎么de你处心积虑酝酿的BUG，所以你可以写点帮助debug的东西，这很重要，把这个搞好了，比赛的时候就有时间睡觉了。

当然，千万别瞎搞一些中间`cout`的东西，因为我们希望出了问题才显示，你没出问题满屏跑飞各种输出，我会让你以后别碰键盘的（🤦‍♂️

举例，我们会在项目里面写一个`SP_ASSERT(X)`，然后你需要保证X这个表达式的返回值是`true`，我会这么写：

```c++
#include <iostream>

#define SP_ASSERT(X)\
{\
    if(!(X))\
    {\
				std::cerr                					             \
        << ">>> ASSERT FAILED -> in line "     	  	   \
        << __LINE__ << ": \n\t-> " << #X               \
        << "\n\t-> at " << __PRETTY_FUNCTION__ << '\n';\
    		std::exit(-1); \
		}\
}

int main()
{
    SP_ASSERT(1==2);
}
```

> Exception一般我们不用，因为我们不处理异常，直接` std::exit(-1) ` 挂掉就好；



---

### Compile Flags

[https://github.com/ganler/GanlerCS/blob/master/Cpp/CodeOptimization/GCC%20Optimization.md](https://github.com/ganler/GanlerCS/blob/master/Cpp/CodeOptimization/GCC Optimization.md)



---

### 多线程(Optional & 长期)

> 帮助想学多线程的人入门。

- Cpp Concurrency in Action （群资料）前三章
- 3 easy pieces：Concurrency部分的前三章
- https://segmentfault.com/a/1190000016171072 这个中文教程挺友好的

> 切记，并发编程的重中之重是你对操作系统并发那一块的了解，光学API不懂原理，就等着调代码调到自闭吧。（🤦‍♂️

我实现过线程池，你可以看看，建议自己写个定长线程池吧（动态不要求：

https://github.com/ganler/thread_pools

---



## Assignment（作业）

其实没有作业，但给你们提点建议，已保证你们可以学以致用：

- debug尝试用GDB，用多了就会的；
- 编译的flag自己备好cheatsheat，平时建项目的时候用；
- 并发，自己多去写写代码（按这个顺序去做，为什么是这些内容呢，因为这些东西我写过，可以face2face指导你：
  - 一把大锁并发容器；
  - 学会如何做并发测试；
  - 并发快排；
  - 并发merge-sort；
  - 线程池；
  - 自旋锁；
  - 过手锁list（先写这么多吧）；

