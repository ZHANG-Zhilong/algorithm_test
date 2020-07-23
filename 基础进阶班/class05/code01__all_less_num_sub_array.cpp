#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

class AllLessNumSubArray {
    int getNum(vector<int> arr, int num) {
        if (arr.empty()) {
            return 0;
        }
        list<int> qmax;
        list<int> qmin;
        int L = 0, R = 0, res = 0;
        while (L < arr.size()) {
            while (R < arr.size()) {
                //min value update structure.
                while (!qmin.empty() && arr[qmin.back()] >= arr[R]) {
                    qmin.pop_back();
                }
                qmin.push_back(R);
                //max value update structure
                while (!qmax.empty() && arr[qmax.back()] <= arr[R]) {
                    qmax.pop_back();
                }
                qmax.push_back(R);
                if (arr[qmax.front()] - arr[qmin.front()] > num) {
                    break;
                }
                R++;
            }
            if (qmax.front() == L) {
                qmax.pop_front();
            }
            if (qmin.front() == L) {
                qmin.pop_front();
            }
            res += R - L;
            L++;

        }
        return res;

    }
};

int main() {


    system("pause");
    return 0;
}
