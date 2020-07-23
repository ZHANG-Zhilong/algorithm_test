#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <queue>
#include<unordered_map>
#include <algorithm>

using namespace std;


class Coins {
private:
    int process1(vector<int> arr, int index, int aim) {
        //index 可以自由使用index和之后所有的钱
        //aim：目标钱数
        //arr：不变的变量，面试数组
        //返回值：方法数量
        int res = 0;
        if (index == arr.size()) {  //我来到数组的最后，已经没有钱了，如果此时目标为零，则找到一种有效划分，之前选择无效
            res = aim == 0 ? 1 : 0;
        } else {
            for (int zhang = 0; zhang * arr[index] <= aim; zhang++) {
                res += process1(arr, index + 1, aim - zhang * arr[index]);
            }
        }
        return res;
    }

public:
    int coinsWay1(vector<int> arr, int aim) {
        if (aim < 0 || arr.empty()) {
            return 0;
        }
        return process1(arr, 0, aim);
    }

    int coinsWay2(vector<int> arr, int aim) {
        if (arr.empty() || aim < 0) {
            return 0;
        }
        vector<vector<int>> dp(arr.size(), vector<int>((size_t) aim + 1, 0));
        for (int i = 0; i < arr.size(); i++) {
            dp[i][0] = 1;
        }
        for (int j = 1; arr[0] * j <= aim; j++) {  //arr.size() ?+1?
            dp[0][(size_t) arr[0] * j] = 1;
        }
        for (int i = 1; i < arr.size(); i++) {
            for (int j = 1; j < (int) aim + 1; j++) {
                dp[i][j] = dp[(size_t) i - 1][j];
                dp[i][j] += (j - arr[i] >= 0) ? dp[i][(size_t) j - arr[i]] : 0;
            }
        }
        return dp[arr.size() - 1][aim];

    }
};

int main() {

    Coins c;
    vector<int> coins = {1, 2};
    cout << c.coinsWay1(coins, 5) << endl;
    cout << c.coinsWay2(coins, 5) << endl;
    system("pause");
    return 0;
}
