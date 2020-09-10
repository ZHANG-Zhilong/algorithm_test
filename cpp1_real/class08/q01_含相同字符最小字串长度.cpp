#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

using namespace std;

class IncludeStr2 {
public:
    static int includeStr2(const string &str1, const string &str2) {

        if (str1.empty() || str2.empty()) {
            return -1;
        }

        //边界条件 ++ 或者 -- 后处于什么情况，处于何种位置
        //何时采集答案
        //确定好分支条件
        int l = 0, r = 0, windowLen = str1.size();
        unordered_map<char, int> debtTable;
        int all = str2.size();

        for (const auto &c : str2) {
            debtTable[c]++;
        }

        while (l < str1.size() - str2.size() && r < str1.size()) {
            if (all > 0) {  //往右扩
                char c = str1[r++];
                if (debtTable.find(c) != debtTable.end()) {
                    if (debtTable[c]-- > 0) {
                        all--;
                    }
                }
            } else if (all == 0) {  //左缩小
                windowLen = min(windowLen, r - l);
                char c = str1[l++];
                if (debtTable.find(c) != debtTable.end()) {
                    if (debtTable[c]++ == 0) {
                        all++;
                    }
                }
                //在什么时候收集答案？（收集答案）处理l（收集答案），然后l右移一位。仔细体会边界的变化
//                windowLen = min(windowLen, r-l);  //为何不是r-l+1? 因为 [l,r) not [l, r]
//                l++;
            }
        }
        return windowLen;
    }

    static int includeStr3(const string &str1, const string &str2) {

        if (str1.empty() || str2.empty()) {
            return -1;
        }

        int left = 0, right = 0;
        int all = 0, minLen = str1.size();
        unordered_map<char, int> strMap;

        for (const auto &n: str2) {
            strMap[n]++;
        }

        while (right != str1.size()) {
            strMap[str1[right]]--;
            if (strMap[str1[right]] >= 0) {
                all--;
            }
            if (all == 0) {
                while (strMap[str1[left]] < 0) {
                    strMap[str1[left++]]++;
                }
                minLen = min(minLen, right - left + 1);
                all++;
                strMap[str1[left++]]++;
            }
            right++;
        }
        return minLen == str1.size() ? 0 : minLen;
    }
};

void play() {
    string str2 = "abccaabxxxxx";
    string str1 = "aaaxx";
    cout << IncludeStr2::includeStr2(str2, str1) << endl;
    cout << IncludeStr2::includeStr3(str2, str1);
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
