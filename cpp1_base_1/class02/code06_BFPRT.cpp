#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

class BFPRT {

public:
    vector<int> getMinKNumsByHeap(vector<int> arr, int k); //O(N*logK)
    void heapInsert(vector<int> &arr, int value, int index);

    void heaptify(vector<int> &arr, int index, int heapSize);

    vector<int> getMinKNumsByBFPRT(vector<int> arr, int k);  //O(N)
    int getMinKthNumByBFPRT(vector<int> arr, int k);

    int select(vector<int> arr, int begin, int end, int i);

    int medianOfMedians(vector<int> arr, int begin, int end);

    vector<int> partition(vector<int> &arr, int begin, int end, int pivotValue);

    int getMedian(vector<int> arr, int begin, int end);

    void insertionSort(vector<int> &arr, int begin, int end);

    void printVect(vector<int> arr);
};

vector<int> BFPRT::getMinKNumsByHeap(vector<int> arr, int k) {
    if (k < 1 || k > arr.size()) {
        return arr;
    }
    vector<int> kHeap(k, 0);
    for (int i = 0; i < k; i++) {
        heapInsert(kHeap, arr[i], i);
    }
    for (int i = k; i < arr.size(); i++) {
        if (arr[i] < kHeap[0]) {
            kHeap[0] = arr[i];
            heaptify(kHeap, 0, kHeap.size());
        }
    }
    return kHeap;
}

void BFPRT::heapInsert(vector<int> &arr, int value, int index) {
    //insert value one by one like use array.
    //this is big root heap.
    //child index = parentIndex*2+1 or +2
    //parent's index = (childIndex-1) /2
    arr[index] = value;
    while (index != 0) {
        int pindex = (index - 1) / 2;
        if (arr[index] > arr[pindex]) {
            swap(arr[index], arr[pindex]);
        } else { break; }
        index = pindex;
    }
}

void BFPRT::heaptify(vector<int> &arr, int index, int heapSize) {
    //insert value in pos 0, justify the big root heap automatically.
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
    while (left < heapSize) {
        if (arr[left] > arr[largest]) {
            largest = left;
        }
        if (arr[right] > arr[largest] && right < heapSize) {
            largest = right;
        }
        if (index != largest) {
            swap(arr[index], arr[largest]);
        } else { break; }
        index = largest;
        left = 2 * index + 1;
        right = 2 * index + 2;
    }
}

vector<int> BFPRT::getMinKNumsByBFPRT(vector<int> arr, int k) {
    if (k < 1 || k > arr.size()) {
        cout << "input err getMinKNumsBFPRT" << endl;
        return arr;
    }
    int kthMin = getMinKthNumByBFPRT(arr, k);
    vector<int> rst(k, 0);
    int index = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] < kthMin && i < rst.size()) {
            //if there are repeated nums? may be beyond the boundary.
            rst[index++] = arr[i];
        }
    }
    while (index < k) {
        rst[index++] = kthMin;
    }
    return rst;

}

int BFPRT::getMinKthNumByBFPRT(vector<int> arr, int k) {
    return select(arr, 0, arr.size() - 1, k - 1);
}

int BFPRT::select(vector<int> arr, int begin, int end, int i) {
    if (begin == end) {
        return arr[begin];
    }
    int pivot = medianOfMedians(arr, begin, end);
    vector<int> pivotRange = partition(arr, begin, end, pivot);
    if (i >= pivotRange[0] && i <= pivotRange[1]) {
        return arr[i];
    } else if (i < pivotRange[0]) {
        return select(arr, begin, pivotRange[0] - 1, i);
    } else {
        return select(arr, pivotRange[1] + 1, end, i);
    }
}

int BFPRT::medianOfMedians(vector<int> arr, int begin, int end) {
    int length = end - begin + 1;
    int offset = length % 5 == 0 ? 0 : 1;
    int size = length / 5 + offset;
    vector<int> medians(size, 0); //offset用来修正medians的长度
    for (int i = 0; i < medians.size(); i++) {
        int beginI = begin + i * 5;
        int endI = beginI + 4;
        medians[i] = getMedian(arr, beginI, min(end, endI));
    }
    return select(medians, 0, medians.size() - 1, medians.size() / 2);//缩小问题规模，如未缩小，递归无法终止。
}

vector<int> BFPRT::partition(vector<int> &arr, int begin, int end, int pivotValue) {
    //返回等于区域的左右边界，游标和小于区元素交换，游标正常前移，和大于区交换，游标不动。
    int small = begin - 1;
    int big = end + 1;
    int cur = begin;
    while (cur != big) {
        if (arr[cur] < pivotValue) {
            swap(arr[++small], arr[cur++]);
        } else if (arr[cur] > pivotValue) {
            swap(arr[--big], arr[cur]); //此处的cur保持不动！！！，否则会错误
        } else {
            cur++;
        }
    }
    vector<int> equalRange = {small + 1, big - 1};
    return equalRange;
}

int BFPRT::getMedian(vector<int> arr, int begin, int end) {
    //不是求中位数，是求接近中位数的那个元素
    insertionSort(arr, begin, end);
    int sum = begin + end;
    int mid = sum / 2 + sum % 2;
    return arr[mid];
}

void BFPRT::insertionSort(vector<int> &arr, int begin, int end) {
    for (int i = begin + 1; i != end + 1; i++) {
        for (int j = i; j != begin; j--) {
            if (arr[j - 1] > arr[j]) {
                swap(arr[j], arr[j - 1]);
            } else { break; }
        }
    }
}

void BFPRT::printVect(vector<int> arr) {
    for (int n : arr) {
        cout << n << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {6, 9, 1, 3, 1, 2, 2, 5, 6, 1, 3, 5, 9, 7, 2, 5, 6, 1, 9};
    // sorted : { 1, 1, 1, 1, 2, 2, 2, 3, 3, 5, 5, 5, 6, 6, 6, 7, 9, 9, 9 }
    //vector<int> arr = { 1,2,3,5 };
    BFPRT bfprt;
    bfprt.printVect(bfprt.getMinKNumsByHeap(arr, 5));
    bfprt.printVect(bfprt.getMinKNumsByBFPRT(arr, 5));
    system("pause");
    return 0;
}
