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
private:
    //预处理主字符串
    string manacherString(const string &s) const {
        string m(2 * s.size() + 1, 0);
        size_t j = 0;
        for (size_t i = 0; i < m.size(); i++) {
            m[i] = (i & 1) == 0 ? '#' : s[j++];
        }
        return m;
    }

public:

    int maxLcpsLength(const string &str) {
        if (str.empty()) {
            return 0;
        }
        if (str.size() == 1) {
            return 1;
        }
        string charArr = manacherString(str);
        int pr = -1;
        int center = -1;
        int maxr = INT_MIN;
        vector<int> parr(charArr.size(), 0);
        for (int i = 0; i < charArr.size(); i++) {
            parr[i] = i < pr ? min(parr.at(2 * center - i), pr - i) : 1;//处理manacher算法中，i<LR时候的两种情况
            while (i + parr[i] < charArr.size() && i - parr[i] > -1) {
                if (charArr[i + parr[i]] == charArr[i - parr[i]]) {  //暴力拓展
                    parr[i]++;
                } else {
                    break;
                }
            }
            if (i + parr[i] > pr) { //更新最右回文半径和回文中心
                pr = i + parr[i];
                center = i;
            }
            maxr = max(maxr, parr[i]);
        }
        return maxr - 1;
        //核心时，PR始终大于等于i-1的位置，是一个右边界不可以小于i-1的最大回文窗口
        //利用回文中心和最右回文边界来标记该窗口
        //充分利用最大的，符合条件的会问字串（窗口）快进
    }


};

int main() {

    //查找字符串中最大回文子串长度，manacher算法
    Manacher manacher;
    string str1 = "abc1234321ab";;
    int i = manacher.maxLcpsLength(str1);
    cout << str1 << endl << i << endl;
    system("pause");
    return 0;
}
