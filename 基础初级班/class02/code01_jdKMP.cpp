#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <typeinfo>

using namespace std;

int getNextLast(const string &s) {
    vector<int> next;
    if (s.empty()) {
        return -1;
    } else if (s.size() == 1) {
        next.push_back(-1);
        return -1;
    }
    next.resize(s.size() + 1);
    next.at(0) = -1;
    next.at(1) = 0;
    int i = 2;
    int cn = 0;
    int rst = 0;
    while (i < s.size() + 1) {
        if (s[i - 1] == s[cn]) {
            next[i++] = ++cn;
        } else if (cn > 0) {
            cn = next[cn];
        } else {
            next[i++] = 0;
        }
    }
    return next.at(next.size() - 1);
}

string getMinLen(const string &s) {
    if (s.empty()) {
        return "";
    }
    int index = getNextLast(s);
    string rst = s;
    while (index < s.size()) {
        rst += s[index++];
    }
    return rst;
}

int main() {
    string s = "11";
    string m = "";
    m = getMinLen(s);
    cout << "m is:\n" << m << endl;
    system("pause");
    return 0;
}
