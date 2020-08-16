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

class Hanoi {
public:
    void hanoi(int n) {
        if (n > 0) {
            func(n, "left", "right", "mid");
        }
    }

private:
    void func(int n, string from, string to, string help) {
        if (n == 1) {
            cout << "move " << n << " from " << from << " to " << to << endl;
        } else {
            func(n - 1, from, help, to);
            cout << "move " << n << " from " << from << " to " << to << endl;
            func(n - 1, help, to, from);
        }

    }

};

int main() {
    Hanoi hanoi;
    hanoi.hanoi(3);

    system("pause");
    return 0;
}