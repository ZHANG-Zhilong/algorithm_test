#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Code03_NeedParentheses {
public:
    int needParentheses(const string &str) {
        if (str.empty()) {
            return -1;
        }
        vector<int> dp(str.size(), 0);
        int pre = 0, ret = 0;
        for (int i = 1; i < str.size(); i++) {
            if (str[i] == ')') {
                pre = i - dp[i - 1] - 1;
                if (pre > 0 && str[pre] == '(') {
                    dp[i] = dp[i - 1] + 2 + (pre > 0 ? dp[pre - 1] : 0);
                }
            }
            ret = max(ret, dp[i]);
        }
        return ret;
    }
};

void play() {
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
