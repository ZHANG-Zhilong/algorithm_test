#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

//四种尝试模型：从左到右、范围尝试、数据做行列、分支限界
class Code02_NumToStringWays {
public:
    static int convertWays(const vector<int> &arr) {
        if (arr.empty()) {
            return -1;
        }
        return process(arr, 0);
    }

    //0～index-1已经转换完毕
    //arr[index, ...]还有多少种有效的字符表达
    static int process(const vector<int> &arr, int index) {
        if (index == arr.size()) {
            return 1;
        }
        //arr[index] 若为零，直接返回零
        if (arr[index] == 0) {
            return 0;
        }
        //arr[index] as one character
        int ret = 0;
        if (index + 1 <= arr.size()) {
            ret += process(arr, index + 1);
        }
        //arr[index] and arr[index+1] as one character
        if (index + 2 <= arr.size() && arr[index] * 10 + arr[index] + 1 < 27) {
            ret += process(arr, index + 2);
        }
        return ret;
    }

    static int dpWays(const vector<int> &arr) {
        if (arr.empty()) {
            return -1;
        }
        const int N = arr.size();
        vector<int> dp(N + 1, 0);
        dp[N] = 1;
        dp[N - 1] = arr[N - 1] == 0 ? 0 : 1;
        for (int i = N - 2; i >= 0; i--) {
            if (arr[i] == 0) {
                dp[i] == 0;
            } else {
                dp[i] = dp[i + 1];
                if (arr[i] * 10 + arr[i + 1] < 27) {
                    dp[i] += dp[i + 2];
                }
            }
        }
        return dp.front();
    }
};

void play() {
    vector<int> arr{1, 1, 1, 1, 4, 3, 3, 1, 1};
    cout << Code02_NumToStringWays::convertWays(arr) << endl;
    cout << Code02_NumToStringWays::dpWays(arr) << endl;
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
