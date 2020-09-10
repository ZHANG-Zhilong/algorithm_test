#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <typeinfo>

using namespace std;

class LowestLexicography {
private:
    struct SortStr {
        bool operator()(const string &a, const string &b) const {
            return a + b < b + a;
        }
    } SortStr;

public:
    string lowestString(vector<string> str) {
        if (&str == nullptr || str.empty());
        sort(str.begin(), str.end(), SortStr);
        string rst = "";
        for (string s : str) {
            rst += s;
        }
        return rst;
    }
};

int main() {
    vector<string> strarr = {"jibw", "ji", "jp", "bw", "jibw"};
    vector<string> strarr2 = {"ba", "b"};
    LowestLexicography llg;
    cout << llg.lowestString(strarr2) << endl;
    cout << llg.lowestString(strarr) << endl;

    system("pause");
    return 0;
}