#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

class BitNode {
public:
    shared_ptr<BitNode> left;
    shared_ptr<BitNode> right;
    int value;

    BitNode(int value) {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
};

class Info {
public:
    int maxPathSum;
    int asHeadMaxPathSum;

    Info(int maxPathSum, int asHeadMaxPathSum) {
        this->maxPathSum = maxPathSum;
        this->asHeadMaxPathSum = asHeadMaxPathSum;
    }
};

class BinaryTreeMaxPathSum {
public:
    shared_ptr<Info> binaryTreeMaxPathSum(shared_ptr<BitNode> root) {
        if (root->left == nullptr && root->right == nullptr) {
            int value = root->value;
            return make_shared<Info>(value, value);
        }

        auto left = make_shared<Info>(0, 0);
        auto right = make_shared<Info>(0, 0);
        if (root->left != nullptr) {
            left = binaryTreeMaxPathSum(root->left);
        }
        if (root->right != nullptr) {
            right = binaryTreeMaxPathSum(root->right);
        }

        int p1 = left->maxPathSum;
        int p2 = right->maxPathSum;
        int p3 = root->value;
        int p4 = root->value + left->asHeadMaxPathSum;
        int p5 = root->value + right->asHeadMaxPathSum;
        int p6 = p4 + p5 - root->value;

        return make_shared<Info>(max(p1, p2), max({p3, p4, p5, p6}));
    }
};

void play() {
    shared_ptr<BitNode> root1 = make_shared<BitNode>(2);
    root1->left = make_shared<BitNode>(1);
    root1->right = make_shared<BitNode>(3);
    BinaryTreeMaxPathSum bt;
    auto rst1 = bt.binaryTreeMaxPathSum(root1);
    cout << max(rst1->asHeadMaxPathSum, rst1->maxPathSum) << endl;

};


int main(int argc, char *argv[]) {
    play();
    cout << "ahola" << endl;
    return 0;
}
