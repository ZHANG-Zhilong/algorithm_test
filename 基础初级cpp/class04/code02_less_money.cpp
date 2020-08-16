#include <iostream>
#include <random>
#include <vector>
#include <queue>
#include <typeinfo>

using namespace std;

class code02_Less_Money {
private:
    priority_queue<int, vector<int>, greater<int>> smallHeap;
    int _lessMoney;
public:
    code02_Less_Money() {
        _lessMoney = 0;
    }

    int lessMoney(vector<int> v) {

        if (v.empty()) {
            return _lessMoney;
        }

        for (auto n : v) {
            smallHeap.push(n);
        }

        while (smallHeap.size() > 1) {
            int val1 = smallHeap.top();
            smallHeap.pop();
            int val2 = smallHeap.top();
            smallHeap.pop();

            smallHeap.push(val1 + val2);
            _lessMoney += val1 + val2;
        }
        return _lessMoney;
    }

};

int main() {
    code02_Less_Money lm;
    vector<int> v = {10, 20, 30};
    int rst = lm.lessMoney(v);
    cout << rst;
    system("pause");
}