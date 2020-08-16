#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include<unordered_map>
#include <algorithm>

using namespace std;

/*
    二叉树中
*/
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

    bool operator==(const Node &node) const {
        return this->value == node.value && this->left == node.left && this->right == node.right;
    }

};

class ReturnType {
public:
    int maxDistance;
    int height;

    ReturnType(int maxDistance, int height) {
        this->maxDistance = maxDistance;
        this->height = height;
    }
};

class MaxDistance {
private:
    ReturnType process(Node head) {

        //basecase
        if (&head == nullptr) {
            return ReturnType(0, 0);
        }

        //collect info
        ReturnType leftTreesInfo = process(*head.left);
        ReturnType rightTreesInfo = process(*head.right);

        //process info
        int p3IncludeHead = leftTreesInfo.height + 1 + rightTreesInfo.height;
        int p1left = leftTreesInfo.maxDistance;
        int p2right = rightTreesInfo.maxDistance;

        //return rst
        int rstDistance = max({p3IncludeHead, p1left, p2right});
        int headHeight = max({leftTreesInfo.height, rightTreesInfo.height}) + 1;

        return ReturnType(rstDistance, headHeight);
    }

public:
    int getMaxDistance(Node head) {
        return process(head).maxDistance;
    }

};


int main() {

    system("pause");
    return 0;
}
