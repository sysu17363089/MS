#include <atomic>
#include <thread>
#include <iostream>
using namespace std;


class XLOCK {
    private:
        atomic_flag my_lock;
    public:
        void lock() {
            // test_and_set() 函数检查 std::atomic_flag 标志，如果 std::atomic_flag 之前没有被设置过，
            // 则设置 std::atomic_flag 的标志，并返回先前该 std::atomic_flag 对象是否被设置过，
            // 如果之前 std::atomic_flag 对象已被设置，则返回 true，否则返回 false。
            // 如果flag已经被其它线程设置，那么就相当于自旋锁已经被其它线程占有，那么就会一直while循环检查flag，直到其它线程释放flag
            while( my_lock.test_and_set()) {}
        }
        void unlock() {
            my_lock.clear();
        }
};

XLOCK mylock;

void func1(int *x) {
    while(*x < 100) {
        mylock.lock();
        cout << "fun1:" << *x <<  endl;
        ++(*x);
        mylock.unlock();
    }
}

void func2(int *x) {
    while(*x < 100) {
        mylock.lock();
        cout << "fun2 " << *x << endl;
        ++(*x);
        mylock.unlock();
    }
}

int main() {
    int x = 1;
    thread t1(func1, &x);
    thread t2(func2, &x);

    t1.join();
    t2.join();

}