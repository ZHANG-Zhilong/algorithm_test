#include <iostream>

using namespace std;

#include <memory>
#include <unordered_map>
#include <vector>

namespace q01_receive_and_print_order_line {
    //顺序打印接收的无序信息（网络传递）
    class Node {
    public:
        int id;
        string msg;
        shared_ptr<Node> next;

        Node(int id, string msg) {
            this->id = id;
            this->msg = msg;
            next = nullptr;
        }
    };

    class MessageBox {

    private:
        int waitPoint = 1;
        unordered_map<int, shared_ptr<Node>> head;
        unordered_map<int, shared_ptr<Node>> tail;

    public:
        void receive(vector<Node> &arr) {

            for (int i = 0; i < arr.size(); i++) {  //simulate stream input.

                shared_ptr<Node> node = make_shared<Node>(arr.at(i));

                //建立了从id到id的连续区间
                head[node->id] = node;
                tail[node->id] = node;

                if (tail.count(node->id - 1) != 0) {  //查找以id-1结尾的连续区间
                    tail[node->id - 1]->next = node;
                    tail.erase(node->id - 1);
                    head.erase(node->id);
                }

                if (head.count(node->id + 1) != 0) {  //查找id+1开头的连续区间
                    node->next = head[node->id + 1];
                    head.erase(node->id + 1);
                    tail.erase(node->id);
                }

                if (waitPoint == node->id) {
                    print();
                }
            }
        }

        void print() {
            auto node = head[waitPoint];
            head.erase(node->id);
            while (node != nullptr) {
                cout << node->id << "  " << node->msg << endl;
                waitPoint++;
                node = node->next;
            }
            tail.erase(waitPoint - 1);
        }

    };

    void play() {

        cout << "Welcome to ReceiveAndPrintOrderLine\n";

        Node n1(4, "fuck");
        Node n2(1, "I");
        Node n3(2, "want");
        Node n5(5, "u.");
        Node n4(3, "to");
        vector<Node> t{n1, n2, n3, n4, n5};
        MessageBox rapl;
        rapl.receive(t);


    }
}


#include <memory>

namespace q02_point_in_triangle {

    //利用向量叉乘判断一个点是否在凸多边形外
    class Point {
    public:
        int x = 0;
        int y = 0;

        Point(int x, int y) {
            this->x = x;
            this->y = y;
        }

        Point operator-(const Point &p) const {
            return Point(p.x - this->x, p.y - this->y);
        }

        void swap(Point &point) {
            int tx, ty;
            tx = point.x;
            ty = point.y;
            point.x = this->x;
            point.y = this->y;
            this->x = tx;
            this->y = ty;
        }
    };

    // If return negative value, it means (x1, y1) in (x2,y2) right
    // If return positive value, it means (x1, y1) in (x2,y2) left
    int cross(const Point &p1, const Point &p2) {
        return p1.x * p2.y - p2.x * p1.y;  //x1*y2 - x2*y1
    }


    class PointInTriangle {
    public:
        bool isInside(Point &p1, Point &p2, Point &p3, Point &p) {
            cout << "isInside" << endl;
            if (cross(p2 - p1, p3 - p1) < 0) {
                p2.swap(p3);
            }
            if (cross(p - p1, p2 - p1) < 0 && cross(p - p2, p3 - p2) < 0 && cross(p - p3, p1 - p3) < 0) {
                return true;
            }
            return false;
        }
    };

    void play() {
        Point p1(0, 0);
        Point p2(0, 5);
        Point p3(5, 0);
        Point p(1, 1);
        PointInTriangle pit;
        cout << pit.isInside(p1, p2, p3, p);
    }
}


#include <vector>

