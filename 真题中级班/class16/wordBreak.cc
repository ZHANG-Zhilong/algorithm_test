#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <memory>

using namespace std;

class Node {
public:
    int path;
    int end;
    vector<shared_ptr<Node>> nexts;

    Node() {
        path = 0;
        end = 0;
        nexts.resize(26);
    }
};

class WordBreak {
public:
    int wordBreak(const string &str, const vector<string> &arr) {
        unordered_set<string> words;
        for (const auto &s: arr) {
            if (words.find(s) == words.end()) {
                words.insert(s);
            }
        }
        return process1(str, 0, words);
    }

    int process1(const string &str, int index, const unordered_set<string> &words) {
        if (index == str.size()) {
            return 1;
        }
        int ways = 0;
        for (int i = index; i < str.size(); i++) {
            string substr = str.substr(index, i - index + 1);
            if (words.find(substr) != words.end()) {
                //	cout<<"substr: "<<substr<<"\tindex: "<<index<<"\ti: "<<i<<endl;
                ways += process1(str, i + 1, words);
            }
        }
        return ways;
    }

    int dp(const string &str, const vector<string> &arr) {
        unordered_set<string> words;
        for (auto n: arr) {
            if (words.find(n) == words.end()) {
                words.insert(n);
            }
        }
        int n = str.size();
        vector<int> dp(n + 1, 0);
        dp[n] = 1;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                string substr = str.substr(i, j - i + 1);
                if (words.find(substr) != words.end()) {
                    dp[i] += dp[j + 1];
                }
            }
        }
        return dp[0];
    }

    int dp2(const string &str, const vector<string> &arr) {
        if (str.empty() || arr.empty()) {
            return -1;
        }
        shared_ptr<Node> root = make_shared<Node>();
        for (const auto &n : arr) {
            auto node = root;
            int index = 0;
            for (const auto &m: n) {
                index = m - 'a';
                if (node->nexts[index] == NULL) {
                    node->nexts[index] = make_shared<Node>();
                }
                node = node->nexts[index];
                node->path++;
            }
            node->end++;
        }

        const int N = str.size();
        vector<int> dp(N + 1, 0);
        dp.back() = 1;
        for (int i = N - 1; i >= 0; i--) {
            auto node = root;
            int index = 0;
            for (int j = i; j < N; j++) {
                index = str[j] - 'a';
                if (node->nexts[index] == NULL) {
                    break;
                }
                node = node->nexts[index];
                if (node->end > 0) {
                    dp[i] += dp[j + 1];
                }
            }
        }
        return dp[0];
    }
};

void play() {
    string str = "aaaab";
    vector<string> arr = {"a", "aa", "ab"};
    WordBreak wb;
    cout << endl << wb.wordBreak(str, arr) << endl;
    cout << endl << wb.dp(str, arr) << endl;
    cout << endl << wb.dp2(str, arr) << endl;
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
