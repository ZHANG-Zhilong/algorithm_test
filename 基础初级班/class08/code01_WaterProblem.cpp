#include <iostream>
#include <string>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <typeinfo>
#include <list>
#include <set>

using namespace std;

class WaterProblem {
public:

    int getWater1(const vector<int> &v) {
        if (&v == nullptr || v.size() < 3) {
            return 0;
        }
        int value = 0;
        for (int i = 1; i < v.size() - 1; i++) {
            int leftMax = 0;
            int rightMax = 0;

            for (int j = 0; j < i; j++) {
                leftMax = v[j] > leftMax ? v[j] : leftMax;
            }
            for (int j = v.size() - 1; j > i; j--) {
                rightMax = v[j] > rightMax ? v[j] : rightMax;
            }
            int water = min(leftMax, rightMax) - v[i];
            value += water > 0 ? water : 0;
        }
        return value;

    }

    int getWater2(const vector<int> &v) {
        if (&v == nullptr || v.size() < 3) {
            return 0;
        }

        size_t n = v.size();
        vector<int> leftMaxs(n, 0);
        vector<int> rightMaxs(n, 0);

        leftMaxs.at(0) = v.at(0);
        for (int i = 1; i < n; i++) {
            leftMaxs.at(i) = max(leftMaxs[i - 1], v[i]);
        }

        rightMaxs.at(n - 1) = v.at(n - 1);
        for (int j = n - 2; j >= 0; j--) {
            rightMaxs.at(j) = max(rightMaxs.at(j + 1), v.at(j));
        }

        int sumWater = 0;
        for (int i = 1; i < n - 1; i++) {
            int water = min(leftMaxs.at(i - 1), rightMaxs.at(i + 1)) - v[i];
            sumWater += water > 0 ? water : 0;
        }
        return sumWater;
    }

    int getWater3(const vector<int> &v) {

        if (&v == nullptr || v.size() < 3) {
            return 0;
        }

        size_t lp = 0, rp = v.size() - 1;
        int leftMax = INT_MIN;
        int rightMax = INT_MIN;
        int sumWater = 0;
        while (lp <= rp) {
            leftMax = leftMax > v.at(lp) ? leftMax : v.at(lp);
            rightMax = rightMax > v.at(rp) ? rightMax : v.at(rp);
            if (leftMax <= rightMax) {
                int water = leftMax - v.at(lp++);
                sumWater += water > 0 ? water : 0;
            } else {
                int water = rightMax - v.at(rp--);
                sumWater += water > 0 ? water : 0;
            }
        }
        return sumWater;
    }

};

inline int mod20(int t) { return abs(t % 20); }

vector<int> generateRandomArray() {
    random_device rd;
    int size = rd() % 15;
    vector<int> myvector(size, 0);
    seed_seq seed4{rd(), rd()};
    seed4.generate(myvector.begin(), myvector.end());
    transform(begin(myvector), end(myvector), begin(myvector), mod20);
    return myvector;
}

int main() {

    for (int i = 0; i < 10000; i++) {
        vector<int> v = generateRandomArray();
        WaterProblem wp;
        int w1 = wp.getWater1(v);
        int w2 = wp.getWater2(v);
        int w3 = wp.getWater3(v);
        if (w1 != w2 || w1 != w3) {
            cout << "fuck, error!" << endl;
            cout << wp.getWater1(v) << endl;
            cout << wp.getWater2(v) << endl;
            cout << wp.getWater3(v) << endl;
            for (auto n : v) { cout << n << " "; }
            exit(-1);
        }
    }

    system("pause");
    return 0;
}