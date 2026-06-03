# 41343134
# 41343143
## 作業三 Sorting Project

## 解題說明
本專案的核心在於實作五種不同的排序方法，去改變資料的「性質」和「大小」，來觀察演算法。實作的五種排序演算法有 :

1. Insertion Sort : 是一種簡單直觀的排序演算法。它的運作方式如同整理手中的撲克牌
2. Quick Sort（Median-of-Three）: 是一種高效率的排序演算法，採用分治法（Divide and Conquer）策略  
3. Iterative Merge Sort  : 
4. Heap Sort  
5. Composite Sort  

--- 

## 解題策略

### 1. Insertion Sort（插入排序）排序方式 : 

它將資料分為「已排序」與「未排序」兩部分，每次從未排序中取出一個元素，

在已排序區中由後向前比對，找到適當位置插入，直到所有元素排序完成。

### 2. Quick Sort (快速排序)  排序方式:

透過挑選一個基準值（Pivot），將陣列分為左右兩部分，使左側元素皆小於基準值

，右側元素皆大於基準值，再遞迴處理兩側子陣列來完成排序。

### 3.



---

## 程式實作
### IDE:
Microsoft Visual Studio Code C/C++


```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
template <class T>
void Permute(T* a, int n) {
    for (int i = n - 1; i >= 1; i--) {
        int j = rand() % (i + 1);
        swap(a[i], a[j]);
    }
}
void InsertionSort(int* a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}
int MedianOfThree(int* a, int low, int high) {
    int mid = low + (high - low) / 2;
    if (a[low] > a[mid]) swap(a[low], a[mid]);
    if (a[low] > a[high]) swap(a[low], a[high]);
    if (a[mid] > a[high]) swap(a[mid], a[high]);
    swap(a[mid], a[high - 1]);
    return a[high - 1];
}
void QuickSortHelper(int* a, int low, int high) {
    if (low + 10 <= high) {
        int pivot = MedianOfThree(a, low, high);
        int i = low;
        int j = high - 1;
        while (true) {
            while (a[++i] < pivot);
            while (a[--j] > pivot);
            if (i < j) swap(a[i], a[j]);
            else break;
        }
        swap(a[i], a[high - 1]);
        QuickSortHelper(a, low, i - 1);
        QuickSortHelper(a, i + 1, high);
    }
    else {
        InsertionSort(a + low, high - low + 1);
    }
}

void QuickSort(int* a, int n) {
    QuickSortHelper(a, 0, n - 1);
}
void Merge(int* a, int* temp, int l, int m, int r) {
    int i = l, j = m + 1, k = l;
    while (i <= m && j <= r) {
        if (a[i] <= a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }
    while (i <= m) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];
    for (i = l; i <= r; i++) a[i] = temp[i];
}

void MergeSort(int* a, int n) {
    int* temp = new int[n];
    for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = min(left_start + curr_size - 1, n - 1);
            int right_end = min(left_start + 2 * curr_size - 1, n - 1);
            Merge(a, temp, left_start, mid, right_end);
        }
    }
    delete[] temp;
}
void MaxHeapify(int* a, int i, int n) {
    int child;
    int temp = a[i];
    for (; 2 * i + 1 < n; i = child) {
        child = 2 * i + 1;
        if (child != n - 1 && a[child + 1] > a[child]) {
            child++;
        }
        if (temp < a[child]) {
            a[i] = a[child];
        }
        else {
            break;
        }
    }
    a[i] = temp;
}
void HeapSort(int* a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapify(a, i, n);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        MaxHeapify(a, 0, i);
    }
}
void CompositeSort(int* a, int n) {
    if (n <= 32) {
        InsertionSort(a, n);
    }
    else {
        MergeSort(a, n);
    }
}
void GenerateInsertionWorst(int* a, int n) {
    for (int i = 0; i < n; i++) a[i] = n - i;
}
void MergeWorstHelper(int* a, int* temp, int l, int r) {
    if (l >= r) return;
    if (l + 1 == r) {
        swap(a[l], a[r]);
        return;
    }
    int m = l + (r - l) / 2;
    int i, k = 0;
    for (i = l; i <= r; i++) temp[k++] = a[i];
    for (i = l, k = 0; i <= m; i++, k += 2) a[i] = temp[k];
    for (i = m + 1, k = 1; i <= r; i++, k += 2) a[i] = temp[k];

    MergeWorstHelper(a, temp, l, m);
    MergeWorstHelper(a, temp, m + 1, r);
}

void GenerateMergeWorst(int* a, int n) {
    for (int i = 0; i < n; i++) a[i] = i + 1;
    int* temp = new int[n];
    MergeWorstHelper(a, temp, 0, n - 1);
    delete[] temp;
}
bool VerifySort(void (*sort_func)(int*, int), string name) {
    const int test_size = 50;
    int* origin = new int[test_size];
    int* test_arr = new int[test_size];

    for (int i = 0; i < test_size; i++) origin[i] = rand() % 1000;
    copy(origin, origin + test_size, test_arr);

    sort_func(test_arr, test_size);
    sort(origin, origin + test_size);

    bool correct = true;
    for (int i = 0; i < test_size; i++) {
        if (test_arr[i] != origin[i]) {
            correct = false;
            break;
        }
    }

    delete[] origin;
    delete[] test_arr;

    cout << "  - " << left << setw(15) << name << ": " << (correct ? "[PASS]" : "[FAIL]") << "\n";
    return correct;
}
void RunCorrectnessTest() {
    cout << "\n==================================================\n";
    cout << " 1. Correctness Test!!\n";
    cout << "==================================================\n";
    bool all_pass = true;
    all_pass &= VerifySort(InsertionSort, "Insertion Sort");
    all_pass &= VerifySort(MergeSort, "Merge Sort");
    all_pass &= VerifySort(HeapSort, "Heap Sort");
    all_pass &= VerifySort(QuickSort, "Quick Sort");
    all_pass &= VerifySort(CompositeSort, "Composite Sort");
    if (!all_pass) {
        cout << "\n[warn!!!]n";
        exit(1);
    }
    cout << "[pass!!!]\n";
}
typedef void (*SortFunc)(int*, int);
double TimeWorstCase(SortFunc sort_func, int* worst_data, int n, int repetitions) {
    int* test_array = new int[n];
    auto start = chrono::high_resolution_clock::now();
    for (int r = 0; r < repetitions; r++) {
        copy(worst_data, worst_data + n, test_array);
        sort_func(test_array, n);
    }
    auto end = chrono::high_resolution_clock::now();
    delete[] test_array;
    chrono::duration<double, micro> duration = end - start;
    return duration.count() / repetitions;
}
double TimeAverageCase(SortFunc sort_func, int n, int repetitions) {
    int* test_array = new int[n];
    auto start = chrono::high_resolution_clock::now();
    for (int r = 0; r < repetitions; r++) {
        for (int i = 0; i < n; i++) test_array[i] = i + 1;
        Permute(test_array, n);
        sort_func(test_array, n);
    }
    auto end = chrono::high_resolution_clock::now();
    delete[] test_array;
    chrono::duration<double, micro> duration = end - start;
    return duration.count() / repetitions;
}
int main() {
    srand(time(nullptr));
    RunCorrectnessTest();
    vector<int> test_sizes = { 500, 1000, 2000, 3000, 4000, 5000 };
    auto get_reps = [](int n) {
        if (n <= 1000) return 500;
        if (n <= 3000) return 100;
        return 20;
        };
    struct DataRow {
        int n;
        double ins, mrg, hp, qk, cmp;
    };
    vector<DataRow> worst_results;
    vector<DataRow> avg_results;
    for (int n : test_sizes) {
        int reps = get_reps(n);
        int* data = new int[n];
        DataRow w_row{ n }, a_row{ n };
        GenerateInsertionWorst(data, n);
        w_row.ins = TimeWorstCase(InsertionSort, data, n, reps);
        GenerateMergeWorst(data, n);
        w_row.mrg = TimeWorstCase(MergeSort, data, n, reps);
        w_row.cmp = TimeWorstCase(CompositeSort, data, n, reps);
        double max_hp = 0, max_qk = 0;
        for (int p = 0; p < 15; p++) {
            for (int i = 0; i < n; i++) data[i] = i + 1;
            Permute(data, n);
            max_hp = max(max_hp, TimeWorstCase(HeapSort, data, n, reps));
            max_qk = max(max_qk, TimeWorstCase(QuickSort, data, n, reps));
        }
        w_row.hp = max_hp;
        w_row.qk = max_qk;
        worst_results.push_back(w_row);
        a_row.ins = TimeAverageCase(InsertionSort, n, reps);
        a_row.mrg = TimeAverageCase(MergeSort, n, reps);
        a_row.hp = TimeAverageCase(HeapSort, n, reps);
        a_row.qk = TimeAverageCase(QuickSort, n, reps);
        a_row.cmp = TimeAverageCase(CompositeSort, n, reps);
        avg_results.push_back(a_row);
        delete[] data;
    }
    cout << fixed << setprecision(2);
    cout << "\n=========================================================================================\n";
    cout << " 2. Worst-Case Test Report (us)\n";
    cout << "=========================================================================================\n";
    cout << left << setw(8) << "n"
        << setw(16) << "Insertion"
        << setw(16) << "Merge"
        << setw(16) << "Heap(Max)"
        << setw(16) << "Quick(Max)"
        << setw(16) << "Composite" << "\n";
    cout << "-----------------------------------------------------------------------------------------\n";
    for (const auto& r : worst_results) {
        cout << left << setw(8) << r.n
            << setw(16) << r.ins
            << setw(16) << r.mrg
            << setw(16) << r.hp
            << setw(16) << r.qk
            << setw(16) << r.cmp << "\n";
    }

    cout << "\n=========================================================================================\n";
    cout << " 3. Average-Case Test Report　(us)\n";
    cout << "=========================================================================================\n";
    cout << left << setw(8) << "n"
        << setw(16) << "Insertion"
        << setw(16) << "Merge"
        << setw(16) << "Heap"
        << setw(16) << "Quick"
        << setw(16) << "Composite" << "\n";
    cout << "-----------------------------------------------------------------------------------------\n";
    for (const auto& r : avg_results) {
        cout << left << setw(8) << r.n
            << setw(16) << r.ins
            << setw(16) << r.mrg
            << setw(16) << r.hp
            << setw(16) << r.qk
            << setw(16) << r.cmp << "\n";
    }
    cout << "=========================================================================================\n";

    return 0;
}
```
## 效能分析 

