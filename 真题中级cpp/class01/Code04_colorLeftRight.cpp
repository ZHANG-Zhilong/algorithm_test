#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Code04_colorLeftRight {
public:
    //left R, right G
    static int minPaint(const string &str) {
        if (str.empty()) {
            return -1;
        }
        const int N = str.size();
        vector<int> left(N, 0);
        vector<int> right(N, 0);
        int temp = 0;
        for (int i = 0; i < N; i++) {
            temp += str[i] == 'G' ? 1 : 0;
            left[i] = temp;
        }
        temp = 0;
        for (int i = N - 1; i >= 0; i--) {
            temp += str[i] == 'R' ? 1 : 0;
            right[i] = temp;
        }
        temp = INT32_MAX;
        for (int i = 0; i < N; i++) {
            temp = min({temp, left[i], right[i]});
        }
        return temp;
    }
};

void play() {
    string str = "GGGGGR";
    cout << Code04_colorLeftRight::minPaint(str) << endl;
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
