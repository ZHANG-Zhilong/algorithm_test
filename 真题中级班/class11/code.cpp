#include <iostream>

using namespace std;

#include <string>
#include <vector>
//namespace q00_kmp{}
namespace q01_shortest_have_twice {

    class KMP {
    public:
        int getIndexOf(const string &str1, const string &str2) {
            if (str1.empty() || str2.empty() || str2.size() > str1.size()) {
                return -1;
            }

            int i1 = 0, i2 = 0;
            vector<int> next = getNextArray(str2);

            while (i1 < str1.size() && i2 < str2.size()) {
                if (str1[i1] == str2[i2]) {
                    i1++;
                    i2++;
                } else if (next[i2] > -1) {
                    i2 = next[i2];
                } else {
                    i1++;
                }
            }
            return i2 == str2.size() ? i1 - i2 : -1;
        }

    private:
        vector<int> getNextArray(const string &str2) {
            //next[0] = -1;
            //next[1] = 0;
            if (str2.size() <= 1) {
                return {-1};
            }

            vector<int> next(str2.size(), 0);
            next[0] = -1;
            next[1] = 0;
            int i = 2;
            int cn = 0;  // jump to position.

            while (i < next.size()) {
                if (str2[i - 1] == str2[cn]) {
                    next[i++] = ++cn;
                } else if (cn > 0) {
                    cn = next[cn];  //前一个字符的最长前缀结束的下一个字符
                } else {
                    next[i++] = 0;
                }
            }
            return next;
        }
    };

    class ShortestHaveTwice {
    public:
        string answer(string str1) {

            if (str1.size() < 1) {
                return "";
            }

            int maxPrefix = getNextArray(str1);

            int len = str1.size();
            for (int i = maxPrefix; i < len; i++) {
                str1.push_back(str1.at(i));
            }
            return str1;
        }

    private:
        int getNextArray(const string &str2) {

            if (str2.size() < 2) {
                return {-1};
            }

            vector<int> next(str2.size() + 1, 0);
            next.at(0) = -1;
            next.at(1) = 0;
            int cn = 0;
            int cur = 2;

            while (cur < next.size()) {
                if (str2[cur - 1] == str2[cn]) {
                    next[cur++] = ++cn;
                } else if (cn > 0) {
                    cn = next[cn];
                } else {
                    next[cur++] = 0;
                }
            }
            return next[next.size() - 1];
        }

    };

    void play() {
        string str1 = "itigerfu";
        string str2 = "tigerfu";
        KMP kmp;
        cout << kmp.getIndexOf(str1, str2) << endl;
        ShortestHaveTwice sht;
        cout << sht.answer(str2) << endl;
    }
}

#include <vector>
#include <memory>

namespace q02_t1subtree_equals_t2 {

    class BitNode {
    public:
        int value;
        shared_ptr<BitNode> left;
        shared_ptr<BitNode> right;

        BitNode(int value) {
            this->value = value;
        }
    };

    class T1SubTreeEqualsT2 {

    private:
        void preOrder(shared_ptr<BitNode> root, vector<int> &arr) {
            if (root == nullptr) {
                arr.push_back(INT32_MIN);
                return;
            }
            arr.push_back(root->value);
            preOrder(root->left, arr);
            preOrder(root->right, arr);
        }

        bool isContain(const vector<int> &arr1, const vector<int> &arr2) {

            if (arr2.size() > arr1.size() || arr1.size() < 1 || arr2.size() < 1) {
                return false;
            }

            int i1 = 0, i2 = 0;
            vector<int> next = getNexts(arr2);


            while (i1 < arr1.size() && i2 < arr2.size()) {
                if (arr1.at(i1) == arr2.at(i2)) {
                    i1++;
                    i2++;
                } else if (next[i2] > 0) {
                    i2 = next[i2];
                } else {
                    i1++;
                }
            }
            if (i2 == arr2.size()) {
                return true;
            }
            return false;
        }