### 時間複雜度： 
| 排序法 | 最佳 | 平均 | 最壞 |
|---|---|---|---|
| Insertion Sort | O(n) | O(n<sup>2</sup>) | O(n<sup>2</sup>) |
| Quick Sort | O(n log n) | O(n log n) | O(n<sup>2</sup>) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) |
| Heap Sort | O(n log n) | O(n log n) | O(n log n) |
| Composite Sort | O(n log n) | O(n log n) | O(n log n) |
### 空間複雜度： 
| 排序法 | 空間複雜度 |
|---|---|
| Insertion Sort | O(1) |
| Quick Sort | O(log n) |
| Merge Sort | O(n) |
| Heap Sort | O(1) |
| Composite Sort | O(n) |

### 測試結果
```
==================================================
 1. 測試各個排序是否正確 Correctness Test!!
==================================================
  - Insertion Sort : [PASS]
  - Merge Sort     : [PASS]
  - Heap Sort      : [PASS]
  - Quick Sort     : [PASS]
  - Composite Sort : [PASS]
[pass!!!]

=========================================================================================
 2. 最壞情況測試 Worst-Case Test Report (us)
=========================================================================================
n       Insertion       Merge           Heap(Max)       Quick(Max)      Composite
-----------------------------------------------------------------------------------------
500     128.37          15.19           21.57           7.68            19.06
1000    532.29          34.38           53.56           19.07           34.82
2000    1904.52         72.69           136.87          79.88           73.08
3000    4293.31         112.44          229.25          148.26          113.25
4000    7601.94         158.85          321.12          237.75          155.08
5000    11974.09        209.94          411.21          308.36          199.19

=========================================================================================
 3. 平均情況測試 Average-Case Test Report (us)
=========================================================================================
n       Insertion       Merge           Heap            Quick           Composite
-----------------------------------------------------------------------------------------
500     78.35           43.39           42.52           42.54           62.05
1000    290.61          91.53           91.48           73.82           90.98
2000    1018.62         190.57          191.05          155.93          188.99
3000    2249.39         297.30          296.95          240.76          294.28
4000    4062.92         404.99          409.80          331.13          399.34
5000    6161.88         515.49          547.21          427.71          513.32
=========================================================================================
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
此題分為兩部分：

1. 隨機插入與二元搜尋樹高度

    * 從一個空的二元搜尋樹（BST）開始。
    * 產生隨機數值並插入樹中，重複n次。
    * 測量最終樹的高度，並計算高度與 log₂(n) 的比值（height / log₂(n)）。
    * 對n=100, 500, 1000, 2000, 3000, ..., 10000 執行此過程。
    
    繪製比值（height / log₂(n)）隨n變化的圖表。
    
    理論上，隨機插入下，該比值應趨近於一個常數（約為 2）。

2. 刪除節點函數
    撰寫一個C++函數，從二元搜尋樹中刪除鍵值為k的節點並分析該函數的時間複雜度。

  

### 解題策略
(a)
建立空的二元搜尋樹 (BST)：一開始 root = nullptr。

隨機產生 n 個插入值：使用 rand() 產生整數。

插入規則：
若 key < node->data 插入左子樹

若 key > node->data 插入右子樹

相等則不插入（避免重複 key）

計算高度與比值：
高度 H 以「節點數」定義：空樹為 0，單一節點為 1
計算 ratio = H / log2(n)


(b)
實作 deleteNode(root, k) 刪除 BST 中 key = k 的節點，並維持 BST 性質不被破壞。

刪除分三種情況處理：

0 個子節點：直接刪除

1 個子節點：用唯一子節點取代被刪節點


2 個子節點：找「右子樹最小值」（inorder successor），用 successor 的值取代，再遞迴刪除 successor

## 程式實作
(a)
### IDE:
Microsoft Visual Studio Code C/C++


```cpp
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct Node {
    int data; Node* l, * r;
    Node(int v) : data(v), l(nullptr), r(nullptr) {}
};

