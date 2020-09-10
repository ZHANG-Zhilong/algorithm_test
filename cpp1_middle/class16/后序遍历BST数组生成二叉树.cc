#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>

using namespace std;

class BitNode {
public:
    int value;
    shared_ptr<BitNode> left;
    shared_ptr<BitNode> right;

    BitNode(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class PostArrayToBST {
public:
    static shared_ptr<BitNode> postArrayToBST(const vector<int> &arr) {
        if (arr.empty()) {
            return NULL;
        }
        return buildTree(arr, 0, arr.size() - 1);
    }

    static void postTraverse(shared_ptr<BitNode> head) {
        if (head == nullptr) {
            return;
        }
        postTraverse(head->left);
        postTraverse(head->right);
        cout << head->value << " ";
    }

private:
    static shared_ptr<BitNode> buildTree(const vector<int> &arr, int l, int r) {
        if (l > r) {
            return NULL;
        }

        auto head = make_shared<BitNode>(arr[r]);

        if (l == r) {
            return head;
        }
        int i = findLeftPos(arr, l, r);
        head->left = buildTree(arr, l, i);
        head->right = buildTree(arr, i + 1, r - 1);
        return head;
    }


    static int findLeftPos(const vector<int> &arr, int l, int r) {
        if (l == r) {
            return arr[r];
        }
        int mid = (l + r) >> 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (arr[mid] > arr[r]) {
                r = mid;
            } else {  //arr[mid]<=arr[r]
                l = mid;
            }  //没有判==
        }
        return l;
    }
};


void play() {
    vector<int> arr{1, 3, 2, 6, 8, 7, 5};
    auto head = PostArrayToBST::postArrayToBST(arr);
    PostArrayToBST::postTraverse(head);
    cout << endl;
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
