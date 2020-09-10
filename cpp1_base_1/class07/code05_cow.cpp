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


class Cow {
public:
    int cowNum(int n) {
        if (n < 0) {
            return 0;
        }
        if (n == 1 || n == 2 || n == 3) {
            return n;
        }
        return cowNum(n - 1) + cowNum(n - 3);
    }

private:


};

int main() {

    Cow cow;
    cout << cow.cowNum(3);
    system("pause");
    return 0;
}