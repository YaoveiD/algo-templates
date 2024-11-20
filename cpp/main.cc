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
 
void worker_thread()
{
    printf("in worker0\n");
    std::lock_guard lk(m);
    printf("in worker1\n");
    n = 1;
    printf("in worker2\n");
    cv.notify_one();
    printf("in worker3\n");
    std::this_thread::sleep_for(2000ms);
}
 
int main()
{
    std::thread worker(worker_thread);
 
    printf("in main0\n");
    std::unique_lock lk(m);
    printf("in main1\n");
    // cv.wait(lk, []{ return n == 1; });
    while (n != 1) {
        printf("waiting in while\n");
        cv.wait(lk);
        printf("in while\n");
    }
    lk.unlock();
    printf("in main2\n");
    assert(n == 1);
    worker.join();
}
