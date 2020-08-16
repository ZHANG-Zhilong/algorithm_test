#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>

using namespace std;

class Code05_UniqueBST {
public:
    static int process(const int N) {
        if (N < 0) {
            return 0;
        }
        if (N == 1) {
            return 1;
        }
        if (N == 2) {
            return 2;
        }
        int leftNum = 0, rightNum = 0, ret = 0;
        for (int i = leftNum; i <= N - 1; i++) {
            leftNum = process(i);
            rightNum = process(N - i - 1);
            ret += leftNum * rightNum;
        }
        return ret;
    }

    static int dp(const int N) {
        if (N <= 0) {
            return 0;
        }
        if (N < 2) {
            return 1;
        }
        vector<int> dp(N + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j <= i - 1; j++) {
                dp[i] += dp[i - j - 1] * dp[j];
            }
        }
        return dp[N];
    }
};

void play() {
    cout << Code05_UniqueBST::dp(4);
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
