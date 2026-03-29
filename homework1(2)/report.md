# 41343134
## 作業三 Polynomial + Available Lists
## 解題說明


### 解題策略

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


2.ChainNode 節點

​



​

- 核心功能：

    - getNode()：取得可用節點

    - getBack(node)：一次回收大量節點

    - getOneNodeOrNew(elem)：取得節點或創建新節點




- 功能：



### 結論

### 心得
