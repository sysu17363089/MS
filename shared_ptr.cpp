
template <class T>
class SharePtr {
    public:
        T* ptr;
        int* count;
        SharePtr(T* obj) {
            ptr = obj;
            count = new int(1);
        }
        SharePtr (SharePtr& other) {
            (*count)++;
            count = other.count;
            ptr = other.ptr;
        }

        SharePtr operator = (SharePtr other) {
            (*count)--;
            if ((*count) == 0) {
                delete ptr;
                delete count;
            }
            count = other.count;
            (*count)++;
            ptr = other.ptr;

        }

        ~SharePtr() {
             (*count)--;
            if (*count == 0){
                delete ptr;
                delete count;
            }
            
        }


};

int main() {
    
}