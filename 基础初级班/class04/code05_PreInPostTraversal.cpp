#include <iostream>
#include <random>
#include <vector>
#include <stack>
#include <queue>
#include <typeinfo>

using namespace std;

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;

    Node(int data) : value(data), left(nullptr), right(nullptr) {}
} Node;

static class PreInPostTraversal {
public:
    static void preOrderRecur(Node *head) {
        if (head == nullptr) {
            return;
        }
        cout << head->value << " ";
        preOrderRecur(head->left);
        preOrderRecur(head->right);
    }

    static void inOrderRecur(Node *head) {
        if (head == nullptr) {
            return;
        }
        inOrderRecur(head->left);
        cout << head->value << " ";
        inOrderRecur(head->right);
    }

    static void postOrderRecur(Node *head) {
        if (head == nullptr) {
            return;
        }
        postOrderRecur(head->left);
        postOrderRecur(head->right);
        cout << head->value << " ";
    }

    static void preOrderUnRecur(Node *head) {
        if (head == nullptr) {
            return;
        }
        stack<Node *> help;
        help.push(head);
        while (!help.empty()) {
            head = help.top();
            cout << head->value << " ";
            help.pop();
            if (head->right != nullptr) {
                help.push(head->right);
            }
            if (head->left != nullptr) {
                help.push(head->left);
            }
            //这里的两个if是否可以更换为if-else结构？
        }
    }

    static void inOrderUnRecur(Node *head) {
        if (head != nullptr) {
            stack<Node *> help;
            while (!help.empty() || head != nullptr) {
                if (head != nullptr) {
                    help.push(head);
                    head = head->left;
                } else {
                    head = help.top();
                    help.pop();
                    cout << head->value << " ";
                    head = head->right;
                }
            }
        }
    }

    static void postOrderUnRecur1(Node *head) {
        if (head == nullptr) {
            return;
        }
        stack<Node *> help;
        stack<int> help2;
        help.push(head);
        while (!help.empty()) {
            head = help.top();
            help.pop();
            help2.push(head->value);
            if (head->left != nullptr) {
                help.push(head->left);
            }
            if (head->right != nullptr) {
                help.push(head->right);
            }
        }
        while (!help2.empty()) {
            int value = help2.top();
            help2.pop();
            cout << value << " ";
        }
    }

    static void postOrderUnRecur2(Node *head) {
        if (head == nullptr) {
            return;
        }
        stack<Node *> help;
        help.push(head);
        Node *c;
        while (!help.empty()) {
            c = help.top();
            help.pop();
            if (c->left != nullptr) {
                help.push(c->left);
            }
            if (c->right != nullptr) {
                help.push(c->right);
            }
            cout << c->value << " ";
        }
    }
};

int main() {
    Node *head = new Node(1);
    Node *node2 = new Node(2);
    Node *node3 = new Node(3);
    Node *node4 = new Node(4);
    Node *node5 = new Node(5);
    Node *node6 = new Node(6);
    Node *node7 = new Node(7);

    head->left = node2;
    head->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    node3->right = node7;

    PreInPostTraversal::preOrderRecur(head);
    cout << endl;
    PreInPostTraversal::preOrderUnRecur(head);
    cout << endl;
    PreInPostTraversal::inOrderRecur(head);
    cout << endl;
    PreInPostTraversal::inOrderUnRecur(head);
    cout << endl;
    PreInPostTraversal::postOrderRecur(head);
    cout << endl;
    PreInPostTraversal::postOrderUnRecur1(head);
    cout << endl;
    PreInPostTraversal::postOrderUnRecur2(head);
    cout << endl;

    system("pause");
}