Node* insertNode(Node* t, int x) {
    if (!t) return new Node(x);
    if (x < t->data) t->l = insertNode(t->l, x);
    else if (x > t->data) t->r = insertNode(t->r, x);
    return t;
}
int height(Node* t) { return t ? 1 + max(height(t->l), height(t->r)) : 0; }
void destroy(Node* t) { if (!t) return; destroy(t->l); destroy(t->r); delete t; }

Node* minNode(Node* t) { while (t && t->l) t = t->l; return t; }
Node* deleteNode(Node* t, int x) {
    if (!t) return nullptr;
    if (x < t->data) t->l = deleteNode(t->l, x);
    else if (x > t->data) t->r = deleteNode(t->r, x);
    else {
        if (!t->l || !t->r) {
            Node* c = t->l ? t->l : t->r;
            delete t; return c;
        }
        Node* s = minNode(t->r);
        t->data = s->data;
        t->r = deleteNode(t->r, s->data);
    }
    return t;
}

int main() {
    srand((unsigned)time(0));

    // (a)
    const int ns[] = { 100,500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000 };
    for (int n : ns) {
        Node* root = nullptr;
        unordered_set<int> used; used.reserve((size_t)(n * 1.3));
        for (int cnt = 0; cnt < n; ) {
            int v = rand();
            if (used.insert(v).second) { root = insertNode(root, v); cnt++; }
        }
        int h = height(root);
        cout << "n=" << n << " height=" << h
            << " ratio=" << (h / log2((double)n)) << "\n";
        destroy(root);
    }

```

```cpp
    // (b) 只示範呼叫 deleteNode，不輸出
    Node* t = nullptr;
    int keys[] = { 50,30,70,20,40,60,80 };
    for (int x : keys) t = insertNode(t, x);
    t = deleteNode(t, 20);
    t = deleteNode(t, 30);
    t = deleteNode(t, 50);
    destroy(t);

    return 0;
}

