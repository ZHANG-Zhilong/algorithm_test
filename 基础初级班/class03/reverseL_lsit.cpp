#include <iostream>
#include <string>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <typeinfo>
#include <list>
#include <set>

using namespace std;

typedef struct Node {
    int value;
    struct Node *next;

    Node(int data) : value(data), next(nullptr) {};
} Node;

class Node2 {
public:
    int value;
    Node2 *next;

    Node2(int data) {
        value = data;
        next = nullptr;
    }
};

void printLinkedList(Node2 &head) {
    if (&head == nullptr) {
        return;
    }
    Node2 *dummy = new Node2(-1);
    dummy->next = &head;
    Node2 *node = dummy->next;
    while (node != nullptr) {
        cout << node->value << " ";
        node = node->next;
    }
    cout << endl;
}

Node2 reverseLinkedList(Node2 *head) {
    if (&head == nullptr && head->next != nullptr) {
        return *head;
    }
    Node2 *dummy = new Node2(-1);
    dummy->next = head;
    Node2 *pre = nullptr, *next = nullptr;
    while (head != nullptr) {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }
    dummy->next = pre;
    return *(dummy->next);
}

int main() {
    Node2 head(1);
    head.next = new Node2(2);
    head.next->next = new Node2(3);
    printLinkedList(head);
    Node2 node = reverseLinkedList(&head);
    printLinkedList(node);

    system("pause");
    return 0;
}