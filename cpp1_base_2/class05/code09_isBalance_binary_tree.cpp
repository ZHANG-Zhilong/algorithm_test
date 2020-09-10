#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include<unordered_map>
#include <algorithm>

using namespace std;

class BalanceTree {

private:
    typedef struct Node {
        int value;
        struct Node *left;
        struct Node *right;

        Node(int data) : value(data), left(nullptr), right(nullptr) {}
    } Node;

    typedef struct ReturnData {
        int height;
        bool isB;

        ReturnData(int h, bool B) : height(h), isB(B) {}
    } ReturnData;

    ReturnData process(Node *head) {
        if (&head == nullptr) {
            return ReturnData(0, true);
        }
        ReturnData leftTreeinfo = process(head->left);
        if (leftTreeinfo.isB == false) {
            return ReturnData(0, false);
        }
        ReturnData rightTreeinfo = process(head->right);
        if (rightTreeinfo.isB == false) {
            return ReturnData(0, false);
        }
        if (abs(leftTreeinfo.height - rightTreeinfo.height) > 1) {
            return ReturnData(0, false);
        }

        return ReturnData(max(leftTreeinfo.height, rightTreeinfo.height) + 1, true);
    }

public:
    bool isBalance(Node head) {
        return process(&head).isB;
    }


};

int main() {

    system("pause");
    return 0;
}
