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

class SlidingWindowMaxValue {
public:
    vector<int> getMaxWindow(const vector<int> &v, int w) {

        if (&v == nullptr || w < 1 || v.size() < w) {
            return vector<int>(0);
        }
        vector<int> rst;
        list<int> qmax;

        for (int i = 0; i < v.size(); i++) {

            if (!qmax.empty() && v[qmax.back()] <= v[i]) {
                qmax.pop_back();
            }

            qmax.push_back(i);

            if (qmax.front() <= i - w) {
                qmax.pop_front();
            }

            if (i >= w - 1) {
                rst.push_back(v[qmax.front()]);
            }
        }
        return rst;
    }
};

int main() {
    vector<int> arr = {4, 3, 5, 4, 3, 3, 6, 7};
    int w = 3;
    SlidingWindowMaxValue swmv;
    vector<int> rst = swmv.getMaxWindow(arr, w);
    for (auto n : rst) {
        cout << n << " ";
    }
    system("pause");
    return 0;
}