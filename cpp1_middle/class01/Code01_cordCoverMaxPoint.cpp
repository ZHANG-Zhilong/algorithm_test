#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Code01_CordCoverMaxPoint {
public:
    static int maxPoint(const vector<int> &arr, const int L) {
        if (arr.empty() || L < 1) {
            return 0;
        }
        int ret = 0;
        //以i位置为结尾，每一个位置尝试，找到最多覆盖点数量
        for (int i = 0; i < arr.size(); i++) {
            int l = findNearest(arr, i, arr[i] - L);
            ret = max(ret, i - l + 1);
        }
        return ret;
    }

private:
    static int findNearest(const vector<int> &arr, int right, int value) {
        int left = 0;
        int index = right;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (arr[mid] <= value) {
                left = mid + 1;
            } else {
                index = mid;
                right = mid - 1;
            }
        }
        return index;
    }

public:
    static int maxPoint2(const vector<int> &arr, const int L) {
        if (arr.empty() || L < 1) {
            return 0;
        }
        int left = 0, right = 0, N = arr.size();
        int ret = 0;
        while (left < N) {
            while (right < N && arr[right] - arr[left] <= L) {
                right++;
            }
            ret = max(ret, right - left);
            left++;
        }
        return ret;
    }

    static int maxPoint3(const vector<int> &arr, const int L) {
        if (arr.empty() || L < 1) {
            return 0;
        }
        int ret = 0;
        for (int i = 0; i < arr.size(); i++) {
            //找到大于value的第一个数
            int l = process(arr, i, arr[i] - L);
            ret = max(ret, i - l + 1);
        }
        return ret;
    }

    static int process(const vector<int> &arr, int r, int value) {
        int l = 0;
        int index = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (arr[mid] <= value) {
                l = mid + 1;
            } else {
                index = mid;
                r = mid - 1;
            }
        }
        return index;
    }

    //二分查找大于k的第一个数
    static int binaryFind(const vector<int> &arr, int k) {
        int l = 0, r = arr.size() - 1;
        int index = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (arr[mid] <= k) {
                l = mid + 1;
                cout << "l:" << l << endl;
            } else {
                index = mid;
                r = mid - 1;
                cout << "r:" << r << endl;
            }
        }
        return arr[index];
    }
};

void play() {
    vector<int> arr{1, 2, 3, 6, 7, 8, 9, 10, 22};
    int length = 6;
    cout << Code01_CordCoverMaxPoint::maxPoint(arr, length) << endl;
    cout << Code01_CordCoverMaxPoint::maxPoint2(arr, length) << endl;

    //测试二分法
    //cout << Code01_CordCoverMaxPoint::binaryFind(arr, length) << endl;
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
