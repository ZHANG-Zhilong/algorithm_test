#include <iostream>
#include <array>
#include <vector>

using namespace std;

class KTimesOneTime {
public:
//为何选择k进制？可以是2进制，x进制中，x<=k
//避免出现单个的数字是k的倍数，把k的倍数打平，使其每一位的数组均小于k
    static int onceNum(const vector<int> &arr, int k) {
        array<int, 32> eO;
        eO.fill(0);
        for (int i = 0; i < arr.size(); i++) {
            setExclusiveOr(eO, arr[i], k);
        }
        int ret = getNumFromKSysNum(eO, k);
        return ret;

    }

private:
    static void setExclusiveOr(array<int, 32> &eO, int value, int k) {
        array<int, 32> curSysNum = getKSysNumFromNum(value, k);
        for (int i = 0; i < eO.size(); i++) {
            eO[i] = (eO[i] + curSysNum[i]) % k;
        }
    }

    static array<int, 32> getKSysNumFromNum(int value, int k) {
        array<int, 32> res;
        res.fill(0);
        int index = 0;
        while (value != 0) {
            res[index++] = value % k;
            value /= k;
        }
        return res;
    }

    static int getNumFromKSysNum(array<int, 32> &eO, int k) {
        int ret = 0;
        for (int i = eO.size() - 1; i >= 0; i--) {
            ret = ret * k + eO[i];
        }
        return ret;
    }
};

void play() {
    vector<int> arr{1, 1, 1, 2, 6, 6, 2, 2, 10, 10, 10, 12, 12, 12, 6, 9};
    KTimesOneTime k;
    cout << k.onceNum(arr, 3);
    vector<int> arr2{-1, -1, -1, -1, -1, 2, 2, 2, 4, 2, 2};
    cout << endl << k.onceNum(arr2, 5) << endl;
}

int main(int argc, char *argv[]) {
    play();
    cout << endl << "ahola" << endl;
    return 0;
}
