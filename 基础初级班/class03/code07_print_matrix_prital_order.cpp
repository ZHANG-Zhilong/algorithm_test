#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <stack>
#include <queue>

using namespace std;

void printEdge(vector<vector<int>> v, int row1, int col1, int row2, int col2);

void spiralOrderPrint(vector<vector<int>> v) {
    int row1 = 0, col1 = 0;
    int row2 = v.size() - 1, col2 = v[0].size() - 1;
    while (col1 <= col2 && row1 <= row2) {
        printEdge(v, row1++, col1++, row2--, col2--);
    }
}

void printEdge(vector<vector<int>> v, int row1, int col1, int row2, int col2) {
    if (row1 == row2) {
        int i = col1;
        while (i <= col2) {
            cout << v[row1][i++] << " ";
        }
    } else if (col1 == col2) {
        int i = row1;
        while (i <= row2) {
            cout << v[i++][col1] << " ";
        }
    } else {
        int curc = col1, curr = row1;
        while (curc < col2) {
            cout << v[curr][curc++] << " ";
        }
        while (curr < row2) {
            cout << v[curr++][curc] << " ";
        }
        while (curc > col1) {
            cout << v[curr][curc--] << " ";
        }
        while (curr > row1) {
            cout << v[curr--][curc] << " ";
        }
    }
}

int main() {
    vector<vector<int>> v = {{1},
                             {2}};
    spiralOrderPrint(v);
    system("pause");
}