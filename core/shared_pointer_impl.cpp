using namespace std;
template <typename T>
class ReferenceCount {
private:
    int count;
    T* ptr;
    mutex mtx;
public:
    ReferenceCount(T* pointer) : ptr(pointer), count(0) {}
    ~ReferenceCount() {
        delete ptr;
    }
    int increase() {
        lock_guard<mutex> lock(mtx);
        count++;
        return count;
    }
    int decrease() {
        lock_guard<mutex> lock(mtx);
        count--;
        return count;
    }
    int getCount() {
        lock_guard<mutex> lock(mtx);
        return count;
    }
};
template <typename T>
class SmartPointer {
private:
    ReferenceCount<T> ref;
public:
    SmartPointer() {
        ref = nullptr;
    }
    SmartPointer(T* pointer) {
        ref = new ReferenceCount<T>(pointer);
        ref->increase();
    }
    SmartPointer(const SmartPointer<T>& other) {
        if (other.ref == nullptr) {
            ref = nullptr;
            return;
        }
        ref = other.ref;
        ref->increase();
    }
    SmartPointer<T>& operator=(const SmartPointer<T>& other) {
        if (ref == other.ref) return this;
        if (ref && ref->decrease() == 0) {
            delete ref;
        }
        ref = other.ref;
        ref->increase();
        return this.
    }
    T& operator*() {
        return *(ref->ptr);
    }
    T* operator*() {
        return ref->ptr;
    }
    ~SmartPointer() {
        if (ref == nullptr) return;
        int count = ref->decrease();
        if (count == 0) {
            delete ref;
        }
        ref = nullptr;
    }
}