        vector<int> getNexts(const vector<int> &arr2) {
            if (arr2.size() < 2) {
                return {-1};
            }

            vector<int> next(arr2.size(), 0);
            next.at(0) = -1;
            next.at(1) = 0;
            int i = 2;
            int cn = 0;

            while (i < next.size()) {
                if (arr2.at(i - 1) == arr2.at(cn)) {
                    next[i++] = ++cn;
                } else if (cn > 0) {
                    cn = next[cn];
                } else {
                    next[i++] = 0;
                }
            }
            return next;
        }

    public:
        void print(shared_ptr<BitNode> root) {
            vector<int> arr;
            preOrder(root, arr);
            for (auto n : arr) {
                cout << n << " ";
            }
            cout << endl;
        }

        void isSubTree(shared_ptr<BitNode> root, shared_ptr<BitNode> root2) {
            vector<int> arr1;
            vector<int> arr2;
            preOrder(root, arr1);
            preOrder(root2, arr2);
            if (isContain(arr1, arr2)) {
                cout << "root contains root2" << endl;
            } else {
                cout << "not Contaions" << endl;
            }

            print(root);
            print(root2);
        }

    };


    void play() {
        cout << "Welcome to T1SubTreeEqualsT2\n";

        shared_ptr<BitNode> root = make_shared<BitNode>(BitNode(1));
        root->left = make_shared<BitNode>(BitNode(2));
        root->right = make_shared<BitNode>(BitNode(3));
        root->left->left = make_shared<BitNode>(BitNode(4));
        root->left->right = make_shared<BitNode>(BitNode(5));

        shared_ptr<BitNode> subRoot = make_shared<BitNode>(BitNode(2));
        subRoot->left = make_shared<BitNode>(BitNode(4));
        subRoot->right = make_shared<BitNode>(BitNode(5));

        T1SubTreeEqualsT2 tse;
        tse.isSubTree(root, subRoot);

    }
}


namespace q03_one_number {
    class OneNumber {
    public:
        static int solution1(int num) {
            if (num < 1) {
                return 0;
            }
            int count = 0;
            for (int i = 0; i < num + 1; i++) {
                count += get1Nums(i);
            }
            return count;
        }

        static int get1Nums(int num) {
            int retval = 0;
            while (num != 0) {
                if (num % 10 == 1) {
                    retval++;
                }
                num /= 10;
            }
            return retval;
        }

        static int solution2(int num) {
            if (num < 1) {
                return 0;
            }
            int len = getLenOfNum(num);
            if (len == 1) {
                return 1;
            }
            int temp1 = pow(10, len - 1);
            int first = num / temp1;
            int firstOneNum = first == 1 ? num % temp1 + 1 : temp1;
            int otherOneNum = first * (len - 1) * (temp1 / 10);
            return firstOneNum + otherOneNum + solution2(num % temp1);
        }

        static int getLenOfNum(int num) {
            int len = 0;
            while (num != 0) {
                len++;
                num /= 10;
            }
            return len;
        }

    };

    void play() {
        cout << OneNumber::solution1(799) << endl;
        cout << OneNumber::solution2(799) << endl;
    }
}


#include <vector>
#include <random>
#include <algorithm>

namespace q04_monster_problem {
    // d[i] i号怪兽的武力
    // p[i] i号怪兽要求的钱
    // hp   当前你具有的能力
    // index 来到了第index个怪兽面前

    // 目前你的能力是hp，你来到了index号怪兽的面前，如果要通过后续所有的怪兽
    //请返回你需要花费的最少钱数
    class MonsterProblem {
    private:
        long process1(const vector<int> &ability, const vector<int> &money, int hp, int index) {
            if (ability.size() < 1 || money.size() < 1 || ability.size() != money.size()) {
                return -1;
            }
            if ((size_t) index == ability.size()) {
                return 0;
            }

            long rst = 0;
            if (hp < ability.at(index)) {
                //must bribe
                rst = money.at(index) + process1(ability, money, hp + ability.at(index), index + 1);
            } else {
                rst = process1(ability, money, hp, index + 1);
                long rst2 = money.at(index) + process1(ability, money, hp + ability.at(index), index + 1);
                rst = min(rst, rst2);
            }
            return rst;
        }

