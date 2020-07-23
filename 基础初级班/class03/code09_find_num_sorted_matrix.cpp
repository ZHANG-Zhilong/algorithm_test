#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

bool isContain(vector<vector<int>> v, int tar) {
    int i = 0, j = v[0].size() - 1;
    while (j >= 0 && i <= v.size() - 1) {
        if (v[i][j] == tar) {
            return true;
        } else if (v[i][j] > tar) {
            j--;
        } else {
            i++;
        }
    }
    return false;
}

int main() {

    vector<vector<int>> v = {{0,   1,   2,   3,   4,   5,   6},// 0
                             {10,  12,  13,  15,  16,  17,  18},// 1
                             {23,  24,  25,  26,  27,  28,  29},// 2
                             {44,  45,  46,  47,  48,  49,  50},// 3
                             {65,  66,  67,  68,  69,  70,  71},// 4
                             {96,  97,  98,  99,  100, 111, 122},// 5
                             {166, 176, 186, 187, 190, 195, 200},// 6
                             {233, 243, 321, 341, 356, 370, 380} // 7
    };

    cout << isContain(v, 233);
    system("pause");
}