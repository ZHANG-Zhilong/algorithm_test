#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <queue>
#include<unordered_map>
#include <algorithm>

using namespace std;

//only positive element.
int getMaxLength(vector<int> arr, int aim) {
    if (aim < 0 || arr.empty()) {
        return -1;
    }
    int L = 0, R = 0, maxLen = 0;
    int sum = arr.at(0);
    while (R < arr.size()) {
        if (sum == aim) {
            maxLen = max(maxLen, R - L + 1);
            sum -= arr[L++];
        } else if (sum < aim) {
            // sum += arr[++R];  ERR
            R++;
            if (R >= arr.size()) {
                break;
            }
            sum += arr[R];
        } else {  //sum>aim
            sum -= arr[L++];
        }
    }
    return maxLen;
}

class LongestSubArrayLessSumAwesomeSolution {
public:
    int maxLengthAwesome(vector<int> arr, int aim) {
        if (arr.empty()) {
            return 0;
        }
        vector<int> sums(arr.size(), 0);
        vector<int> ends(arr.size(), 0);
        sums.at(arr.size() - 1) = arr.at(arr.size() - 1);
        ends.at(arr.size() - 1) = arr.size() - 1;

        for (int i = arr.size() - 2; i >= 0; i--) {
            if (sums.at(i + 1) < 0) {
                sums.at(i) = arr.at(i) + sums.at(i + 1);
                ends.at(i) = ends.at(i + 1);
            } else {
                sums.at(i) = arr.at(i);
                ends.at(i) = i;
            }
        }

        int R = 0;
        int sum = 0;
        int len = 0;
        for (int start = 0; start < arr.size(); start++) {
            while (R < arr.size() && sum + sums.at(R) <= aim) {  //向右扩的逻辑
                sum += sums.at(R);
                R = ends.at(R) + 1;  //扩不动的边界的下一个
            }
            sum -= R > start ? arr.at(start) : 0;  //扩不动的逻辑
            len = max(len, R - start);
            R = max(R, start + 1);
        }
        return len;
    }
};


int main() {
    vector<int> arr = {5, 3, 4, 1, 1, 1, 1};
    cout << getMaxLength(arr, 4) << endl;  //4

    vector<int> arr2 = {100, 200, 7, -6, -3, 300};
    LongestSubArrayLessSumAwesomeSolution awesome;
    cout << awesome.maxLengthAwesome(arr2, 7) << endl; //3
    system("pause");
    return 0;
}
