#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <stack>
#include <queue>

using namespace std;

void printLevel(vector<vector<int>> v, int row1, int col1, int row2, int col2, bool upPrint);

void printMatrixZigZag(vector<vector<int>> v) {
    int row1 = 0, col1 = 0;
    int row2 = 0, col2 = 0;
    int endr = v.size() - 1, endc = v[0].size() - 1;
    bool upPrint = true;
    while (row1 <= endr) {
        printLevel(v, row1, col1, row2, col2, upPrint);
        printf("flag: %d %d %d %d\n", row1, col1, row2, col2);
        row1 = col1 == endc ? row1 + 1 : row1;
        col1 = col1 == endc ? col1 : col1 + 1;
        col2 = row2 == endr ? col2 + 1 : col2;
        row2 = row2 == endr ? row2 : row2 + 1;
        upPrint = !upPrint;
    }
}

void printLevel(vector<vector<int>> v, int row1, int col1, int row2, int col2, bool upPrint) {

    if (upPrint == true) {
        while (row2 >= row1) {
            cout << v[row2--][col2++] << " ";
        }
    } else {
        while (row1 <= row2) {
            cout << v[row1++][col1--] << " ";
        }
    }
}

int main() {
    vector<vector<int>> v = {{1, 2, 3},
                             {4, 5, 6},
                             {7, 8, 9}};
    printMatrixZigZag(v);
    system("pause");
}