#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include<unordered_map>
#include <algorithm>

using namespace std;

class MostXOR {
public:
    int mostXor(vector<int> arr) {
        if (arr.empty()) {
            return 0;
        }
        int ans = 0;
        int zxor = 0;
        vector<int> dp(arr.size(), 0);
        unordered_map<int, int> mymap;
        mymap[0] = -1;  // result position
        for (int i = 0; i < arr.size(); i++) {
            zxor ^= arr[i];
            if (mymap.count(zxor) > 0) {
                int pre = mymap[zxor];
                dp[i] = pre == -1 ? 1 : (dp[pre] + 1);
            }
            if (i > 0) {
                dp[i] = max(dp[(size_t) i - 1], dp[i]);
            }
            mymap[zxor] = i;
            ans = max(ans, dp[i]);
        }
        return ans;


    }
};


class LongestSumSubArrayLength {

public:
    int maxLength(vector<int> arr, int aim) {
        if (arr.empty()) {
            return 0;
        }
        unordered_map<int, int> preSum;  // sum, index
        preSum.insert(pair<int, int>(-1, 0));  //very important
        int len = 0;
        int sum = 0;
        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];
            if (preSum.count(sum - aim) > 0) {
                len = max(len, i - preSum[sum - aim]);
            }
            if (preSum.count(sum) == 0) {
                preSum.insert(pair<int, int>(sum, i));
            }
        }
        return len;
        //给定目标数值，求得数组中子数组相加可得aim的最长子数组长度
        //逆向求解：求一个数为结尾的子数组，相加可得aim的最长子数组
        //preSum中存储以第i个元素为结尾的，从第零个元素开始的子数组累加和
        //若以arr[i]结尾的sum为2000， aim为1200，求从零开始累加到800的位置
        //该位置下一个位置元素开始累加到i位置，子数组之和就是aim
    }
};

int main() {

    system("pause");
    return 0;
}
