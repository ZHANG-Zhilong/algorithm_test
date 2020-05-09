#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Code05_maxOneBorderSize {

public:
    static int getMaxSize(const vector<vector<int>> &matrix) {
        if (matrix.empty() || matrix.front().empty()) {
            return -1;
        }

        int col = matrix.size(), row = matrix.front().size();
        int minBoard = min(col, row);
        vector<vector<int>> right(col, vector<int>(row, 0));
        vector<vector<int>> down(col, vector<int>(row, 0));
        setBorderMap(matrix, right, down);

        for (int size = minBoard; size >= 1; size--) {
            if (hasSizeOfBorder(size, col, row, matrix, right, down)) {
                return size;
            }
        }
    }

    static bool hasSizeOfBorder(
            int size, int col, int row,
            const vector<vector<int>> &matrix,
            const vector<vector<int>> &right,
            const vector<vector<int>> &down) {

        for (int i = 0; i + size - 1 < col; i++) {
            for (int j = 0; j + size - 1 < row; j++) {
                if (right[i][j] >= size
                    && down[i][j] >= size
                    && right[i + size - 1][j] >= size
                    && down[i][j + size - 1] >= size) {
                    return true;
                }
            }
        }
    }

    static void setBorderMap(
            const vector<vector<int>> &matrix,
            vector<vector<int>> &right,
            vector<vector<int>> &down
    ) {
        //右侧有多少个连续的1
        //right[i][j]  matrix[i][j], col i count '1' (include [i][j])
        //down[i][j]   matrix[i][j], row j count '1' (include [i][j])
        int col = right.size();  //only check once
        int row = right.front().size();
        if (matrix.size() != col || matrix.size() != row) {
            cout << "input error." << endl;
            return;
        }
        right.back().back() = matrix.back().back() == 1 ? 1 : 0;
        down.back().back() = matrix.back().back() == 1 ? 1 : 0;
        for (int i = col - 2; i >= 0; i--) {
            if (matrix[i].back() == 1) {
                right[i].back() = 1;
                down[i].back() = down[i + 1].back() + 1;
            }
        }

        for (int j = row - 2; j >= 0; j--) {
            if (matrix.back()[j] == 1) {
                down.back()[j] = 1;
                right.back()[j] = right.back()[j + 1] + 1;
            }
        }

        for (int i = col - 2; i >= 0; i--) {
            for (int j = row - 2; j >= 0; j--) {
                if (matrix[i][j] == 1) {
                    right[i][j] = right[i][j + 1] + 1;
                    down[i][j] = down[i + 1][j] + 1;
                }
            }
        }
    }

    static vector<vector<int>> generateRandom01Matrix(int colSiz, int rowSiz) {
        vector<vector<int>> matrix(colSiz, vector<int>(rowSiz, 0));
        random_device rd;
        for (int i = 0; i < colSiz; i++) {
            for (int j = 0; j < rowSiz; j++) {
                matrix[i][j] = 2 * (double) rd() / random_device().max();
            }
        }
        return matrix;
    }

    static void printMatrix(const vector<vector<int>> &matrix) {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.front().size(); j++) {
                cout << matrix[i][j] << "  ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }
};

void play() {
    auto matrix = Code05_maxOneBorderSize::generateRandom01Matrix(5, 5);
    vector<vector<int>> right(matrix.size(), vector<int>(matrix.front().size(), 0));
    vector<vector<int>> down(matrix.size(), vector<int>(matrix.front().size(), 0));
    Code05_maxOneBorderSize::setBorderMap(matrix, right, down);
    Code05_maxOneBorderSize::printMatrix(matrix);
    Code05_maxOneBorderSize::printMatrix(right);
    Code05_maxOneBorderSize::printMatrix(down);
    cout << Code05_maxOneBorderSize::getMaxSize(matrix) << endl;
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
