#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include<unordered_map>
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

    bool operator==(const Node &node) const {
        return this->value == node.value && this->left == node.left && this->right == node.right;
    }

};

class ReturnType {
public:
    int size;
    Node *head;
    int max;
    int min;

    ReturnType(int size, Node *head, int max, int min) {
        this->size = size;
        this->head = head;
        this->max = max;
        this->min = min;
    }
};

class BigestSubBST {
public:
    Node bigestSubBST(Node head) {

    }

    ReturnType process(Node head) {
        if (&head == nullptr) {
            //避免干扰决策过程，可以最后写bascase
            return ReturnType(0, nullptr, INT_MIN, INT_MAX);
        }

        //默认左右子树可以返回相应信息，认为是一个黑盒过程
        Node *left = head.left;
        Node *right = head.right;
        ReturnType leftSubTreesInfo = process(*left);
        ReturnType rightSubTreesInfo = process(*right);

        //我这棵树怎么返回相应信息
        int p3IncludeItSelf = 0;
        if (leftSubTreesInfo.head == left && rightSubTreesInfo.head == right
            && leftSubTreesInfo.max < head.value && rightSubTreesInfo.min > head.value) {
            p3IncludeItSelf = leftSubTreesInfo.size + 1 + rightSubTreesInfo.size;
        }

        //最大搜索二叉树来自我的左子树，最大搜索二叉树来自我的右子树
        int p1 = leftSubTreesInfo.size;
        int p2 = rightSubTreesInfo.size;

        //拆黑盒的过程一直到结束
        //my answer
        int maxSize = max({p1, p3IncludeItSelf, p2});

        //看搜索二叉树来自那种情况，是哪种情况，头部就相应的变成谁的返回值
        Node *maxHead = p1 > p2 ? leftSubTreesInfo.head : rightSubTreesInfo.head;
        if (maxSize == p3IncludeItSelf) {
            maxHead = &head;
        }

        return ReturnType(maxSize, maxHead, max({leftSubTreesInfo.max, rightSubTreesInfo.max, head.value}),
                          min({leftSubTreesInfo.min, rightSubTreesInfo.min, head.value}));
    }
};

int main() {

    system("pause");
    return 0;
}
