#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

void mergeSort(vector<int> v);

void mergeSort(vector<int> v, int l, int r);

void merge(vector<int> v, int l, int mid, int r);

void mergeSort(vector<int> v) {
    if (v.size() < 2 || v.empty()) {
        return;
    }
    mergeSort(v, 0, v.size() - 1);
}

void mergeSort(vector<int> v, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = l + ((r - l) >> 1);
    mergeSort(v, l, mid);
    mergeSort(v, mid + 1, r);
    merge(v, l, mid, r);
}

void merge(vector<int> v, int l, int mid, int r) {
    int p1 = l, p2 = mid + 1;
    int i = 0;
    vector<int> help(r - l + 1, 0);
    while (p1 <= mid && p2 <= r) {
        help[i++] = v[p1] < v[p2] ? v[p1++] : v[p2++];
    }
    while (p1 <= mid) {
        help[i++] = v[p1++];
    }
    while (p2 <= r) {
        help[i++] = v[p2++];
    }
    for (int i = 0; i < help.size(); i++) {
        v[l++] = help[i];
    }
}

//for test
void comparator(vector<int> &v) {
    sort(v.begin(), v.end());
}


inline int mod100(int i) {
    return i % 100;
}

//for test
vector<int> generateRandomArray(int size, int value) {
    vector<int> v(size, 0);
    random_device rd;
    seed_seq seed4 = {rd(), rd(), rd()};
    seed4.generate(begin(v), end(v));
    transform(begin(v), end(v), begin(v), mod100);
    return v;
}

//for test
bool isEqual(vector<int> v1, vector<int> v2) {
    if ((v1.empty() && !v2.empty()) || (!v1.empty() && v2.empty())) {
        return false;
    }
    if (v1.empty() && v2.empty()) {
        return true;
    }
    if (v1.size() != v2.size()) {
        return false;
    }
    //考虑使用transfrom优化
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}

//for test
int randz() {
    random_device rd;
    seed_seq seed4 = {rd(), rd(), rd()};
    vector<int> vt = {0, 0};
    seed4.generate(begin(vt), begin(vt) + 1);
    return abs(vt[0] % 10) + 1;
}

//for test
void printVector(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ' ';
    }
    cout << ';' << endl;
}


int main() {

    int testTimes = 15000;
    int size = 10;
    int value = 100;
    bool succeed = true;

    double startime = time(NULL);
    //对数器，测试testTimes次数
    for (int i = 0; i < testTimes; i++) {

        //生成不同大小，且内容随机的数组
        //random 类的使用 http://c.biancheng.net/view/635.html
        size = randz();
        vector<int> v1 = generateRandomArray(size, value);
        vector<int> v2(v1.size(), 0);
        copy(begin(v2), end(v2), begin(v1));
        vector<int> v3(v1.size(), 0);
        copy(begin(v3), end(v3), begin(v1));

        mergeSort(v1);
        comparator(v2);
        if (!isEqual(v1, v2)) {
            succeed = false;
            printVector(v1);
            printVector(v2);
            printVector(v3);
            cout << "fucking fuck " << i << endl;
            exit(-1);
            break;
        }

        //printVector(v1);

    }

    double endtime = time(NULL);
    double span = (endtime - startime);
    cout << "execute time cost " << span << "s" << endl;
    cout << "nice\n";
    system("pause");


}