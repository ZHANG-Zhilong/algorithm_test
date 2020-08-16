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

class Knapsack {

public:
    int maxValue(const vector<int> &w, const vector<int> &v, int bag) {
        return process1(w, v, 0, 0, bag);
    }

    int process1(const vector<int> &w, const vector<int> &v, int i, int alreadyValue, int bag) {
        if (alreadyValue > bag) {  //20行和23行的先后顺序非常重要
            return INT_MIN;  //invalid value.  剪支操作
        }
        if (i == w.size()) {
            return 0;
        }
        int value1 = process1(w, v, i + 1, alreadyValue, bag);
        int value2 = v[i] + process1(w, v, i + 1, alreadyValue + w[i], bag);
        return max(value1, value2);
    }

    int maxValue2(const vector<int> &weight, const vector<int> &value, int bag) {
        vector<vector<int>> dp(weight.size() + 1, vector<int>(bag + 1, 0));
        for (int i = weight.size() - 1; i >= 0; i--) {
            for (int j = bag; j >= 0; j--) {
                dp.at(i).at(j) = dp.at(i + 1).at(j);
                if (j + weight[i] <= bag) {
                    dp.at(i).at(j) = max(dp.at(i).at(j), value[i] + dp.at(i + 1).at(j + weight[i]));
                }
            }
        }
        return dp[0][0];
    }
};

int main() {
    vector<int> weight{1, 2, 3, 6, 7};
    vector<int> value{2, 3, 4, 7, 4};
    Knapsack knapsack;
    cout << knapsack.maxValue(weight, value, 10) << endl;
    cout << knapsack.maxValue2(weight, value, 10) << endl;

    system("pause");
    return 0;
}