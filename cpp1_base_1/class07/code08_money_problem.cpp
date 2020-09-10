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

class MoneyProblem {
public:
    bool money1(const vector<int> &arr, int aim) {
        process1(arr, 0, 0, aim);
    }

    bool process1(const vector<int> &arr, int i, int sum, int aim) {

        if (sum == aim) return true;

        if (i == arr.size()) return false;

        return process1(arr, i + 1, sum, aim) || process1(arr, i + 1, sum + arr.at(i), aim);
    }

    bool money2(const vector<int> &arr, int aim) {
        vector<vector<int>> dp(arr.size() + 1, vector<int>(aim + 1, 0));
        for (int i = 0; i < arr.size() + 1; i++) {
            dp.at(i).at(aim) = true;
        }
        for (int i = arr.size() - 1; i >= 0; i--) {
            for (int j = aim; j >= 0; j--) {
                dp[i][j] = dp[i + 1][j];
                if (j + arr[i] <= aim) {
                    dp[i][j] = dp[i][j] || dp[i][j + arr[i]];
                }
            }
        }
        return dp[0][0];

    }
};

int main() {
    vector<int> v = {1, 4, 8};
    MoneyProblem mp;
    cout << mp.money1(v, 12) << endl;
    cout << mp.money2(v, 12) << endl;
    system("pause");
    return 0;
}