namespace q03_money_ways {
    //动态规划，两张表联动
    //兑换钱
    //coins每一个只可以用一次
    //cupoons每一个可以用无限次
    //两种都用，找对应钱数可以有多少种方法
    class MoneyWays {
    public:
        int moneyWays(
                const vector<int> &arbitary,
                const vector<int> &onlyone,
                int money) {

            if (money == 0) {
                return 0;
            }

            if (arbitary.size() < 1 && onlyone.size() < 1) {
                return money == 0 ? 1 : 0;
            }

            //coin数组，和券数组不可能都没有
            vector<vector<int>> dparb = this->getArbi(arbitary, money);
            vector<vector<int>> dpone = this->getDpOne(onlyone, money);

            if (dparb.size() < 1) {
                return dpone[dpone.size() - 1][dpone[0].size() - 1];
            }

            if (dpone.size() < 1) {
                return dparb[dparb.size() - 1][dparb[0].size() - 1];
            }

            int ret = 0;
            for (int i = 0; i < money + 1; i++) {
                ret += dparb[dparb.size() - 1][i] *
                       dpone[dpone.size() - 1][money - i];
            }
            return ret;
        }

        vector<vector<int>> getDpOne(
                const vector<int> arr,
                int money) {

            if (arr.size() < 1) {
                return {};
            }

            vector<vector<int>> dp(arr.size(), vector<int>(money + 1, 0));
            if (arr[0] < dp[0].size()) {
                dp[0][arr[0]] = 1;
            }

            for (int i = 0; i < dp.size(); i++) {
                dp[i][0] = 1;
            }

            for (int i = 1; i < dp.size(); i++) {
                for (int j = 1; j < dp[0].size(); j++) {
                    dp[i][j] = dp[i - 1][j];
                    if (j - arr[i] > -1) {
                        dp[i][j] += dp[i - 1][j - arr[i]];
                    }
                }
            }

            return dp;
        }

        vector<vector<int>> getArbi(
                const vector<int> arr,
                int money) {

            if (arr.size() < 1) {
                return {};
            }

            vector<vector<int>> dp(arr.size(), vector<int>(money + 1, 0));

            for (int i = 0; i < arr.size(); i++) {
                dp[i][0] = 1;
            }

            for (int j = 1; j * arr[0] < money + 1; j++) {
                dp[0][j * arr[0]] = 1;
            }

            for (int i = 1; i < dp.size(); i++) {
                for (int j = 1; j < money + 1; j++) {
                    dp[i][j] = dp[i - 1][j];
                    dp[i][j] += j - arr[i] > 0 ? dp[i][j - arr[i]] : 0;
                }
            }
            return dp;
        }

    };

    void play() {
        MoneyWays mw;
        vector<int> arb{1};
        vector<int> one{1};
        int money = 11;
        cout << mw.moneyWays(arb, one, money);
    }
}

#include <vector>
#include <algorithm>

namespace q04_palindrome_add_min {
    //范围上的尝试模型
    class PalindromeAddMin {
        //一个字符串在任意位置最少添加几个字符使其变为回文字符串
        //方法二：求一个字符串最长回文子序列长度k， rst=N-k；
    public:
        //返回变成回文串后的一种结果
        //把动态规划填好之后，总能够根据状态转移回去
        //类似一个深度优先遍历
        string getPalindrome(const string &str) {
            if (str.size() < 1) {
                return str;
            }
            auto dp = this->getDP(str);
            int len = str.size() + dp[0].back();
            string res(len, '0');
            int i = 0;
            int j = str.size() - 1;
            int resl = 0;
            int resr = res.size() - 1;

            while (i < j) {
                if (str[i] == str[j]) {
                    res[resl++] = str[i++];
                    res[resr++] = str[j--];
                } else if (dp[i][j - 1] < dp[i + 1][j]) {
                    res[resl++] = str[j];
                    res[resr--] = str[j--];
                } else {
                    res[resl++] = str[i];
                    res[resr--] = str[i++];
                }
            }
            return res;
        }


