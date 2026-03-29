# 41343134
## 作業三 Max/Min Heap
## 解題說明
    使用最小堆（Min-Heap）來實作最小優先佇列（Min Priority Queue, MinPQ）
    
   - 虛擬析構函數
   - IsEmpty()：檢查佇列是否為空
   - Top()：回傳引用的最大元素
   - Push(const T&)：加入一個元素
   - Pop()：移除最大優先級的元素

### 解題策略
1. n 個整數後全部插入堆中，再重複取出 Top() 並 Pop

2. 定義 MinPQ<T> 虛擬函式
   - Push(x)：插入元素

   - Top()：取得目前最小元素（不刪除）
   
   - Pop()：刪除目前最小元素


4. 陣列表示完全二元樹
   使用陣列 heap 來存 heap：
   根節點：heap[1]
   
   parent = i/2

   left child = 2*i
   
   right clild = 2*i+1
   
## 程式實作
### IDE:
Microsoft Visual Studio Code C/C++


```cpp
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
```
## 效能分析
### 時間複雜度：
    Top()：O(1)
    Push(x)：O(log n)
    Pop()：O(log n)
    總時間複雜度：O(n log n)
### 空間複雜度：
    heap 空間複雜度：O(n)
    
## 測試案例


| 測試案例 | 輸入參數   | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   |6<br> 6 4 1 3 2 5   | 1 2 4 6 3 5   |  1 2 4 6 3 5       |
| 測試二   |7<br> 5 1 2 8 3 5 6   | 1 3 2 8 5 5 6     |  1 3 2 8 5 5 6       |




### 測試輸入
```
6
6 4 1 3 2 5
7
5 1 2 8 3 5 6 
```
### 測試輸出
```
1 2 4 6 3 5

1 3 2 8 5 5 6
```


## 申論及開發報告




​



​



### 結論

### 心得
