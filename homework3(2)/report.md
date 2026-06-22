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

### 1. Insertion Sort（插入排序）方式 : 

它將資料分為「已排序」與「未排序」兩部分，每次從未排序中取出一個元素，

在已排序區中由後向前比對，找到適當位置插入，直到所有元素排序完成。

具備極高的高快取

### 2. Quick Sort (快速排序)  方式 :

透過挑選一個基準值（Pivot），將陣列分為左右兩部分，使左側元素皆小於基準值

右側元素皆大於基準值，再遞迴處理兩側子陣列來完成排序。

採用了 Median-of-Three（三數取中法） 來挑選 Pivot

取一個元素作為Pivot基準，來分割左右兩側的元素。


### 3. Iterative Merge Sort (迭代版合併排序) 方式 :
 
它不使用遞迴，而是由底向上 (Bottom-Up) 進行，從小區塊開始兩兩合併，直到整個陣列排序完成。

當資料量極大時，大問題切成完全獨立的小問題是個最穩定的排序方法。



### 4. Heap Sort (堆積排序) 方式 :

它將資料轉換成最大或最小堆積結構(tree)進行排序找出極值。

1. 建立最大或最小堆積樹
2. 提取最大或最小值交換並固定
3. 將Heap大小-1再重複調整成最大最小樹
4. 重複2跟3直到排序正確

### 5. Composite Sort (混合排序) 方式 : 

根據眼前的「資料量大小」，切換最適合的演算法

當資料量很大（ > 32 個元素）時使用 Merge Sort（合併排序），快速把資料切大塊、分組處理。
當資料被切到很小（ < 32 個元素）時使用 Insertion Sort（插入排序執行。

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
        swap(a[i], a[j]); // 將目前的元素與隨機位置的元素對調
    }
}
void InsertionSort(int* a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
    // 只要前面的元素比 key 大，就往後挪一格，幫 key 騰出空間
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}
int MedianOfThree(int* a, int low, int high) {
    int mid = low + (high - low) / 2;
    if (a[low] > a[mid]) swap(a[low], a[mid]); //確保 low <= mid
    if (a[low] > a[high]) swap(a[low], a[high]); // 確保 low <= high
    if (a[mid] > a[high]) swap(a[mid], a[high]); // 確保 mid <= high
    swap(a[mid], a[high - 1]); // 把 Pivot 隱藏在 high - 1 的位置
    return a[high - 1];
}
void QuickSortHelper(int* a, int low, int high) {
    if (low + 10 <= high) {
        int pivot = MedianOfThree(a, low, high);
        int i = low;
        int j = high - 1;
        while (true) {
            while (a[++i] < pivot); // 左指標向右找大於等於 pivot 的數
            while (a[--j] > pivot); // 右指標向左找小於等於 pivot 的數
            if (i < j) swap(a[i], a[j]);
            else break;
        }
        swap(a[i], a[high - 1]); // 把 Pivot 放回兩邊分割點的交界處
        QuickSortHelper(a, low, i - 1); // 遞迴處理左半邊
        QuickSortHelper(a, i + 1, high); // 遞迴處理右半邊
    }
    else {
        InsertionSort(a + low, high - low + 1); // 元素量太小時，直接改用插入排序
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
    while (i <= m) temp[k++] = a[i++]; // 複製左邊剩餘的資料
    while (j <= r) temp[k++] = a[j++]; // 複製右邊剩餘的資料
    for (i = l; i <= r; i++) a[i] = temp[i]; // 把排序好的輔助陣列覆蓋回原陣列

}

void MergeSort(int* a, int n) {
    int* temp = new int[n]; // 動態配置一塊與原陣列一樣大的輔助空間
    // curr_size 代表目前要合併的子陣列長度，以 2 的冪次方不斷翻倍：1, 2, 4, 8
    for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
    // left_start 代表每次合併兩兩分組的起點位置
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
    int temp = a[i]; // 暫存目前準備要「下沉」的根節點
    for (; 2 * i + 1 < n; i = child) {
        child = 2 * i + 1; // 找出左子節點位置
        // 如果右子節點存在，且右子節點比左子節點大，那就把目標轉向右子節點
        if (child != n - 1 && a[child + 1] > a[child]) {
            child++;
        }
        // 如果子節點比暫存的根節點大，就把子節點拉上來替代父節點
        if (temp < a[child]) {
            a[i] = a[child];
        }
        else {
            break; // 父節點已經比子節點都大，符合 Max Heap 性質，停止下沉
        }
    }
    a[i] = temp; 將原本的根節點安置在最終點
}
void HeapSort(int* a, int n) {
    // 從最後一個非葉子節點開始，由底向上建立一個完整的 Max Heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        MaxHeapify(a, i, n);
    }
    // 每次將堆頂最大值交換到陣列最尾端固定，並縮小 Heap 規模重新調整
    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]); // 把最大值換到陣列後方固定
        MaxHeapify(a, 0, i); // 對前方剩餘的 i 個元素重新進行堆積下沉調整
    }
}
void CompositeSort(int* a, int n) {
    if (n <= 32) {
        InsertionSort(a, n); // 小資料量：直接利用插入排序
    }
    else {
        MergeSort(a, n); // 大資料量：使用高穩定度的合併排序拆分
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
## 結論

### 演算法正確性驗證 (Correctness Test) 
透過動態記憶體配置產生一組隨機亂數序列，並將演算法的輸出結果與 C++ 標準函式庫的 std::sort 進行比對，以此作為判斷演算法實作正確性。

### 最壞情況分析 (Worst-case Analysis)
強迫排序演算法去做最多次的比較與資料交換，用來測出它們的最慢時間極限。
### 平均情況測試(Average-case Analysis)
將沒有任何規律的隨機數列用來測試，並計算平均花費時間。
### 效能綜合比較(Performance Comparison)
將最壞與平均時間收集起來並輸出成表格。

## 申論及開發報告

本次作業實作與建構多種排序演算法加深了對抽象理論的理解，更在真實硬體環境的數據觀測中，

體會到「理論漸進複雜度」與「底層物理執行效能」之間的微妙動態差異。

### 1. 理論與實作差異

寫程式時發現：
快速排序（Quick Sort）：快速排序如果運氣很差，選到極端的大數或小數當基準，會排得超級慢。我們實作了「三個數字挑中間值」的方法，讓它幾乎不會遇到最卡的情況。

混合排序（Composite Sort）：資料很多時它用（Merge Sort），資料被切到剩下下一點點（小於32個）時，它就立刻換成（Insertion Sort）。這種看情況切換的方法，讓整體速度變快非常多。

合併排序（Merge Sort）不用遞迴：合併排序原本要，一層層不斷呼叫遞迴，這很吃記憶體也浪費時間。我們改成用「迴圈」一層層直接往上打包，省去了頻繁呼叫函式的時間，也完全不用擔心記憶體會爆掉（Stack Overflow）。


---

 
