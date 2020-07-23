#include <iostream>

using namespace std;

#include <vector>
#include <algorithm>

namespace q01_q03_best_time_to_buy_and_sell_stocks {

    class BestTimeToBuyAndSellStocks1 {
    public:
        int maxProfit(const vector<int> &prices) {
            if (prices.empty()) {
                return -1;
            }
            int retval = 0;
            int minval = INT32_MAX;
            for (int i = 1; i < prices.size(); i++) {
                minval = min(minval, prices[i]);
                retval = max(0, prices[i] - minval);
            }
            return retval;
        }
    };

    class BestTimeToBuyAndSellStocks2 {
    public:
        int maxProfit(const vector<int> &prices) {
            if (prices.empty()) {
                return -1;
            }
            int retval = 0;
            for (int i = 1; i < prices.size(); i++) {
                retval += max(0, prices.at(i) - prices.at((int64_t) i - 1));
            }
            return retval;
        }
    };

    class BestTimeToBuyAndSellStockFllow {
    public:

        static int maxProfit(const vector<int> &prices, int k) {

            if (prices.empty()) {
                return -1;
            }
            size_t N = prices.size();
            if (k > N / 2) {
                //相当于不限制交易次数的
                return maxProfit(prices);
            }
            vector<int> dp(N, 0);  //压缩， 只用到上一行dp  一维表
            int retval = 0;

            //纵向是交易次数，横向是prices[i]
            for (int j = 1; j <= k; j++) {
                int pre = dp[0];
                int best = pre - prices[0];
                for (int i = 1; i < N; i++) {
                    pre = dp[i];
                    dp[i] = max(dp[(int64_t) i - 1], prices[i] + best);
                    best = max(best, pre - prices[i]);
                    retval = max(dp[i], retval);
                }
            }
            return retval;
        }

        static int maxProfit(const vector<int> &prices) {
            if (prices.empty()) {
                return -1;
            }
            int retval = 0;
            for (int i = 1; i < prices.size(); i++) {
                retval += max(0, prices.at(i) - prices.at((int64_t) i - 1));
            }
            return retval;
        }

        static int maxProfit2(const vector<int> &prices, int k) {
            if (prices.empty()) {
                return -1;
            }
            int len = prices.size();
            if (k > len / 2) {
                return maxProfit(prices);
            }
            vector<vector<int>> dp(prices.size(), vector<int>(k + 1, 0));
            for (int i = 1; i < len; i++) {
                for (int j = 1; j <= k; j++) {
                    int pre = dp[i - 1][j];


                    for (int k = 0; i - k >= 0; k++) {
                        pre = max(pre, dp[i - k][j - 1] - prices[i - k] + prices[i]);
                    }
                    dp[i][j] = pre;
                }
            }
            return dp.back().back();
        }
    };

    void play() {
        vector<int> prices{1, 2, 3, 4, 3, 2, 3, 2, 3, 8, 7, 4, 3, 9};
        cout << BestTimeToBuyAndSellStockFllow::maxProfit(prices, 5) << endl;
        cout << BestTimeToBuyAndSellStockFllow::maxProfit2(prices, 5) << endl;
        cout << "hello" << endl;
    }
}

#include <vector>

namespace q04_distinct_sequence {
    class DistinctSequence {
    public:
        static int numDistinct1(const string &s, const string &t) {
            if (s.empty() || t.empty()) { return 0; }
            return process(s, t, s.size(), t.size());

        }

    private:
        static int process(const string &s, const string &t, int i, int j) {
            if (j == 0) {
                return 1;
            }
            if (i == 0) {
                return 0;
            }
            int res = process(s, t, i - 1, j);
            if (s[i] == t[j]) {
                res += process(s, t, i - 1, j - 1);
            }
            return res;
        }

    public:
        //分析可能性
        //dp[i][j]  s[0~i]部分的子序列是否与  t[0~j]的子串相等
        //exclude s[i]   ->  dp[i-1][j]
        //include s[i]   ->  if(s[i]==t[j]){ dp[i-1][j-1]}
        //sum of two possibilities.
        static int numDistinct2(const string &s, const string &t) {
            if (s.empty() || t.empty()) {
                return 0;
            }

            vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));

