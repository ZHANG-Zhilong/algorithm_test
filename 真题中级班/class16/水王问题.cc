#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <memory>
#include <array>

using namespace std;

//查找一个数字出现次数大于数组长度的一半
//水王问题
class HalfMajor {
public:
    static int printHalfMajor(const vector<int> &arr) {
        if (arr.empty()) {
            return -1;
        }
        int hp = 0;
        int candy = 0;
        for (const auto &n: arr) {
            if (hp == 0) {
                candy = n;
                hp++;
            } else if (n == candy) {
                hp++;
            } else {
                hp--;
            }
        }
        if (hp == 0) {
            return -1;
        } else {
            int times = 0;
            for (const auto &n: arr) {
                if (n == candy) {
                    times++;
                }
            }
            return times > arr.size() / 2 ? candy : -1;
        }
    }
};

void play() {
    vector<int> arr{1, 2, 7, 3, 4, 5, 6, 7, 7};
    cout << HalfMajor::printHalfMajor(arr);
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
