#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <typeinfo>
#include <string>
#include <cstdlib>

using namespace std;

class BitNode {
public:
    int value;
    BitNode *left;
    BitNode *right;

    BitNode(int value = 0) {
        this->value = value;
        left = (BitNode *) nullptr;
        right = (BitNode *) nullptr;
    }
};


void traverseBinaryTree(const BitNode &head, string &str) {
    if (&head == nullptr) {
        str += "#_";
        return;
    }
    str += to_string(head.value) + "_";
    traverseBinaryTree(*head.left, str);
    traverseBinaryTree(*head.right, str);
}

BitNode generateBitTree(const string &s) {
    BitNode *head = (BitNode *) nullptr;
    if (s.empty()) {
        return *head;
    }
    head = new BitNode(0);
    string buf = "";
    int i = 0;
    while (i < s.size()) {
        if (s[i] != '_') {
            buf += s[i];
        } else if (s[i] == '_') {
        }
    }
    return *head;
}

int main() {

    BitNode head(1);
    head.left = new BitNode(12);
    head.right = new BitNode(3);

    string str = "";
    traverseBinaryTree(head, str);
    cout << str;

    system("pause");
    return 0;
}
