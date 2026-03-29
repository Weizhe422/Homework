#include <iostream>
#include <stdexcept>
#include <utility>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() = default;
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T& x) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    T* heap;        
    int capacity;
    int size;

    void Resize(int newCapacity) {
        if (newCapacity < 1) newCapacity = 1;
        T* newHeap = new T[newCapacity + 1];
        for (int i = 1; i <= size; i++) newHeap[i] = heap[i];
        delete[] heap;
        heap = newHeap;
        capacity = newCapacity;
    }

    void SiftUp(int i) {
        while (i > 1) {
            int p = i / 2;
            if (!(heap[i] < heap[p])) break;
            swap(heap[i], heap[p]);
            i = p;
        }
    }

    void SiftDown(int i) {
        while (true) {
            int left = 2 * i;
            int right = left + 1;
            int smallest = i;

            if (left <= size && heap[left] < heap[smallest]) smallest = left;
            if (right <= size && heap[right] < heap[smallest]) smallest = right;

            if (smallest == i) break;
            swap(heap[i], heap[smallest]);
            i = smallest;
        }
    }

public:
    explicit MinHeap(int initCapacity = 10)
        : heap(nullptr), capacity(initCapacity), size(0) {
        if (capacity < 1) capacity = 1;
        heap = new T[capacity + 1]; 
    }

    ~MinHeap() override {
        delete[] heap;
    }

    bool IsEmpty() const override { return size == 0; }

    const T& Top() const override {
        if (IsEmpty()) throw runtime_error("Top() on empty heap");
        return heap[1];
    }

    void Push(const T& x) override {
        if (size == capacity) Resize(capacity * 2);
        heap[++size] = x;
        SiftUp(size);
    }

    void Pop() override {
        if (IsEmpty()) throw runtime_error("Pop() on empty heap");
        heap[1] = heap[size--];
        if (!IsEmpty()) SiftDown(1);
    }

  
    void PrintArrayOrder() const {
        for (int i = 1; i <= size; i++) {
            if (i != 1) cout << ' ';
            cout << heap[i];
        }
        cout << '\n';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    MinHeap<int> pq(n > 0 ? n : 1);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pq.Push(x);
    }

   
    pq.PrintArrayOrder();
    return 0;
}