            for (int i = 0; i < dp.size(); i++) {
                dp[i][0] = 1;
            }

            for (int i = 1; i < dp.size(); i++) {
                for (int j = 1; j < dp.front().size(); j++) {
                    dp[i][j] = dp[i - 1][j] + (s[i] == t[j] ? dp[i - 1][j - 1] : 0);
                }
            }
            return dp.back().back();
        }

        static int numDistinct3(const string &s, const string &t) {
            if (s.empty() || t.empty()) {
                return 0;
            }
            vector<int> dp(t.size() + 1, 0);
            dp[0] = 1;

            for (int i = 1; i <= s.size(); i++) {
                for (int j = 1; j <= t.size(); j++) {
                    //空间压缩
                    dp[j] = dp[j] + (s[i] == t[j] ? dp[j - 1] : 0);
                }
            }
            return dp.back();
        }

    };

    void play() {
        cout << DistinctSequence::numDistinct1("fuccck", "fuck") << endl;
        cout << DistinctSequence::numDistinct2("fuccck", "fuck") << endl;
        cout << DistinctSequence::numDistinct3("fuccck", "fuck") << endl;
    }
}

#include <vector>

namespace q05_expression_add_operators {
    class ExpressionAddOperators {
    public:
        static int ways(const string &num, int target) {
            if (num.empty()) {
                return 0;
            }
            int cur = num[0] - '0';
            return process1(num, target, 0, cur, 1);
        }

        static int process1(
                const string &num,
                int target,
                int left,
                int cur,
                int index) {

            if (index == num.size()) {
                return target == left + cur ? 1 : 0;
            }

            int n = num[index] - '0';
            int ways = 0;
            //+
            ways += process1(num, target, left + cur, n, index + 1);
            //-
            ways += process1(num, target, left + cur, -n, index + 1);
            //*
            ways += process1(num, target, left, cur * n, index + 1);
            //connect
            if (cur < 0) {
                ways += process1(num, target, left, cur * 10 + n, index + 1);
            } else if (cur > 0) {
                ways += process1(num, target, left, cur * 10 - n, index + 1);
            }
            return ways;
        }

        static vector<string> ways2(const string &num, int target) {

            if (num.empty()) {
                return {};
            }

            vector<string> ret;
            string path(num.size() * 2 - 1, '0');
            long n = 0;
            for (int i = 0; i < num.size(); i++) {
                n = n * 10 + num[i] - '0';
                path[i] = num[i];
                process2(num, target, 0, n, i + 1, ret, path, i + 1);
                if (n == 0) {
                    break;
                }
            }
            return ret;
        }

        static void process2(
                const string &num,
                int target,
                int left,
                int cur,
                int index,
                vector<string> &res,
                string &path,
                int len) {

            if (index == num.size()) {
                if (left + cur == target) {
                    res.push_back(path);
                }
                return;
            }

            //index< num.size()
            long n = 0;
            int j = len + 1;
            for (int i = index; i < num.size(); i++) {
                n = n * 10 + num[i] - '0';
                path[j++] = num[i];
                path[len] = '+';
                process2(num, target, left + cur, n, i + 1, res, path, j);
                path[len] = '-';
                process2(num, target, left + cur, -n, i + 1, res, path, j);
                path[len] = '*';
                process2(num, target, left, cur * n, i + 1, res, path, j);
                if (num[index] == 0) {
                    break;
                }
            }
        }

    };

    void play() {
        cout << "expression add operators\n";

        string num = "123";
        int target = 6;
        auto ways1 = ExpressionAddOperators::ways(num, target);
        auto ways2 = ExpressionAddOperators::ways2(num, target);
        cout << endl;

    }
}


int main() {
    //q01_q03_best_time_to_buy_and_sell_stocks::play();
    //q04_distinct_sequence::play();
    //day05_q04_word_serach::play();
    q05_expression_add_operators::play();
}