    public:
        long func1(const vector<int> &ability, const vector<int> &money) {
            return process1(ability, money, 0, 0);
        }

        long func2(const vector<int> &ability, const vector<int> &money) {
            //abilityty and money is positiove array
            long sumAbility = 0;
            for (auto n : ability) {
                sumAbility += n;
            }

            size_t n = ability.size();
            vector<vector<long>> dp(n, vector<long>((size_t) sumAbility + 1, -1));

            dp[0][ability.at(0)] = money.at(0);  //first row
            //first column default -1

            for (size_t i = 1; i < dp.size(); i++) {

                for (size_t j = 1; j < dp[0].size(); j++) {

                    if (j < (size_t) ability.at(i)) {

                        //dp[i][j]=-1;

                    } else {   //j>=ability[i]

                        long p1 = dp[i - 1][j];
                        long p2 = -1;

                        if (dp[i - 1][j - ability.at(i)] != -1) {
                            p2 = money.at(i) + dp[i - 1][j - ability.at(i)];
                            // in this case j>ability.at(i);
                        }
                        dp[i][j] = (p1 == -1 || p2 == -1) ? (p1 == -1 ? p2 : p1) : min(p1, p2);
                    }
                }
            }

            for (size_t i = 0; i < dp[0].size(); i++) {
                if (dp[(size_t) n - 1][i] != -1) {
                    return dp[(size_t) n - 1][i];
                }
            }
            return -1;
        }

        long func3(const vector<int> &ability, const vector<int> &money) {

            if (ability.size() < 1 || money.size() < 1 || ability.size() != money.size()) {
                return -1;
            }

            size_t m = ability.size();

            unsigned int sumMoney = 0;
            for (auto n : money) sumMoney += n;

            vector<vector<long>> dp(m, vector<long>((size_t) sumMoney + 1, -1));
            dp[0][money[0]] = ability[0];
            // first column default is -1

            for (int i = 1; i < dp.size(); i++) {
                for (int j = 1; j < dp[0].size(); j++) {

                    long p1 = -1;
                    if (dp[(size_t) i - 1][j] != -1 && dp[(size_t) i - 1][j] > ability[i]) {
                        p1 = dp[(size_t) i - 1][j];
                    }

                    long p2 = -1;
                    if (j - money[i] >= 0 && dp[(size_t) i - 1][(size_t) j - money[i]] != -1) {
                        p2 = dp[(size_t) i - 1][(size_t) j - money[i]] + ability[i];
                    }

                    dp[i][j] = max(p1, p2);
                }
            }

            long retval = -1;
            for (int i = 0; i < dp[0].size(); i++) {
                if (dp[(size_t) m - 1][i] != -1) {
                    retval = i;
                    break;
                }
            }
            return retval;
        }
    };

    void play() {

        cout << "welcome to monster world" << endl;

        vector<int> ability{1, 2, 100, 5};
        vector<int> money{1, 3, 2, 100};

        MonsterProblem mp;

        cout << "func1 rst:" << endl;
        cout << mp.func1(ability, money) << endl;

        cout << "func2 rst:" << endl;
        cout << mp.func2(ability, money) << endl;

        cout << "func3 rst:" << endl;
        cout << mp.func3(ability, money) << endl;
    }
}


#include <vector>
#include <unordered_set>
#include <algorithm>

namespace q05_longest_integrated_length {

    //最长可整合子数组
    class LongestIntegratedLength {

    public:

        int longestIntegratedLength(const vector<int> &arr) {

            if (arr.size() < 1) {
                return -1;
            }

            int maxlen = INT32_MIN;
            unordered_set<int> checkRepeat;
            int maxv = INT32_MIN, minv = INT32_MAX;

            for (int start = 0; start < arr.size(); start++) {  // L boundary

                checkRepeat.clear();

                for (int end = start; end < arr.size(); end++) {  // R right boundary.

                    //check  subarray  L ... R
                    if (checkRepeat.count(arr.at(end)) != 0) {
                        break;  // 有重复值，重新换开头子数组
                    } else {
                        checkRepeat.insert(arr.at(end));
                        maxv = max(maxv, arr.at(end));
                        minv = min(minv, arr.at(end));
                        if (maxv - minv == end - start) {  //L ... R 是可整合的
                            maxlen = maxlen > (end - start + 1) ? maxlen : (end - start + 1);
                        }
                    }
                }
            }
            return maxlen;
        }


    };

