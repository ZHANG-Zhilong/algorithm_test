#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <queue>
#include<unordered_map>
#include <algorithm>

using namespace std;

//http://myblog.huangjinjin.xin/2018/11/27/暴力递归改动态规划套路2-纸牌博弈问题/
class CardInLine {
public:
    int win2(vector<int> arr) {
        if (arr.empty()) {
            return 0;
        }
        vector<vector<int>> f(arr.size(), vector<int>(arr.size(), 0));
        vector<vector<int>> s(arr.size(), vector<int>(arr.size(), 0));
        for (int j = 0; j < arr.size(); j++) {
            f[j][j] = arr[j];
            for (int i = j - 1; i >= 0; i--) {
                f[i][j] = max(arr[i] + s[i + 1][j], arr[j] + s[i][j - 1]);
                s[i][i] = min(f[i + 1][j], f[i][j - 1]);
            }
        }
        return max(f[0][arr.size() - 1], s[0][arr.size() - 1]);
    }


    int win1(vector<int> arr) {
        if (arr.empty()) {
            return 0;
        }
        return max(f(arr, 0, arr.size() - 1), s(arr, 0, arr.size() - 1));
    }

private:
    int f(vector<int> arr, int i, int j) {
        if (i == j) {
            return arr[i];
        }
        return max(arr[i] + s(arr, i + 1, j), arr[j] + s(arr, j, j - 1));
    }

    int s(vector<int> arr, int i, int j) {
        if (i == j) {
            return 0;
        }
        return min(f(arr, i + 1, j), f(arr, i, j - 1));
    }
};

int main() {

    system("pause");
    return 0;
}
