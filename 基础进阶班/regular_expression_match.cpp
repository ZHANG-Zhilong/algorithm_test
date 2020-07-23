#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <queue>
#include<unordered_map>
#include <algorithm>

using namespace std;


class RegularExpressionMatch {
public:

    bool process(string str, string exp, int i, int j) {
        if (j == exp.size()) {
            return i == str.size();
        }

        //  j+1位置没有字符了，或者j+1位置有字符但是不为*  -->j位置有字符，考察j+1位置情况
        if ((size_t) j + 1 == exp.size() && exp[(size_t) j + 1] != '*') {
            return i != str.size() && (str[i] == exp[j] || exp[(size_t) j + 1] == '.')
                   && process(str, exp, i + 1, j + 1);
        }
        //走到这里的大逻辑为，exp的j+1位置有字符并且为*
        while (i != str.size() && (exp[j] == str[i] || exp[j] == '.')) {
            if (process(str, exp, i, j + 2)) {  //尝试每一个可以尝试的后缀
                return true;
            }
            i++;
        }
        //str i位置的字符匹配零次
        return process(str, exp, i, j + 2);
    }

    bool isMatch(string str, string exp) {
        if (str.empty() || exp.empty()) {
            return false;
        }
        if (!isValid(str, exp)) {
            return false;
        }
        vector<vector<bool>> dp = initDPMap(str, exp);
        for (int i = str.size() - 1; i > -1; i--) {
            for (int j = exp.length() - 2; j > -1; j--) {
                if (exp[j + 1] != '*') {
                    dp[i][j] = (str[i] == exp[j] || exp[j] == '.') && dp[i + 1][j + 1];
                } else {
                    int si = i;
                    while (si != str.size() && (str[si] == exp[j] || exp[j] == '.')) {
                        if (dp[si][j + 2]) {
                            dp[i][j] = true;
                            break;
                        }
                        si++;
                    }
                    if (dp[i][j] != true) {
                        dp[i][j] = dp[si][j + 2];
                    }
                }
            }
        }


    }

private:

    vector<vector<bool>> initDPMap(string str, string exp) {
        int slen = str.size();
        int elen = exp.size();
        vector<vector<bool>> dp((size_t) slen + 1, vector<bool>((size_t) elen + 1, false));
        dp.at(slen).at(elen) = true;
        // i row, j column
        for (int j = elen - 2; j > -1; j = j - 2) {
            if (exp[j] != '*' && exp[j + 1] == '*') {
                dp[slen][j] = true;
            } else {
                break;
            }
        }
        if (slen > 0 && elen > 0) {
            if ((exp[elen - 1] == '.' || str[slen - 1] == exp[elen - 1])) {
                dp[slen - 1][elen - 1] == true;
            }
        }
        return dp;

    }

    bool isValid(string s, string e) {
        for (int i = 0; i < s.size(); i++) {
            if (s.at(i) == '.' || s.at(i) == '*') {
                return false;
            }
        }
        for (int i = 0; i < e.size(); i++) {
            if (e.at(i) == '*' && (i == 0 || e.at((size_t) i - 1) == '*')) {
                return false;
            }
        }
        return true;
    }

};

int main() {
    system("pause");
    return 0;
}
