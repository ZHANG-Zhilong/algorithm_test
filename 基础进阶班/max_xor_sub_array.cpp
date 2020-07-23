#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <queue>
#include<unordered_map>
#include <algorithm>

using namespace std;

int getMaxE2(vector<int> arr) {
    int maxv = INT_MIN;
    vector<int> dp(arr.size(), 0);
    int eor = 0;
    for (int i = 0; i < arr.size(); i++) {
        eor ^= arr[i];
        maxv = max({maxv, eor});
        for (int j = 1; j < i; j++) {
            int curEor = dp[(size_t) j - 1] ^arr[j];
            maxv = max({curEor, maxv});
        }
        dp[i] = eor;
    }
    return maxv;
}

int getMaxEor2(vector<int> arr) {
    if (arr.size() <= 1) {
        return 0;
    }
    int maxv = INT_MIN;
    vector<int> dp(arr.size(), 0);
    int eor = 0;
    for (int i = 1; i < arr.size(); i++) {
        eor ^= arr[i];
        maxv = max({maxv, eor});
        for (int j = 1; j < i; j++) {
            int curEor = arr[j] ^dp[(size_t) j - 1];
            maxv = max(curEor, maxv);
        }
        dp[i] = eor;
    }

}


class NumTrie {
private:
    class Node {
    public:
        vector<Node *> nexts;

        Node() {
            nexts = {nullptr, nullptr};
        }
    };

private:
    Node *head;
public:
    NumTrie() {
        head = new Node();
    }

    void add(int num) {
        Node *cur = head;
        for (int move = 31; move >= 0; move--) {
            int path = ((num >> move) & 1);  //1&1->1, 0&1->0
            cur->nexts[path] = (cur->nexts[path] == nullptr) ? new Node() : cur->nexts[path];
            cur = cur->nexts[path];
        }
    }

    int maxEor(int num) {
        //num->  eor(0~i)
        Node *cur = head;
        int res = 0;
        for (int move = 31; move >= 0; move--) {
            int path = (num >> 31) & 1;  //eor(0~i)
            int best = move == 31 ? path : path ^ 1;  //expected, eor(0~k)
            best = (cur->nexts[best] == nullptr) ? (best ^ 1) : best;  //reality
            res |= (path ^ best) << move;  // path^best-> 0000 0000 0000 0000/0001 (e.g.)
            cur = cur->nexts[best];
        }
        return res;  //eor(0~i)^eor(0~k-1) max -> eor(k~i) max
    }
};

int maxEorSubArray(vector<int> arr) {
    if (arr.empty()) {
        return 0;
    }
    int maxv = INT_MIN;
    int eor = 0;
    NumTrie numTrie;
    numTrie.add(0);
    for (int i = 0; i < arr.size(); i++) {
        eor ^= arr[i];
        maxv = max(maxv, numTrie.maxEor(eor));
        numTrie.add(eor);
    }
    return maxv;
}

int main() {

    system("pause");
    return 0;
}
