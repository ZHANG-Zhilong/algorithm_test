#include <iostream>
#include <random>
#include <vector>
#include <stack>
#include <queue>
#include <typeinfo>

using namespace std;


int getLessIndex(vector<int> v) {
    if (v.empty() || v.size() == 0) {
        return -1;
    }
    if (v.size() == 1 || v[0] < v[1]) {
        return 0;
    }
    if (v[v.size() - 2] > v[v.size() - 1]) {
        return v.size() - 1;
    }
    int left = 0, right = v.size() - 2;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (v[mid] > v[mid + 1]) {
            left = mid + 1;
        } else if (v[mid] > v[mid - 1]) {
            right = mid - 1;
        } else {
            return mid;
        }
        return left;
    }
}

void printVector(vector<int> v) {
    for (auto n : v) {
        cout << n << " ";
    }
    cout << endl;
}

int main() {

    vector<int> v = {6, 5, 3, 4, 6, 7, 8};
    printVector(v);
    int index = getLessIndex(v);
    cout << "index: " << index << ", value: " << v[index] << endl;
    system("pause");
}