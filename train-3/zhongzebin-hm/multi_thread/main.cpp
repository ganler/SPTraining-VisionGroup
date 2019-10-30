#include <iostream>
#include <thread>
#include <unistd.h>
const auto t1 = std::chrono::system_clock::now();
void function_1() {
    //延时500ms 为了保证test()运行结束之后才打印
    usleep(0.5*1000000);
    std::cout << "I'm function_1()" << std::endl;
    const auto t2 = std::chrono::system_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "time consumed "<<duration * 1e-3<<std::endl;
}
void function_2() {
    //延时500ms 为了保证test()运行结束之后才打印
    usleep(1000000);
    std::cout << "I'm function_2()" << std::endl;
    const auto t2 = std::chrono::system_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "time consumed "<<duration * 1e-3<<std::endl;
}

void test() {
    std::thread t1(function_1);
    std::thread t2(function_2);
    t1.detach();
    t2.detach();
    // t1.join();
    std::cout << "test() finished" << std::endl;
}

int main() {

    test();
    //让主线程晚于子线程结束
    usleep(1.5*1000000);
    const auto t2 = std::chrono::system_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "time consumed "<<duration * 1e-3<<std::endl;
    return 0;
}