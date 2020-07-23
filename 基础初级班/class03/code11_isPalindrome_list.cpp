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

typedef struct Node {
    int value = 0;
    struct Node *next;

    Node(int data) : value(data), next(nullptr) {};
} Node;

int printLinkedList(Node *head);

// n extra space.
bool isPalindrome1(Node *head) {
    if (head == nullptr) {
        return true;
    }
    Node dummy = Node(0);
    dummy.next = head;

    stack<int> helpstack;
    while (head->next != nullptr) {
        helpstack.push(head->value);
        head = head->next;
    }

    head = dummy.next;
    while (!helpstack.empty() && head != nullptr) {
        int value = helpstack.top();
        if (value == head->value) {
            head = head->next;
            helpstack.pop();
        } else {
            return false;
        }
    }
    return true;
}

// n/2 extra space.
bool isPalindrome2(Node *head) {
    if (head == nullptr || head->next != nullptr) {
        return true;
    }
    stack<int> helpstack;
    Node *dummy = new Node(-1);
    dummy->next = head;

    Node *fast = dummy->next;
    Node *slow = dummy->next->next;

    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    while (slow != nullptr) {
        helpstack.push(slow->value);
        slow = slow->next;
    }

    head = dummy->next;
    while (head != nullptr) {
        if (head->value != helpstack.top()) {
            return false;
        }
        helpstack.pop();
        head = head->next;
    }
    return true;
}

bool isPalindrome3(Node *head) {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }
    bool ret = true;
    Node *dummy = new Node(-1);
    dummy->next = head;
    Node *n1 = dummy->next;
    Node *n2 = dummy->next;
    Node *n3 = dummy->next;

    if (n2->next != nullptr && n2->next->next != nullptr) {
        n2 = n2->next->next;
        n1 = n1->next;
    }  // n1-mid  n2-end or end-1

    //reverser the right part linked list.
    n2 = n1->next;
    n1->next = nullptr;
    while (n2 != nullptr) {
        n3 = n2->next;
        n2->next = n1;
        n1 = n2;
        n2 = n3;
        //node1 -> node2 -> node3
    }  //  n1       n2      <n3>
    n3 = n1;
    n1 = n3;

    //judge palindrome structre.
    n2 = dummy->next;
    while (n2 != nullptr && n1 != nullptr) {
        if (n1->value != n2->value) {
            ret = false;
            break;
        }
        n1 = n1->next;
        n2 = n2->next;
    }

    //recover the reversed linked list.
    n2 = n3->next;
    n3->next = nullptr;
    while (n2 != nullptr) {
        n1 = n2->next;
        n2->next = n3;
        n3 = n2;
        n2 = n1;
        //n2 = n1;   wrong writing
        //n3 = n2;
    }
    printLinkedList(dummy->next);
    return ret;
}

int printLinkedList(Node *head) {
    if (head == nullptr) {
        cout << "the LinkList is null\n";
        return -1;
    }
    while (head != nullptr) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
    return 0;
}


int main() {
    Node *node1 = new Node(1);
    node1->next = new Node(2);
    node1->next->next = new Node(1);
    node1->next->next->next = new Node(1);

    printLinkedList(node1);

    if (isPalindrome3(node1) == true) {
        cout << "the linkedlist is palindrome.\n";
    } else {
        cout << "not\n";
    }


    system("pause");
}