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
    Node *next;

    Node(int data) {
        value = data;
        next = nullptr;
    }
};


class JosePhusKill {
public:
    Node *josePhusKill(Node *head, int m) {
        if (&head == nullptr || head->next == nullptr || m < 1) {
            return head;
        }
        Node *cur = head->next;
        int tmp = 1;   // list size
        while (cur != head) {
            cur = cur->next;
            tmp++;
        }
        tmp = getLive(tmp, m);
        while (--tmp != 0) {  //tmp-> servive node position
            head = head->next;
        }
        head->next = head;
        return head;
    }

private:
    int getLive(int i, int m) {
        if (i == 1) {
            return 1;
        }
        return (getLive(i - 1, m) + m - 1) % i + 1;
    }
};


int main() {
    Node head(1);
    head.next = new Node(2);
    head.next->next = new Node(3);
    head.next->next->next = &head;

    JosePhusKill jp;
    cout << jp.josePhusKill(&head, 2)->value << endl;

    system("pause");
    return 0;
}
