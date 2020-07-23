#include <iostream>
#include <random>
#include <vector>
#include <queue>
#include <typeinfo>

using namespace std;

class MedianFinder {

private:
    priority_queue<int, vector<int>, less<int>> bigHeap;
    priority_queue<int, vector<int>, greater<int>> smallHeap;
    int _num;
public:
    MedianFinder() {
        _num = 0;
    }

    void addNum(int num) {
        _num = num;
        if (bigHeap.empty()) {
            bigHeap.push(_num);
            modifyTwoHeapSize();
            return;
        }
        if (bigHeap.top() >= _num) {
            bigHeap.push(_num);
            modifyTwoHeapSize();
            return;
        } else {
            if (smallHeap.empty()) {
                smallHeap.push(_num);
                modifyTwoHeapSize();
                return;
            }
            if (smallHeap.top() <= _num) {
                smallHeap.push(_num);
            } else {
                bigHeap.push(_num);
            }
        }
        modifyTwoHeapSize();
    }

    double findMedian() {
        int bigSize = bigHeap.size();
        int smallSize = smallHeap.size();
        if (bigSize + smallSize == 0) {
            return 0;
        }
        if (bigSize == 0) {
            int val = smallHeap.top();
            smallHeap.pop();
            return val;
        } else if (smallSize == 0) {
            int val = bigHeap.top();
            bigHeap.pop();
            return val;
        }
        int big = bigHeap.top();
        int small = smallHeap.top();
        while (!bigHeap.empty()) bigHeap.pop();
        while (!smallHeap.empty()) smallHeap.pop();

        if (((bigSize + smallSize) & 1) == 0) {
            double val = (small + big) / 2;
            return val;
        }
        return bigSize > smallSize ? big : small;
    }

    int modifyTwoHeapSize() {
        if (bigHeap.size() - smallHeap.size() == 2) {
            int val = bigHeap.top();
            bigHeap.pop();
            smallHeap.push(val);
        } else if (smallHeap.size() - bigHeap.size() == 2) {
            int val = smallHeap.top();
            smallHeap.pop();
            bigHeap.push(val);
        }
        return 0;
    }
};

class GetRandomArray {
public:
    vector<int> operator()(int size, int min, int max) {
        random_device rd;
        vector<int> v;
        if (size <= 0 || max == min) {
            size = rd() % 10;
        }
        int len = abs(max - min);
        for (int i = 0; i < size; i++) {
            v.push_back(rd() % len);
        }
        return v;
    }
};

class PrintVector {
public:
    void operator()(vector<int> v) {
        for (auto n : v) {
            printf("%d ", n);
        }
        printf("\n");
    }
};

class GetMedianOfArray {
private:
    double _median;
public:
    GetMedianOfArray() {
        _median = 0.0;
    }

    double operator()(vector<int> v) {
        sort(v.begin(), v.end());
        int mid = (v.size() - 1) / 2;
        if ((v.size() & 1) == 0) {
            _median = (v[mid] + v[mid + 1]) / 2;
        } else {
            _median = v[mid];
        }
        return _median;
    }
};

int main() {
    PrintVector printv;
    GetRandomArray getRandomArray;
    MedianFinder medianFinder;
    GetMedianOfArray getArrayMedian;

    //int count = 1;
    int count = 100;
    for (int i = 0; i < count; i++) {
        vector<int> v = getRandomArray(-1, 0, 10);
        //vector<int> v = {1,5,7,1,7};
        printv(v);
        for (int i = 0; i < v.size(); i++) {
            medianFinder.addNum(v[i]);
        }
        double rst = medianFinder.findMedian();
        double rst2 = getArrayMedian(v);

        if (rst != rst2) {
            printf("error, %dth test.\n", i);
            printv(v);
            printf("medianFinder: %.3lf\n", rst);
            printf("getArrayMedian: %.3lf\n", rst2);
            system("pause");
        }
    }
    system("pause");
}