#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

struct Node {
    int value;
    Node *next;

    Node(int data) : value(data), next(NULL) {};

};

void printCommonPart(Node *head1, Node *head2) {
    while (head1 != NULL && head2 != NULL) {
        if (head1->value < head2->value) {
            head1 = head1->next;
        } else if (head1->value < head2->value) {
            head2 = head2->next;
        } else {
            cout << head1->value << "  ";
            head1 = head1->next;
            head2 = head2->next;
        }

    }
    cout << endl;
}

void printLinkList(Node *node) {
    while (node != nullptr) {
        cout << node->value << "  ";
        node = node->next;
    }
    cout << endl;
}

int main() {
    Node *node1 = new Node(1);
    Node dummy1(-1);
    dummy1.next = node1;
    node1->next = new Node(2);
    node1->next->next = new Node(4);
    node1->next->next->next = new Node(6);

    Node *node2 = new Node(2);
    Node dummy2(-1);
    dummy2.next = node2;
    node2->next = new Node(4);
    node2->next->next = new Node(7);

    printLinkList(node1);
    printLinkList(node2);
    printCommonPart(node1, node2);

    system("pause");
}