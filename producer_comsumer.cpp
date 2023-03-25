#include<semaphore.h>
#include<thread>
#include<iostream>
#include<queue>
#include<mutex>

using namespace std;
sem_t full, empty;
mutex mt;
queue<int> q;
int SIZE = 5;

void producer() {
    while (1) {
        sem_wait(&full);
        unique_lock<mutex> ulk(mt);
        q.push(1);
        cout << "Produce, Now has " << q.size() << endl;
        this_thread::sleep_for(chrono::seconds(1));
        sem_post(&empty);
    }
}

void comsumer() {
    while (1) {
        sem_wait(&empty);
        unique_lock<mutex> uck(mt);
        q.pop();
        cout << "Comsume, Now has " << q.size() << endl;
        this_thread::sleep_for(chrono::seconds(1));
        sem_post(&full);
    }
}

int main() {
    sem_init(&full, 0, 5);
    sem_init(&empty, 0, 0);
    thread t1(producer);
    thread t2(comsumer);

    t1.join();
    t2.join();
}