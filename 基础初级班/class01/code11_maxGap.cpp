#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;


int bucket(int num, int len, int max, int min) {
    return (num - min) * len / (max - min);
}

int maxGap(vector<int> v) {
    if (v.empty() || v.size() < 2) {
        return 0;
    }

    int len = v.size();
    int max = INT_MIN;
    int min = INT_MAX;

    for (auto n : v) {
        max = max > n ? max : n;
        min = min < n ? min : n;
    }
    if (max == min) {
        return 0;
    }

    vector<bool> bhas(len + 1, false);
    vector<int> bmax(len + 1, INT_MIN);
    vector<int> bmin(len + 1, INT_MAX);
    int bid = 0;
    for (int i = 0; i < len; i++) {
        bid = bucket(v[i], len, max, min);
        bhas[i] = true;
        bmax[i] = bmax[i] > v[i] ? bmax[i] : v[i];
        bmin[i] = bmin[i] < v[i] ? bmin[i] : v[i];
    }

    int res = bmax[0];
    for (int i = 1; i < len + 1; i++) {
        if (bhas[i] == true) {
            res = res > (bmin[i] - bmax[i - 1]) ? res : bmax[i - 1];
        }
    }
    return res;
}

//for test
int comparator(vector<int> &v) {
    if (v.size() < 2) {
        return 0;
    }
    sort(begin(v), end(v));
    int maxgap = INT_MIN;
    for (int i = 0; i < v.size() - 1; i++) {
        maxgap = max((v[i + 1] - v[i]), maxgap);
    }
    return maxgap;
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

bool isEqual(int a, int b) {
    return a == b;
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
        random_device rd;
        size = abs((int) rd() % 100) + 1;
        vector<int> v1 = generateRandomArray(size, value);
        vector<int> v2(v1.size(), 0);
        copy(begin(v2), end(v2), begin(v1));
        vector<int> v3(v1.size(), 0);
        copy(begin(v3), end(v3), begin(v1));

        if (!isEqual(maxGap(v1), comparator(v2))) {
            succeed = false;
            printVector(v1);
            printVector(v2);
            printVector(v3);
            break;
        }
        //printVector(v1);
    }

    double endtime = time(NULL);
    double span = (endtime - startime);
    cout << "execute time cost " << span << "s" << endl;
    string str = succeed ? "nice" : "fucking fuck!";
    cout << str << endl;
    system("pause");
}