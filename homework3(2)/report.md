# 41343134
# 41343143
## 作業三 Sorting Project

## 解題說明
本專案的核心在於實作五種不同的排序方法，去改變資料的「性質」不同輸入資料 和「大小」不同資料量，來觀察演算法。

實作的五種排序演算法有 :

1. Insertion Sort : 是一種簡單直觀的排序演算法。它的運作方式如同整理手中的撲克牌
2. Quick Sort（Median-of-Three）: 是一種高效率的排序演算法，採用分治法（Divide and Conquer）策略  
3. Iterative Merge Sort : 是一種基於「分治法 (Divide and Conquer)」的排序演算法。
4. Heap Sort : 是一種基於「完全二元樹」概念的高效排序演算法。
5. Composite Sort : 是指多條件排序或基數排序（Radix Sort）的延伸。  

分治法為何 : 將一個難以直接解決的大問題，分割成多個規模較小、相似的子問題，各個解決後，再將子問題的答案合併以解決最初的大問題。 

--- 

## 解題策略

### 1. Insertion Sort（插入排序）排序方式 : 

它將資料分為「已排序」與「未排序」兩部分，每次從未排序中取出一個元素，

在已排序區中由後向前比對，找到適當位置插入，直到所有元素排序完成。

### 2. Quick Sort (快速排序)  排序方式:

透過挑選一個基準值（Pivot），將陣列分為左右兩部分，使左側元素皆小於基準值

右側元素皆大於基準值，再遞迴處理兩側子陣列來完成排序。

### 3. Iterative Merge Sort

它不使用遞迴，而是由底向上 (Bottom-Up) 進行，從小區塊開始兩兩合併，直到整個陣列排序完成。

### 4. Heap Sort

它將資料轉換成最大或最小堆積結構以找出極值。

### 5. Composite Sort

它的核心邏輯是設定多層級的優先順序：當第一優先條件的值相同時，會退而求其次根據第二條件排序，依此類推，直到所有條件比對完畢。

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
---

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

---

## 測試與驗證 

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
---

## 申論及開發報告
1.Heap 適合用來實作 Priority Queue，能在插入與刪除最小值時保持高效率，且能隨時維持「最小值在根」的特性。

2.使用 1-based 陣列存放完全二元樹，可以用簡單的索引運算得到父子節點位置，不需要額外指標，記憶體使用較節省且存取效率高。

3.核心功能:

* SiftUp：插入新元素後，只需要沿著父節點路徑往上修正，即可恢復 Min-Heap 性質。
  
* SiftDown：刪除根後將最後元素放到根，沿著較小子節點往下修正，即可恢復 Min-Heap 性質。
 
* Resize：在容量不足時擴充陣列，確保結構可處理更大輸入。

---

  ## 優點
  
  1. 時間效率穩定
  
  2. 陣列實作（1-based）結構簡單、效能佳

  3. 抽象介面清楚（MinPQ）

  ## 缺點
  
  1. 容量策略固定倍增，可能造成多餘記憶體

  2. 建堆方式為逐一 Push，建堆成本較高
