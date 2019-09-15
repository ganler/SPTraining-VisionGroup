# Submission

## 目录

[TOC]

## Code

```shelll
cd SPTraining-VisionGroup/train-2
mkdir ljy-hm
cd ljy-hm
touch dynamic_template_array2D .hpp
gedit dynamic_template_array2D .hpp
touch classifier.hpp
gedit classifier.hpp
touch main.cpp
gedit main.cpp
touch CMakeLists.txt
gedit CMakeLists.txt
mkdir build && cd build
cmake ..
make -j4
./SP19CLASSIFIER_TEST
touch README.md
gedit README.md
```

## Questions

1.感觉个人对c++11还需学习，还需时间。虽说之前在大作业中写过动态三维数组，且有学长一维数组的模板，但	仍然感觉不是很好。

2.第二个要求重写分类器我并不能理解==“重做”==的意思，所以我只能把学长的代码复制粘贴了一遍，同时又结合了	ppt学习了一下。

3.写多线程时虽然能理解但自己写又是两回事。同时我在`make  -j4`时出现了两三个ERROR，终端显示的好像都是	==thread==的问题，但我实在是不会调试了，就先这样吧。

4.主要还是它用了将近两天时间，我已经没时间了，我都没有复习预习，人要有舍有得，也只能这样了，有时间	下周接着钻研吧。

5.吐槽一下ubuntu自带的输入法中文奇烂，可惜网上说搜狗在ubuntu下有占cpu100%的bug。