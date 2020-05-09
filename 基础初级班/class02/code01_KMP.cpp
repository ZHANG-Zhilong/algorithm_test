#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <typeinfo>

using namespace std;

//get str's prefix and suffix info array.
vector<int> getNextArray(string str) {   //O(M)  i, i-cn  
    //math ralation: next[i-1] = cn,
    //cn is (pos i-1)'s prefix's end's next pos.
    //next: a  b  c  d  .  .  .  a  b  c  d  .  .  .  ..
    //                 cn             i-1 i i+1
    vector<int> next;
    if (str.empty()) {
        return next;
    }
    if (str.size() == 1) {
        next.push_back(-1);
        return next;
    }
    next.resize(str.size());
    next[0] = -1;
    next[1] = 0;
    size_t cn = 0;
    size_t i = 2;
    while (i < str.size()) {
        if (str[i - 1] == str[cn]) {
            next[i++] = ++cn;
        } else if (cn > 0) {
            cn = next[cn];
        } else {
            next[i++] = 0;
        }
    }
    return next;
}


int getIndexOf(const string &s, const string &m) {
    if (m.empty() || s.empty() || s.size() < m.size() || m.size() < 1) {
        return -1;
    }
    vector<int> next = getNextArray(m);
    int i1 = 0, i2 = 0;
    while (i1 < s.size() && i2 < m.size()) {
        if (s[i1] == m[i2]) {
            i1++;
            i2++;
        } else if (next[i2] == -1) {
            i1++;
        } else {
            i2 = next[i2];
        }
    }
    return i2 == m.size() ? i1 - i2 : -1;
}

int main() {
    string s = "fuckufuckuuuuuuuu";
    string m = "kuu";
    int index = getIndexOf(s, m);
    cout << s << endl << m << endl << index;
    system("pause");
    return 0;
}
