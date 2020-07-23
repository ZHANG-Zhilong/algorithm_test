#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <typeinfo>
#include <list>
#include <set>

using namespace std;

int getMin(const vector<int> &v, int L, int R) {
    if (L == R) {
        return v[L];
    }
    int mid = (L + R) / 2;
    int l = getMin(v, L, mid);
    int r = getMin(v, mid + 1, R);
    return min(l, r);
}

long factorial(int n) {

    if (n == 1) return 1l;
    return n * factorial(n - 1);
}

int main() {
    vector<int> v = {1, 2, 3, 4, 6, 7, 5, 6, 4, 3, 0};
    cout << getMin(v, 0, v.size() - 1) << endl;

    long rst = factorial(10);
    cout << rst << endl;
    system("pause");
    return 0;
}