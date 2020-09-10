#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Code02_appleMinBags {
public:
    static int minBags(const int apple) {
        if (apple < 0) {
            return -1;
        }
        int bag6 = -1;
        int bag8 = apple / 8;
        int rest = apple - 8 * bag8;
        while (bag8 >= 0 && rest < 24) {
            int restUse6 = rest % 6 == 0 ? rest / 6 : -1;
            if (restUse6 != -1) {
                bag6 = restUse6;
                break;
            }
            rest = apple - 8 * (--bag8);
        }
        return bag6 == -1 ? bag6 : bag6 + bag8;
    }

    static int minBags2(const int apple) {
        if (apple < 0) {
            return -1;
        }
        if (apple < 18) {
            if (apple == 6 || apple == 8) {
                return 1;
            } else if (apple == 12 || apple == 14 || apple == 16) {
                return 2;
            } else {
                return -1;
            }
        }
        return (apple - 18) / 8 + 3;
    };

};

void play() {
    int ret = 0;
    for (int i = 1; i < 100; i++) {
        if ((i & 1) == 1) continue;
        int ret2 = Code02_appleMinBags::minBags(i);
        int ret3 = Code02_appleMinBags::minBags2(i);
        if (ret2 != ret3) {
            cout << "opps" << endl;
            break;
        }
    }
    cout << "pass." << endl;
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
