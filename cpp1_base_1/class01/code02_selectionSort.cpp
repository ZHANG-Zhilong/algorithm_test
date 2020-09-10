#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;


void bubleSort(vector<int> &v) {
    if (v.size() < 2) {
        return;
    }
    for (int i = 0; i < v.size(); i++) {
        int maxid = i;
        for (int j = i; j < v.size(); j++) {
            if (v[j] <= v[maxid]) {
                maxid = j;
            }
        }
        swap(v[i], v[maxid]);
    }

}

//用于测试
void rightMethod(vector<int> &v) {
    sort(v.begin(), v.end());
}

void printVector(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ' ';
    }
    cout << ';' << endl;
}

int mod100(int i) {
    return i % 100;
}

vector<int> generRanArr(int size, int value) {
    vector<int> v(size, 0);
    random_device rd;
    seed_seq seed4 = {rd(), rd(), rd()};
    seed4.generate(begin(v), end(v));
    transform(begin(v), end(v), begin(v), mod100);
    return v;
}

bool isEqual(vector<int> v1, vector<int> v2) {
    if (v1.size() != v2.size()) {
        return false;
    }
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}

int main() {

    int testTimes = 200;
    int size = 10;
    int value = 100;
    bool succeed = true;

    for (int i = 0; i < testTimes; i++) {
        vector<int> v1 = generRanArr(size, value);
        vector<int> v2 = v1;
        bubleSort(v1);
        rightMethod(v2);
        if (!isEqual(v1, v2)) {
            succeed = false;
            printVector(v1);
            printVector(v2);
            cout << "fucking fuck " << i << endl;
            exit(-1);
            break;
        }

    }
    cout << "nice\n";
    system("pause");


}