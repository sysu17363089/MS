#include<iostream>
#include<thread>
#include<semaphore.h>
using namespace std;

sem_t s1, s2;
void print_a() {
    while (1) {
        sem_wait(&s1);
        cout << 'A' << endl;
        this_thread::sleep_for(chrono::seconds(1));
        sem_post(&s2);
    }
    
}

void print_b() {
    while (1) {
        sem_wait(&s2);
        cout << 'B' << endl;
        this_thread::sleep_for(chrono::seconds(1));
        sem_post(&s1);
    }
    
}

int main() {
    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 0);
    thread t1(print_a);
    thread t2(print_b);

    t1.join();
    t2.join();

}