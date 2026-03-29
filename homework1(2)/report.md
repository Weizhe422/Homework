# 41343134
## 作業三 Max/Min Heap
## 解題說明
    使用最小堆（Min-Heap）來實作最小優先佇列（Min Priority Queue, MinPQ）

### 解題策略
1. n 個整數後全部插入堆中，再重複取出 Top() 並 Pop() 
   定義 MinPQ<T> 虛擬函式
   Push(x)：插入元素
   Top()：取得目前最小元素（不刪除）
   Pop()：刪除目前最小元素

2. 陣列表示完全二元樹
   使用陣列 heap 來存 heap：
   根節點：heap[1]
   parent = i/2
   left child = 2*i
   right clild = 2*i+1
   
## 程式實作
### IDE:
Microsoft Visual Studio Code C/C++


```
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T& x) = 0;
    virtual void Pop() = 0;
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    T* heap;        // 1-based
    int capacity;
    int size;

    void Resize(int newCapacity) {
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
    MinHeap(int initCapacity = 10) : capacity(initCapacity), size(0) {
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
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    MinHeap<int> pq(n); // 初始容量設 n，通常就不會 resize
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        pq.Push(x);
    }

    // 輸出排序結果
    for (int i = 0; i < n; i++) {
        cout << pq.Top();
        pq.Pop();
        if (i != n - 1) cout << " ";
    }
    cout << "\n";
    return 0;
}


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
    
## 測試與驗證
## 測試案例


### 測試一：基本多項式運算


**運算結果：**



### 測試輸入
```

```
### 測試輸出
```

```


## 申論及開發報告
### 申論
#### 資料結構設計



​



​

- 核心功能：




- 功能：



### 結論

### 心得
