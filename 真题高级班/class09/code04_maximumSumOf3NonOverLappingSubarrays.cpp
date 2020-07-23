#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MaxSumOfThreeArrays {
public:
    static int maxSumOfThreeSubArrays(const vector<int> &arr, int k) {
        int N = arr.size();
        int sum = 0;
        vector<int> range(N, 0);  //记录每一个以i位置为开始的长度为k的子数组累加和
        vector<int> left(N, 0);     //从左向右的dp
        vector<int> right(N, 0);    //从右向左的dp

        for (int i = 0; i < k; i++) {
            sum += arr[i];
        }
        range[0] = sum;
        left[k - 1] = sum;  //左侧的dp数组
        for (int i = k; i < N; i++) {
            sum = sum - arr[i - k] + arr[i];  //当前子数组累加和
            range[i - k + 1] = sum;
            left[i] = std::max(left[i - 1], sum);
        }
        cout << "left" << endl;
        printVec(left);
        sum = 0;
        for (int i = N - 1; i > N - 1 - k; i--) {
            sum += arr[i];
        }
        right[N - k] = sum;
        for (int i = N - 1 - k; i >= 0; i--) {
            sum = sum + arr[i] - arr[i + k];
            right[i] = max(right[i + 1], sum);
        }
        cout << "right" << endl;
        printVec(right);

        sum = 0;
        int maxValue = INT32_MIN;
        for (int i = k; i < N - k; i++) {
            int temp = left[i - 1] + range[i] + right[i + k];
            maxValue = max(maxValue, temp);
        }
        return maxValue;
    }

    static void printVec(const vector<int> &arr) {
        for (const auto &n: arr) {
            cout << n << " ";
        }
        cout << endl;
    }
};

void play() {
    vector<int> arr{9, 8, 7, 6, 2, 2, 2, 2};
    int k = 2;
    cout << endl << MaxSumOfThreeArrays::maxSumOfThreeSubArrays(arr, k);
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
