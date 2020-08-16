#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Code03_eatGrass {
public:
    static string winner(const int n) {
        if (n < 5) {
            return (n == 0 || n == 2) ? "后手" : "先手";
        }
        int base = 1;
        while (base <= n) {
            if (winner(n - base) == "后手") {
                return "先手";
            }
            if (base > n / 4) {
                break;
            }
            base *= 4;
        }
        return "后手";
    }

    static string winner2(const int n) {
        int r = n % 5;
        return (r == 0 || r == 2) ? "后手" : "先手";
    }
};

void play() {
    for (int i = 0; i < 50; i++) {
        if (Code03_eatGrass::winner(i) != Code03_eatGrass::winner2(i)) {
            cout << "opps" << endl;
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
