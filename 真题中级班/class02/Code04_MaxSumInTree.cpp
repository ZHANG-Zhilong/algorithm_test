#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>

using namespace std;

//二叉树的递归套路
//假设X是头节点，头节点可以向其左子树和右子树要信息
//抽象左子树信息和右子树信息，明确需要什么信息
//头节点综合左子树的信息和右子树的信息并返回自己的信息
//

class Node {
public:
    int value;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    Node(int value) {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
};

using NodePtr = shared_ptr<Node>;

class Info {
public:
    int maxPathSum;

    Info(int maxPathSum) {
        this->maxPathSum = maxPathSum;
    }
};

using InfoPtr = shared_ptr<Info>;

class Code04_MaxSumInTree {
public:
    static int maxPath(NodePtr root) {
        if (root == nullptr) {
            return -1;
        }
        return process(root)->maxPathSum;
    }

    static InfoPtr process(NodePtr root) {
        if (root == nullptr) {
            return nullptr;
        }
        InfoPtr left = process(root->left);
        InfoPtr right = process(root->right);
        int p1 = root->value;
        int p2 = left != nullptr ? root->value + left->maxPathSum : 0;
        int p3 = right != nullptr ? root->value + right->maxPathSum : 0;
        if (left != nullptr && right != nullptr) {
            return make_shared<Info>(max(p2, p3));
        }
        if (left == nullptr && right == nullptr) {
            return make_shared<Info>(p1);
        }
        return make_shared<Info>(left == nullptr ? p3 : p2);
    }
};

void play() {
    NodePtr root = make_shared<Node>(1);
    root->left = make_shared<Node>(5);
    root->right = make_shared<Node>(9);
    root->left->right = make_shared<Node>(9);
    cout << Code04_MaxSumInTree::maxPath(root) << endl;
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
