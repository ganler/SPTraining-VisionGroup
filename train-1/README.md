# Task1

## MarkDown

下载MarkDown编辑器Typora。使用MarkDown书写本次作业，转pdf后提PR(pull request)到[这里](https://github.com/ganler/SPTraining-VisionGroup)；

## Search Engine

国外有丰富的高质量资料，所以第一步是学会科学上网。

看[这里](http://ibloodline.com/articles/2018/02/01/fuck-wall.html)；

平时多学会自己搜东西。

## Git

学会使用Git：

- 什么是Git，能干嘛
- 如何用Git进行版本管理
- 如何用Git进行多人合作

相关教程：

[廖雪峰](https://www.liaoxuefeng.com/wiki/896043488029600/896067074338496)

> 看40%即可。

## Ubuntu

#### 安装

[教程](https://www.jianshu.com/p/38e6be8efecf)

> 类似的教程很多，anyway装好就行。19版win10有wsl，可以试试(我没试过)。

#### 使用

[资料](https://wiki.ubuntu.org.cn/命令行指南)

## 使用cmake+gcc编译程序

[教学](https://www.hahack.com/codes/cmake/)

#### 举例

编译一个hello world。

```bash
# 命令行下
mkdir foo && cd foo # 建立一下foo文件夹并且进入
touch foo.cpp       # 建立foo.cpp文件
# 然后你可以开始编辑foo.cpp 用nano/vim/gedit都可以
touch CMakeLists.txt# 建立文件(名字不能有差错)
```

> 写上：

```c++
// foo.cpp
#include <iostream>
int main() { std::cout << "hello world\n"; }
```

```cmake
# CMakeLists.txt
cmake_minimum_required (VERSION 3.0) # CMake 最低版本号要求
project (foo)    										 # 项目名称(默认为可执行文件的名称)
add_executable(foo main.cc)          # 生成可执行文件所使用的文本文件
```

```bash
# 回到命令行
mkdir build && cd build
cmake ..                             # 使用cmake生成makefile
make -j4                             # 产生可执行文件
./foo                                # 运行可执行文件
```

## 作业

在

- 搭好Ubuntu
- 建立GitHub账号
- 科学上网成功
- Typora下载完

之后

#### fork源项目

[参考教材](https://www.zhihu.com/question/20393785)

[源项目地址](https://github.com/ganler/SPTraining-VisionGroup)

fork完后，你可以直接git clone你fork后的项目到本地（通过使用`git clone 你的地址`）。

然后这样你就把`SPTraining-VisionGroup`文件夹弄下来了，然后你进入后会发现有个train1的文件夹，然后你需要在train1中建立项目。

#### 写代码！写代码！

进入train1后：

```bash
mkdir xxx-hm   # 建立homework，xxx是你名字的缩写
```

然后依照上面的内容在xxx-hm编译一个程序。

这个程序的内容也就手写一个**快排**吧

程序的架构应该是这样的：

在hm里面，你先建立`qsort.hpp`，在`qsort.hpp`中：

```c++
#pragma once

template <typename Iter>
void qsort(Iter beg, Iter end)
{
    // Implementation.
}
```

写好之后，在main.cpp里面调用一下。

#### 写个README

在xxx-hm建立一个README.md，将你在命令行里面打过的东西都贴在里面(要求有高亮)，然后就是把你的疑惑写上。

```markdown
# Submission

## Code

​```shell
...
​```

## Questions

...
```

#### Pull Request

对[源项目地址](https://github.com/ganler/SPTraining-VisionGroup)提PR。具体怎么做自己Google吧，你总得有自己搜索信息的能力。
