#include <iostream>
#include <random>
#include <stack>
#include <unordered_map>
#include <typeinfo>

using namespace std;

class TrieNode {
public:
    int pass;
    int end;
    TrieNode *map[26];
    //unordered_map<char, TrieNode> next;
public:
    TrieNode() {
        pass = 0;
        end = 0;
        for (int i = 0; i < 26; i++) {
            map[i] = nullptr;
        }
    }
    //unordered_map<char, TrieNode> nexts;
};

class Trie {
private:
    TrieNode *_root;
public:
    Trie() {
        _root = new TrieNode();
    }

    int insert(string str);

    int pop(string str);

    int serach(string str);

    int prefixSerach(string str);
};

int Trie::insert(string str) {
    if (str.empty()) {
        return -1;
    }
    TrieNode *node = this->_root;
    int index = 0;
    for (int i = 0; i < str.size(); i++) {
        index = str[i] - 'a';
        if (node->map[index] == nullptr) {
            node->map[index] = new TrieNode();
        }
        node = node->map[index];
        (node->pass)++;
    }
    node->end++;
}

int Trie::pop(string str) {
    if (str.empty()) {
        cout << "pop null string." << endl;
        return -1;
    }
    TrieNode *node = _root;
    int index = 0;
    if (this->serach(str)) {
        for (int i = 0; i < str.size(); i++) {
            index = str[i] - 'a';
            if ((node->pass--) == 1) {
                node = nullptr;
                return 0;
            }
            node = node->map[index];
        }
        node->end--;
    }

}

int Trie::serach(string str) {
    if (str.empty()) {
        cout << "pop null string." << endl;
        return -1;
    }
    int index = 0;
    TrieNode *node = _root;
    for (int i = 0; i < str.size(); i++) {
        index = str[i] - 'a';
        if (node->map[index] == nullptr) {
            return -1;
        }
        node = node->map[index];
    }
    return node->end;

}

int Trie::prefixSerach(string str) {
    if (str.empty()) {
        return 0;
    }
    TrieNode *node = _root;
    int index = 0;
    for (int i = 0; i < str.size(); i++) {
        index = str[i] - 'a';
        if (node->map[index] == nullptr) {
            return 0;
        }
        node = node->map[index];
    }
    return node->pass;
}

int main() {
    string str = "fuck";
    Trie trie;
    trie.insert(str);
    trie.insert(str);
    cout << trie.serach(str);
    trie.pop(str);
    string str2 = "f";
    cout << trie.prefixSerach(str2);
    system("pause");
}