#include <iostream>
#include <string>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <typeinfo>
#include <list>
#include <set>

using namespace std;

class MinPath {

public:
    int minPath1(const vector<vector<int>> &matrix) {
        return process1(matrix, 0, 0);
    }

    int process1(const vector<vector<int>> &matrix, int i, int j) const {
        if (i == matrix.size() - 1 && j == matrix[0].size() - 1) {
            return matrix[i][j];
        }
        if (i == matrix.size() - 1) {
            return matrix[i][j] + process1(matrix, i, j + 1);
        }
        if (j == matrix[0].size() - 1) {
            return matrix[i][j] + process1(matrix, i + 1, j);
        }

        return matrix[i][j] + min(process1(matrix, i, j + 1),
                                  process1(matrix, i + 1, j));
    }

public:
    int minPath2(const vector<vector<int>> &matrix) {
        return process2(matrix, 0, 0);
    }

    unordered_map<string, int> sillyCache;

    string getId(int i, int j) { return to_string(i) + "_" + to_string(j); }

    int process2(const vector<vector<int>> &matrix, int i, int j) {
        int rst = 0;
        if (i == matrix.size() - 1 && j == matrix[0].size() - 1) {
            string nextKey = getId(i, j);
            if (sillyCache.count(nextKey) > 0) {
                rst = sillyCache[nextKey];
            } else {
                rst = matrix[i][j];
            }
        } else if (i == matrix.size() - 1) {
            string nextKey = getId(i, j + 1);
            if (sillyCache.count(nextKey) > 0) {
                rst = matrix[i][j] + sillyCache[nextKey];
            } else {
                rst = matrix[i][j] + process2(matrix, i, j + 1);
            }
        } else if (j == matrix[0].size() - 1) {
            string nextKey = getId(i + 1, j);
            if (sillyCache.count(nextKey) > 0) {
                rst = matrix[i][j] + sillyCache[nextKey];
            } else {
                rst = matrix[i][j] + process2(matrix, i + 1, j);
            }
        } else {
            string rightNextKey = getId(i, j + 1);
            string downNextKey = getId(i + 1, j);
            int rightNext = 0, downNext = 0;

            if (sillyCache.count(rightNextKey) > 0) {
                rightNext = sillyCache[rightNextKey];
            } else {
                rightNext = process2(matrix, i, j + 1);
            }

            if (sillyCache.count(downNextKey) > 0) {
                downNext = sillyCache[downNextKey];
            } else {
                downNext = process2(matrix, i + 1, j);
            }

            rst = matrix[i][j] + min(downNext, rightNext);
        }
        string sid = getId(i, j);
        sillyCache.insert(pair<string, int>(sid, rst));
        return rst;
    }

public:
    int minPath3(const vector<vector<int>> &matrix) {
        return process3(matrix, 0, 0);
    }

    int process3(const vector<vector<int>> &matrix, int i, int j) {
        if (&matrix == nullptr || matrix.size() == 0 || &matrix[0] == nullptr || matrix[0].size() == 0) {
            cout << "the matrix is null." << endl;
            return -1;
        }
        int row = matrix.size();
        int col = matrix[0].size();
        vector<vector<int>> dp(row, vector<int>(col, 0));
        dp.at(0).at(0) = matrix.at(0).at(0);

        for (size_t i = 1; i < row; i++) {
            dp.at(i).at(0) = dp.at(i - 1).at(0) + matrix.at(i).at(0);
        }
        for (size_t j = 1; j < col; j++) {
            dp.at(0).at(j) = dp.at(0).at(j - 1) + matrix.at(0).at(j);
        }
        for (size_t i = 1; i < row; i++) {
            for (size_t j = 1; j < col; j++) {
                dp.at(i).at(j) = min(dp.at(i - 1).at(j), dp.at(i).at(j - 1)) + matrix.at(i).at(j);
            }
        }
        return dp.at(row - 1).at(col - 1);
    }
};

int main() {
    vector<vector<int>> matrix = {{1, 3, 5, 9},
                                  {8, 1, 3, 4},
                                  {5, 0, 6, 1},
                                  {8, 8, 4, 0}};
    MinPath minpath;
    cout << minpath.minPath1(matrix) << endl;
    cout << minpath.minPath2(matrix) << endl;
    cout << minpath.minPath3(matrix) << endl;
    system("pause");
    return 0;
}