# Train-2

## Task

请阅读[这里](https://github.com/ganler/superpower19classifier)的代码，并使用标准线程库，书写代码将其多线程执行。

这里多线程执行是指当有很多个图片，比如说4N张图片，我使用4个线程去执行，那么如果线程切换时间不计的话，我的速度就快了4倍了。

你需要提交一个`main.cpp`文件，请仿照`test.cpp`的格式，但把单线程执行写成多线程执行。

完成后请Pull request，我将对其进行评价。

## 实现思路参考

- 直接使用`std::thread`，跑完后`join()`即可；
- 直接使用异步API `std::async`，最后拿`std::future`就好；
- 实现线程池，手动异步（可参考我写的[线程池库](https://github.com/ganler/thread_pools)）

