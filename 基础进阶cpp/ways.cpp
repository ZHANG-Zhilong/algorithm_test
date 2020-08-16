#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <queue>
#include<unordered_map>
#include <algorithm>

using namespace std;

//N 一共有1~N的位置
//M 来到的位置
//P 可以走的步数
//K 最终停在的位置
//返回值 一共有多少中走法
int ways(int N, int curPosition, int restSteps, int K) {
    if (N < 2 || curPosition < 1 || curPosition > N || restSteps < 0 || K < 1 || K > N) {
        return 0;
    }
    if (restSteps == 0) {
        return curPosition == K ? 1 : 0;
    }
    int res = 0;
    if (curPosition == 1) {
        res = ways(N, curPosition + 1, restSteps - 1, K);
    }
    if (curPosition == N) {
        res = ways(N, curPosition - 1, restSteps - 1, K);
    }
    if (curPosition > 1 || curPosition < N) {
        res = ways(N, curPosition - 1, restSteps - 1, K) +
              ways(N, curPosition + 1, restSteps - 1, K);
    }
    return res;
}

int main() {

    system("pause");
    return 0;
}
