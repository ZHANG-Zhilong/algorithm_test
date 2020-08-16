#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Node {
public:
    int value;
    Node *left;
    Node *right;

    Node(int data = 0) {
        value = data;
        left = nullptr;
        right = nullptr;
    }
};

class Morris {

public:

    void morrisPre(const Node &head) {
        if (&head == nullptr) {
            return;
        }
        Node *cur1 = new Node();
        Node *cur2 = new Node();
        *cur1 = head;
        while (cur1 != nullptr) {
            cur2 = cur1->left;
            if (cur2 != nullptr) {
                while (cur2->right != nullptr && cur2->right != cur1) {
                    cur2 = cur2->right;
                }
                if (cur2->right == nullptr) {
                    cur2->right = cur1;
                    cout << cur1->value << " ";
                    cur1 = cur1->left;
                    continue;
                } else {
                    cur2->right = nullptr;
                }
            } else {
                cout << cur1->value << " ";
            }
            //第一次来到该节点有两种情况：
            //1、该节点左子树最右孩子为空
            //2、该节点左孩子为空，也就是没有左子树
            cur1 = cur1->right;
        }
    }

    void morrisIn(const Node &head) {
        if (&head == nullptr) {
            return;
        }
        Node *cur1 = new Node();
        Node *cur2 = new Node();
        *cur1 = head;
        while (cur1 != nullptr) {
            cur2 = cur1->left;
            if (cur2 != nullptr) {
                while (cur2->right != nullptr && cur2->right != cur1) {
                    cur2 = cur2->right;
                }
                if (cur2->right == nullptr) {
                    cur2->right = cur1;
                    cur1 = cur1->left;
                    continue;
                } else {
                    cur2->right = nullptr;
                }
            }
            //中序遍历是第二次来到该节点时打印该节点
            //cur1向右移动的前提是左子树为空或者左子树都遍历完了,而且以后再也不回到左子树
            cout << cur1->value << " ";
            cur1 = cur1->right;
        }
    }

    void morrisPost(Node &head) {
        if (&head == nullptr) {
            return;
        }
        Node *cur1 = new Node();
        Node *cur2 = new Node();
        *cur1 = head;
        while (cur1 != nullptr) {
            cur2 = cur1->left;
            if (cur2 != nullptr) {
                while (cur2->right != nullptr && cur2->right != cur1) {
                    cur2 = cur2->right;
                }
                if (cur2->right == nullptr) {
                    cur2->right = cur1;
                    cur1 = cur1->left;
                    continue;
                } else {
                    cur2->right = nullptr;
                    printEdge(*cur1->left);
                }
            }
            cur1 = cur1->right;
        }
        printEdge(head);
    }

    void printEdge(Node &head) {
        Node *tail = new Node();
        *tail = reverseEdge(head);
        Node *cur = tail;
        while (cur != nullptr) {
            cout << cur->value << " ";
            cur = cur->right;
        }
        head = reverseEdge(*tail);
    }

    Node reverseEdge(Node &head) {
        Node *pre = nullptr;
        Node *from = new Node();
        Node *next = new Node();
        *from = head;
        while (from != nullptr) {
            next = from->right;
            from->right = pre;
            pre = from;
            from = next;
        }
        return *pre;
    }
};

int main() {
    Node *head = new Node(4);
    head->left = new Node(2);
    head->right = new Node(6);
    head->left->left = new Node(1);
    head->left->right = new Node(3);
    head->right->left = new Node(5);
    head->right->right = new Node(7);

    Morris morris;
    morris.morrisPre(*head);
    cout << endl;
    morris.morrisIn(*head);
    cout << endl;
    morris.morrisPost(*head);

    system("pause");
    return 0;
}