        //返回需要添加的字符个数，两种方法等效
        vector<vector<int>> getdp(const string &str) {
            if (str.size() < 1) {
                return {};
            }
            vector<vector<int>> dp(str.size(), vector<int>(str.size(), 0));
            for (int i = 1; i < str.size(); i++) {
                dp[i - 1][i] = str[i] == str[i - 1] ? 0 : 1;
            }
            for (int i = 2; i < str.size(); i++) {
                int l = 0, r = i;
                while (l < str.size() && r < str.size()) {
                    if (str[l] == str[r]) {
                        dp[l][r] = dp[l + 1][r - 1];  //左下角
                    } else {
                        dp[l][r] = min(dp[l + 1][r], dp[l][r - 1]) + 1;
                    }
                    l++, r++;
                }
            }
            return dp;
        }

        vector<vector<int>> getDP(const string &str) {
            if (str.size() < 1) {
                return {};
            }
            vector<vector<int>> dp(str.size(), vector<int>(str.size(), 0));
            for (int j = 1; j < str.size(); j++) {
                dp[j - 1][j] = str[j - 1] == str[j] ? 0 : 1;
                for (int i = j - 2; i > -1; i--) {
                    if (str[i] == str[j]) {   //process general position
                        dp[i][j] = dp[i + 1][j - 1];
                    } else {
                        dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
                    }
                }
            }
            return dp;
        }
    };


    void play() {
        PalindromeAddMin pam;
        pam.getDP("fuck");
        cout << pam.getPalindrome("fucck");

    }
}

#include <vector>

namespace q04_1_palindrome_string {
    class PalindromeString {
    public:
        //求str1的回文序列，str2是str1的最长回文子序列
        string palindromeString(const string &str1, const string &str2) {
            if (str1.size() < str2.size()) {
                return "error input";
            } else if (str1.size() == str2.size()) {
                return str1;
            }
            if (str2.size() < 1) {
                string str11 = const_cast<string &>(str1);
                char mid = str11.back();
                str11.pop_back();
                string ret = str11;
                reverse(str11.begin(), str11.end());
                return ret + mid + str11;
            }

            int len = str1.size() * 2 - str2.size();
            int l1 = 0, r1 = str1.size() - 1;
            int l2 = 0, r2 = str2.size() - 1;
            string leftpart;

            while (l1 < r1) {

                string left, right;
                while (str1[l1] != str2[l2]) {
                    left.push_back(str1[l1++]);
                }
                while (str1[r1] != str2[r2]) {
                    right.push_back(str1[r1--]);
                }
                char mid = str1[l1];
                leftpart += left + right + mid;
                l1++, r1--;
                l2++, r2--;
            }

            char mid = 0;
            if (l1 == r1) {
                mid = str1[l1];
            } else {
                mid = leftpart.back();
                leftpart.pop_back();
            }
            string rightpart = leftpart;
            reverse(rightpart.begin(), rightpart.end());
            return leftpart + mid + rightpart;
        }
    };

    void play() {
        PalindromeString ps;
        cout << ps.palindromeString("a2b4cdef2gh", "242") << endl;
        cout << ps.palindromeString("abcdefgh", "") << endl;
        cout << ps.palindromeString("12321", "12321") << endl;
        cout << ps.palindromeString("12321", "12321564") << endl;
    }
}

#include <vector>

namespace q04_2_max_common_subsequence {

