#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <queue>
#include<unordered_map>
#include <algorithm>

using namespace std;

class Node {
public:
    int value;
    Node *left;
    Node *right;

    Node(int data) {
        value = data;
        left = nullptr;
        right = nullptr;
    }
};

bool isCBT(Node head) {
    if (&head == nullptr) {
        return true;
    }
    Node *node = &head;
    queue<Node *> que;
    bool leaf = false;
    Node *l = nullptr;
    Node *r = nullptr;
    que.push(&head);
    while (!que.empty()) {
        node = que.front();
        que.pop();
        l = node->left;
        r = node->right;
        if ((l == nullptr && r != nullptr) || leaf && (l != nullptr || r != nullptr)) {
            return false;
        }
        if (l != nullptr) {
            que.push(l);
        }
        if (r != nullptr) {
            que.push(r);
        } else {
            leaf = true;
        }
    }
    return true;

}

int main() {
    Node *head = new Node(1);
    head->left = new Node(2);
    head->right = new Node(3);

    head->left->left = new Node(4);
    head->right->left = new Node(4);
    cout << isCBT(*head);

    system("pause");
    return 0;
}
