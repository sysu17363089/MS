#include <iostream>
#include <mutex>
#include <memory>
using namespace std;

class SingleObj_lazy1 {
    public:
        SingleObj_lazy1(SingleObj_lazy1& other) = delete;
        SingleObj_lazy1 operator = (SingleObj_lazy1& other) = delete;

        static SingleObj_lazy1& get_obj () {
            static SingleObj_lazy1 myobj;
            return myobj;
        }   
    private:
        SingleObj_lazy1() {}
};

mutex mtx;
class SingleObj_lazy2 {
    public:
        SingleObj_lazy2(SingleObj_lazy2& other) = delete;
        SingleObj_lazy2 operator = (SingleObj_lazy2& other) = delete;
        shared_ptr<SingleObj_lazy2> get_obj () {
            if (obj_ptr == NULL) {
                unique_lock<mutex> uck(mtx);
                obj_ptr = shared_ptr<SingleObj_lazy2>(new SingleObj_lazy2);
            } 
            return obj_ptr;
        }
    private:
        static shared_ptr<SingleObj_lazy2> obj_ptr;
        SingleObj_lazy2() {};
};