    //求两个字符串最长公共子序列  dp
    class MaxCommonSubSequence {
        //求两个字符串最长公共子序列问题  //子序列可以不连续，子串必须连续
        //一个样本做行，一个样本做列
        //分类讨论四种情况
        //str1[i], str2[j], str
        //str以str1[i]结尾不，以str2[j]结尾		dp[i][j] = dp[i][j-1]
        //str不以str1[i]结尾，以str2[j]结尾		dp[i][j] = dp[i-1][j]
        //str以str1[i]结尾，也以str2[j]结尾		dp[i][j] =  str1[i]==str2[j]? dp[i-1][j-1]+1:dp[i-1][j-1]
        //str不以str1[i]结尾，也不以str2[j]结尾	dp[i][j] = dp[i-1][j-1]
    public:
        int getMax(
                const string &str1,
                const string &str2) {

            if (str1.size() < 1 || str2.size() < 1) {
                return -1;
            }

            vector<vector<int>> dp(str1.size(), vector<int>(str2.size(), 0));

            for (int i = 0; i < str1.size(); i++) {
                dp[i][0] = str1[i] == str2[0] ? 1 : 0;
            }

            for (int j = 1; j < str2.size(); j++) {
                dp[0][j] = str1[0] == str2[j] ? 1 : 0;
            }

            for (int i = 1; i < str1.size(); i++) {
                for (int j = 1; j < str2.size(); j++) {

                    //三种可能性或者四种可能性
                    if (str1[i] == str2[j]) {
                        dp[i][j] = max({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1] + 1});
                        //dp[i-1][j-1]+1 > dp[i-1][j-1]
                    } else {
                        dp[i][j] = max({dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]});
                    }
                }
            }
            return dp.back().back();
        }
    };

    void play() {
        MaxCommonSubSequence mcss;
        cout << mcss.getMax("fuuuuusxck", "fuuck") << endl;
    }

}

#include <vector>

namespace q04_3_max_palindrome_subsequence {
    class MaxPalindromeSubsequence {
        //求一个字符串的最长回文子序列   vs  字符串最长回文子串
        //str1   str1逆序  求两个字符串最长公共子序列  必是最长回文子序列
    public:
        int maxPalin(const string &str) {
            if (str.size() < 1) {
                return -1;
            }


            return 0;
        }

    };

    void play() {
        MaxPalindromeSubsequence mps;
        cout << mps.maxPalin("fuc123fshs321ck");
    }
}

#include <vector>

namespace q05_print_unique_pari_and_triad {
    //打印有序数组中和为aim的对
    class PrintUniquePair {
    public:

        void printUniquePair(
                const vector<int> &arr,
                int aim) {
            if (arr.size() < 1 || aim <= arr[0]) {
                cout << arr.back();
                return;
            }
            int l = 0, r = arr.size() - 1;
            while (l < r) {
                int sum = arr[l] + arr[r];
                if (sum > aim) {
                    r--;
                } else if (sum < aim) {
                    l++;
                } else {
                    if (l == 0 || arr[l - 1] != arr[l]) {
                        cout << arr[l] << ", " << arr[r] << endl;
                    }
                    //下面两行至少存在一个即可
                    l++;
                    //r--;
                }
            }
        }
    };

    class PrintUniqueTriad {
    public:
        void printUniqueTriad(
                const vector<int> &arr,
                int aim) {

            if (arr.size() < 1 || aim < arr.front()) {
                return;
            }
            for (int i = 0; i < arr.size() - 2; i++) {
                if (i == 0 || arr[i - 1] != arr[i]) {
                    printRest(arr, i, i + 1, arr.size() - 1, aim - arr[i]);
                }
            }
        }

        void printRest(
                const vector<int> &arr,
                int cur,
                int l,
                int r,
                int aim
        ) {

            if (l >= r || cur >= l) {
                return;
            }

            while (l < r) {
                int sum = arr[l] + arr[r];
                if (sum < aim) {
                    l++;
                } else if (sum > aim) {
                    r--;
                } else {
                    if (l == 0 || arr[l - 1] != arr[l]) {
                        cout << arr[cur] << ", " << arr[l] << ", " << arr[r] << endl;
                    }
                    l++;
                }
            }
        }
    };

    void play() {
        PrintUniquePair pup;
        PrintUniqueTriad put;
        vector<int> test1{1, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 5, 5, 6, 7, 8, 9};
        pup.printUniquePair(test1, 10);
        put.printUniqueTriad(test1, 10);
    }
}

int main(int agrc, char *argv[]) {

    //q01_receive_and_print_order_line::play();
    //q02_point_in_triangle::play();
    //q03_money_ways::play();
    //q04_palindrome_add_min::play();
    //q04_1_palindrome_string::play();
    //q04_2_max_common_subsequence::play();
    //q04_3_max_palindrome_subsequence::play();
    q05_print_unique_pari_and_triad::play();
    return 0;
}

