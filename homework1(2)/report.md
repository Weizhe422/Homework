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
1.Heap 適合用來實作 Priority Queue，能在插入與刪除最小值時保持高效率，且能隨時維持「最小值在根」的特性。

2.使用 1-based 陣列存放完全二元樹，可以用簡單的索引運算得到父子節點位置，不需要額外指標，記憶體使用較節省且存取效率高。

3.核心功能:

* SiftUp：插入新元素後，只需要沿著父節點路徑往上修正，即可恢復 Min-Heap 性質。
  
* SiftDown：刪除根後將最後元素放到根，沿著較小子節點往下修正，即可恢復 Min-Heap 性質。
 
* Resize：在容量不足時擴充陣列，確保結構可處理更大輸入。

  ## 優點
  
  1. 時間效率穩定
  
  2. 陣列實作（1-based）結構簡單、效能佳

  3. 抽象介面清楚（MinPQ）

  ## 缺點
  
  1. 容量策略固定倍增，可能造成多餘記憶體

  2. 建堆方式為逐一 Push，建堆成本較高

## 作業一 Binary Search Tree

## 解題說明


  

### 解題策略
(a)


(b)

## 程式實作
(a)
### IDE:
Microsoft Visual Studio Code C/C++


```cpp

```

```cpp

```
## 效能分析
(a)
空間複雜度：
| 類型              | 複雜度             |
| --------------- | --------------- |
|

時間複雜度： 
 |操作      | 平均時間     | 最壞時間 |

(b)
時間複雜度： 
|操作      | 平均時間     | 最壞時間 |
| ------- | -------- |  -------- | 


## 測試與驗證

### 測試案例

| 測資 | 輸入參數n | 預期輸出  | 實際輸出  |
|----------|--------------|----------|----------|
| 測試一   |100|   14 ,2.10721  |   2.10721 |
| 測試二   | 500 |  21 ,2.34224 |   2.34224   |
| 測試三   |1000 | 22  ,2.20755 |   2.20755|
| 測試四   |2000 |  24 ,2.18863|    2.18863 |
| 測試五   |3000 |  25 ,2.16436|    2.16436 |
| 測試六   |4000 | 29  ,2.42358 |   2.42358 |
| 測試七   |5000 | 28  ,2.27870 |     2.27870 |
| 測試八  | 6000 | 31  ,2.46997 |   2.46997 |
| 測試九  | 7000 | 34  ,2.66184  |  2.66184 |
| 測試十   | 8000 | 32  ,2.46803  | 2.46803  |
| 測試十一  |9000 | 31 ,2.35998 |  2.35998 |
| 測試十二   | 10000 | 29 ,2.18247 | 2.18247  |

### 測試輸出

```
n        H     H/log2n
100      14    2.10721
500      21    2.34224
1000     22    2.20755
2000     24    2.18863
3000     25    2.16436
4000     29    2.42358
5000     28    2.2787
6000     31    2.46997
7000     34    2.66184
8000     32    2.46803
9000     31    2.35998
10000    29    2.18247
```
![BST ratio plot](src/1.png)
### 結論
本實驗透過對不同規模𝑛的資料進行隨機插入，對每個不同的 (n) 建立一棵 Binary Search Tree（BST）
，並計算其高度，進一步與 
  $\log_2$(n) 進行比較分析。

## 申論及開發報告
本實驗不僅實作 BST，更重要的是透過實驗方式驗證理論分析結果。
理論上，BST 的操作效率取決於樹高，在最壞情況下可能退化為 𝑂(𝑛)，但在隨機輸入下，其期望高度為 𝑂(log⁡𝑛)從實驗結果可觀察到：
- 高度隨 𝑛增加呈現緩慢上升
- 與 log⁡𝑛成長趨勢一致
- 比值趨於穩定常數
### 優點
- 能驗證理論（log n 成長）
- 使用隨機化，貼近實務情境
- 實作簡單、易於擴充
### 缺點
- 高度計算成本高
- 亂數品質有限
- 記憶體與遞迴風險