```
## 效能分析
(a)
空間複雜度：
BST 佔用空間（n 個節點）：O(n)

總空間複雜度：　O(n)

時間複雜度： 
時間複雜度： 
 |操作      | 平均時間     | 最壞時間 |
| ------- | -------- | ---- |
| insert  | O(log n) | O(n) |
| 插入 n 次 | O(log n) | O(n*n) |
| height  | O(n)     | O(n) |

(b)
時間複雜度： 
|操作      | 平均時間     | 最壞時間 |
| ------- | -------- |  -------- | 
| delete Ｎode | O(log n) | O(n) |


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

### 結論
1.測試結果可觀察到 H/log2(n) 大致落在約 2.1 ~ 2.6 的區間內,整體趨勢仍接近「常數」而非隨 n 線性成長
2.與隨機插入所形成的 BST 在平均情況下高度約為 Θ(log n) 的理論相同，因此 H/log2(n) 會接近常數

## 申論及開發報告

從圖中可見，比值大致落在約 2.1～2.7 間波動，最高約 2.66、最低約 2.1，整體平均大約在 2 附近。
![二元搜尋樹高度與log_2(n)比值](src/ratio.png)
### 優點
選擇函式版的三個優點
1.符合題目要求直觀
2.程式碼較短、易閱讀
3.彈性高、容易測試
### 缺點
選擇函式版的三個缺點
1.root 需要手動更新，容易用錯
2.記憶體管理責任在使用者：需要自己呼叫
3.封裝性較差
