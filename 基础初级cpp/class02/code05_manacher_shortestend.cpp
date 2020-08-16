#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <typeinfo>
#include <string>
#include <cstdlib>

using namespace std;

class Manacher {
public:
    //预处理主字符串
    string manacherString(const string &s) const {
        string rst(s.size() * 2 + 1, 0);
        int i = 0, j = 0;
        while (i < rst.size()) {
            if ((i & 1) == 0) {
                rst[i++] = '#';
            } else {
                rst[i++] = s[j++];
            }
        }
        return rst;
    }

public:

    string shortestEnd(const string &str) {
        if (str.empty()) {
            return "";
        }
        string str2 = this->manacherString(str);
        vector<int> parr(str2.size(), 0);
        int pr = -1, center = -1, max = INT_MIN;
        int reversePos = -1;
        for (int i = 0; i < str2.size(); i++) {
            parr[i] = i < pr ? min(parr[2 * center - i], pr - i) : 1;
            while (i + parr[i] < str2.size() && i - parr[i] > -1) {
                if (str2[i + parr.at(i)] == str2.at(i - parr.at(i))) {
                    parr.at(i)++;
                } else {
                    break;
                }
            }
            if (i + parr.at(i) > pr) {
                pr = i + parr.at(i);
                center = i;
            }
            if (pr = str2.size()) {
                reversePos = parr[i];
                break;
            }
        }

        str2 = str;
        for (int i = str2.size() - 1 - reversePos; i > -1; i--) {
            str2 += str2[i];
        }
        return str2;
    }

};

int main() {

    //查找字符串中最大回文子串长度，manacher算法
    Manacher manacher;
    string str1 = "abc1234321ab";;
    cout << manacher.manacherString(str1);
    string str2 = manacher.shortestEnd(str1);
    cout << str1 << endl << str2 << endl;
    system("pause");
    return 0;
}
