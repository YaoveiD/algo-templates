#include <cassert>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
 
std::mutex m;
std::condition_variable cv;
int n;
 
void worker_thread()
{
    // Wait until main() sends data
    std::lock_guard lk(m);
    n = 1;
    // cv.notify_one();
}
 
int main()
{
    std::thread worker(worker_thread);
 
    std::unique_lock lk(m);
    cv.wait(lk, []{ return n == 1; });
    assert(n == 1);
    worker.join();
}