    void play() {
        vector<int> t = {5, 5, 3, 2, 6, 4, 3};
        LongestIntegratedLength lil;
        cout << lil.longestIntegratedLength(t) << endl;

    }

}

namespace q06_palindrome_shortest_end {

    class Manacher {

    public:
        string manacherString(const string &str) {
            if (str.empty()) {
                return "";
            }
            int len = str.size();
            string ret(len * 2 + 1, '#');
            for (int i = 0; i < len; i++) {
                ret.at(2 * i + 1) = str.at(i);
            }
            return ret;
        }

    public:
        int maxLcpsLength(const string &str) {
            if (str.size() < 1) {
                return 0;
            }

            string charArr = this->manacherString(str);
            vector<int> pArr(charArr.size(), 0);
            int index = -1;  //最右回文边界对应的回文中心
            int pR = -1;  //最右回文边界
            int maxv = INT32_MIN;

            for (int i = 0; i < charArr.size(); i++) {
                pArr[i] = i < pR ? min(pArr[2 * index - i], pR - i) : 1;
                while (i + pArr[i] < charArr.size() && i - pArr[i] > -1) {
                    if (charArr[i + pArr[i]] == charArr[i - pArr[i]]) {
                        pArr[i]++;
                    } else {
                        break;
                    }
                }
                if (i + pArr[i] > pR) {
                    pR = i + pArr[i];
                    index = i;
                }
                maxv = max(maxv, pArr[i]);
            }
            return maxv - 1;
        }
    };

    class PalindromeShortestEnd {
    private:
        string manacherStr(const string &str) {
            if (str.empty()) {
                return "";
            }
            int len = str.size();
            string ret(2 * len + 1, '#');
            for (int i = 0; i < str.size(); i++) {
                ret.at(2 * i + 1) = str.at(i);
            }
            return ret;
        }

    public:
        string shortestEnd(const string &str2) {
            if (str2.size() < 1) {
                return "";
            }
            string charArr = this->manacherStr(str2);
            vector<int> pArr(charArr.size());
            int index = -1;
            int pR = -1;
            int maxContainsEnd = 0;

            for (int i = 0; i < charArr.size(); i++) {
                pArr.at(i) = pR > i ? min(pR - i, pArr[2 * index - i]) : 1;
                while (i + pArr.at(i) < pArr.size() && i - pArr.at(i) > -1) {
                    if (charArr.at(i + pArr.at(i)) == charArr.at(i - pArr.at(i))) {
                        pArr.at(i)++;
                    } else {
                        break;
                    }
                }

                if (i + pArr.at(i) > pR) {
                    index = i;
                    pR = i + pArr.at(i);
                }
                if (pR == charArr.size()) {
                    maxContainsEnd = pArr.at(i);
                    break;
                }
            }

            maxContainsEnd /= 2;
            string appendstr(str2.begin(), str2.begin() + maxContainsEnd + 1);
            reverse(appendstr.begin(), appendstr.end());
            return str2 + appendstr;
        }

    };

    void play() {

        cout << "welcome palindrome shortest end." << endl;

        //test manacher
        Manacher m;
        cout << m.maxLcpsLength("fuckuuu") << endl;

        //test palindrome shortest end

        PalindromeShortestEnd pse;
        cout << pse.shortestEnd("fuckuuu");
    }
}

int main(int agrc, char *argv[]) {
    //q01_shortest_have_twice::play();
    //q02_t1subtree_equals_t2::play();
    //q04_monster_problem::play();
    q03_one_number::play();
    //q05_longest_integrated_length::play();
    //q06_palindrome_shortest_end::play();


    return 0;
}


