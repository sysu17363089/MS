#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
std::string flag("A");

void PrintA()
{
    while(true) {
        std::unique_lock<std::mutex> lck(mtx);
        while (flag == "B") {
            cv.wait(lck);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "A" << std::endl;
        flag = "B";
        cv.notify_all();
    }
}

void PrintB()
{
    while(true) {
        std::unique_lock<std::mutex> lck(mtx);
        while (flag == "A") {
            cv.wait(lck); // cv.wait(lck, lambda)
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "B" << std::endl;
        flag = "A";
        cv.notify_all();
    }
}

int main()
{
    std::thread t1(PrintA);
    std::thread t2(PrintB);
    t1.join();
    t2.join();
    std::cin.get();
}