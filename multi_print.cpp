#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>

using namespace std;

mutex alock;
condition_variable cv;
char curr_term = 'A';

void print_a() {
    while (true) {
        unique_lock<mutex> ulk(alock);
        if (curr_term == 'B') {
            cv.wait(ulk); // 对ulk进行解锁，并阻塞在这一行
        }
        if (curr_term == 'A') {
            this_thread::sleep_for(chrono::seconds(1));
            cout << 'A' << endl;
            curr_term = 'B';
            cv.notify_one();
        } 
    }
}

void print_b() {
    while (true) {
        unique_lock<mutex> ulk(alock);
        if (curr_term == 'A') {
            cv.wait(ulk); // 对ulk进行解锁，并阻塞在这一行
        }
        if (curr_term == 'B') {
            this_thread::sleep_for(chrono::seconds(1));
            cout << 'B' << endl;
            curr_term = 'A';
            cv.notify_one();
        } 
    }
}

int main() {
    thread t1(print_a);
    thread t2(print_b);

    t1.join();
    t2.join();

    return 0;

}