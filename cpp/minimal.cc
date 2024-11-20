#include <cassert>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
 
using namespace std::chrono_literals;
std::mutex m;
std::condition_variable cv;
int n;
 
int main()
{
    printf("in main0\n");
    std::unique_lock lk(m);
    // lk.lock();
    printf("in main1\n");
    lk.unlock();
    printf("in main2\n");
}
