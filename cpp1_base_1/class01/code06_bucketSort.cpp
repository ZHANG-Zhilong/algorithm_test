﻿#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

void bucketSort(vector<int> v) {
    if (v.empty() || v.size() < 2) {
        return;
    }
    int maxv = 0;
    for (int i = 0; i < v.size(); i++) {
        maxv = v[i] > maxv ? v[i] : maxv;
    }
    vector<int> bucket(maxv + 1, 0);
    for (auto n : v) {
        bucket[n]++;
    }
    int j = 0;
    for (int i = 0; i < bucket.size(); i++) {
        while (bucket[i] > 0 && j < v.size()) {
            v[j++] = i;
        }
    }

}

//for test
int comparator(vector<int> &v) {
    if (v.empty() || v.size() < 2) {
        return 0;
    }
    int ret = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = i; j < v.size(); j++) {
            ret += v[i] < v[j] ? v[j] : 0;
        }
    }
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
    vector<int> vt(1, 0);
    seed4.generate(begin(vt), end(vt));
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

        bucketSort(v1);
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