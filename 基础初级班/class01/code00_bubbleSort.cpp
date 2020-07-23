#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void bubleSort(vector<int> &v) {
    if (v.size() < 2) {
        return;
    }
    for (int i = v.size() - 1; i > 0; i--) {
        for (int j = 0; j < v.size() - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
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

vector<int> generRanArr(int size, int value) {
    vector<int> v;
    for (int i = 0; i < size; i++) {
        int temp = rand() % value;
        if (temp % 2 == 0) {
            temp *= -1;
        }
        v.push_back(temp);
    }
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
            cout << "fucking fuck" << endl;
            exit(-1);
            break;
        }
    }
    cout << "nice\n";
    system("pause");


}