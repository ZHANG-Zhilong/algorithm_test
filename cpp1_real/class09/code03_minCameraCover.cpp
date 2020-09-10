//
// Created by hizhi on 2020/4/24.
// 监控二叉树 @ leetcode
//

#include <iostream>
#include <algorithm>
#include <memory>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution1 {
private:
    class Info {
    public:
        long long uncover;
        long long coveredHasCamera;
        long long coveredNoCamera;

        Info(long long uncover, long long coveredHasCamera, long long coveredNoCamera) {
            this->uncover = uncover;
            this->coveredHasCamera = coveredHasCamera;
            this->coveredNoCamera = coveredNoCamera;
        }
    };

public:
    static int minCameraCover(TreeNode *root) {
        Info rst = process(root);
        return min({rst.coveredHasCamera, rst.coveredNoCamera, rst.uncover + 1});
    }

    static Info process(TreeNode *root) {
        if (root == nullptr) {
            return Info(INT32_MAX, INT32_MAX, 0);
        }
        Info left = process(root->left);
        Info right = process(root->right);
        long long uncover = 0, coveredHasCamera = 0, coveredNoCamera = 0;
        uncover = left.coveredNoCamera + right.coveredNoCamera;
        coveredHasCamera = min({left.coveredNoCamera, left.coveredHasCamera, left.uncover}) +
                           min({right.coveredNoCamera, right.coveredHasCamera, right.uncover});
        coveredNoCamera = min({left.coveredHasCamera + right.coveredHasCamera,
                               left.coveredHasCamera + right.coveredNoCamera,
                               left.coveredNoCamera + right.coveredHasCamera
                              });
        cout << uncover << " " << coveredHasCamera + 1 << " " << coveredNoCamera << endl;
        return Info(uncover, coveredHasCamera + 1, coveredNoCamera);
    }
};

class Solution2 {
private:
    enum class Status {
        UNCOVERED, COVERED_NO_CAMERA, COVERED_HAS_CAMERA
    };

    class Info {
    public:
        Status status;
        int camera;

        Info(Status status, int camera) {
            this->status = status;
            this->camera = camera;
        }
    };

public:
    static int minCameraCover(TreeNode *root) {
        Info rst = process(root);
        return rst.status == Status::UNCOVERED ? rst.camera + 1 : rst.camera;
    }

private:
    static Info process(TreeNode *root) {
        if (root == nullptr) {
            return Info(Status::COVERED_NO_CAMERA, 0);
        }
        Info left = process(root->left);
        Info right = process(root->right);
        int camera = left.camera + right.camera;
        if (left.status == Status::UNCOVERED || right.status == Status::UNCOVERED) {
            return Info(Status::COVERED_HAS_CAMERA, camera + 1);
        }
        if (left.status == Status::COVERED_HAS_CAMERA || right.status == Status::COVERED_HAS_CAMERA) {
            return Info(Status::COVERED_NO_CAMERA, camera);
        }
        return Info(Status::UNCOVERED, camera);
    }

};

void play() {
    TreeNode root(1);
    Solution1::minCameraCover(&root);
    Solution2::minCameraCover(&root);
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
