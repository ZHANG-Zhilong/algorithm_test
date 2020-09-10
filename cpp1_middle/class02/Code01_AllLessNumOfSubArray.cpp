#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

//窗口最大值最小值更新结构
//采用双根队列的方式，进行更新，代价是O(1)
//最大值更新：双根队列，从左向右严格递减，qMax.front()是该窗口内最大值的索引
//右边的是最大值的候补元素，值越大、越靠近R越靠左
//同理，最小值的更新是 从左到右严格递增，qMin.front()是窗口内最小值的索引
class Code01_AllLessNumOfSubArray {
public:
    static int getNum(const vector<int> &arr, int k) {
        if (arr.empty()) {
            return -1;
        }
        list<int> qMax, qMin;
        int l = 0, r = 0;
        int ret = 0;
        while (l < arr.size()) {
            while (r < arr.size()) {
                while (!qMax.empty() && arr[qMax.back()] <= arr[r]) {
                    qMax.pop_back();
                }
                qMax.push_back(r);
                while (!qMin.empty() && arr[qMin.back() >= arr[r]]) {
                    qMin.pop_back();
                }
                qMin.push_back(r);
                r++;
                if (arr[qMax.front()] - arr[qMin.front()] >= k) {
                    break;
                }
            }
            ret += r - l;
            if (qMax.front() == l) {
                qMax.pop_front();
            }
            if (qMin.front() == l) {
                qMin.pop_back();
            }
            l++;
        }
        return ret;
    }
};

void play() {

}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
