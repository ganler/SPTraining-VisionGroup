# Submission

## Code

```shell
git clone git@github.com:CiceroCaesar/SPTraining-VisionGroup.git
cd SPTraining-VisionGroup/train-1
mkdir ljy-hm
cd ljy-hm
touch qsort.hpp
gedit qsort.hpp
touch main.cpp
gedit main.cpp
touch CMakeLists.txt
gedit CMakeLists.txt
mkdir build && cd build
sudo apt-get install g++
Y
cmake ..
make -j4
./qsort
touch README.md
gedit README.md
```

## Questions

1. 首先还是很抱歉我英文不太好，勉强看懂一般的英文文章，至于自己写，平常全靠翻译软件加自己二次修改，所以这部分只能拿中文来写了（会努力提高的）。
2. 不知道为什么，我在*ubuntu*下的*Typora*的斜体与粗体格式不好用，而*windows*下的就正常。
3. 这一条应该也不算疑惑吧，我的算法感觉也需加强，连快排我仍需参考谷歌，说来惭愧，我快排的代码几乎就是把[维基百科]([https://zh.wikipedia.org/wiki/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F](https://zh.wikipedia.org/wiki/快速排序))认真读几遍理解之后，还上[知乎](https://zhuanlan.zhihu.com/p/52884590)上学习了一下才明白它（但最后至少明白了，结果就是好的），改了一丢丢无关紧要的东西，就“抄”上去了（虽然我不想承认，但我觉得还是得说一下吧），当然main.cpp还是要自己写了。
4. 没看明白*Typora*的代码段，我觉得只需输入``````shell```，接下来输入在命令行里大过的东西即可吧，那最后的==**```**==我就不知道它的意义了。
5. 在上一条中的==**```**==我本来想表示成实时显示的代码，即如此表示```demo```，但到最后我也没解决这个问题，因为同时写九个==**`**==并不能得到我想要的输出，所以我只能加粗高亮了。
6. 在**CODE**部分代码的要求是高亮，我上网上查说是只要代码块中输入对应的语言，就会自动高亮，然会结果就是如上，但我感觉跟```== ==```造成的高亮效果感觉不同，但叫我自己手动加高亮，我也不知道在哪加，就只能先如此了。
7. *CMakeLists.tx*t中的```add_executable(qsort main.cc)```但我担心错，将其中```main.cc```改成```main.cpp```了，虽然后来上网查了一下说[“今天，在Unix世界之外，它主要是`.cpp`。Unix似乎`.cc`更经常使用。”](https://cloud.tencent.com/developer/ask/59122)，但我还是不清楚到底该怎么办。
8. 才发现在本地*Typora*内看到的效果比*github*好很多，我不明白为什么会出现这种情况，难道是我自己哪写的有问题还是格式不适配的原因。



