#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <queue>
#include<unordered_map>
#include <algorithm>

using namespace std;

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

int main() {
    vector<int> arr = {5, 3, 4, 1, 1, 1, 1};
    cout << getMaxLength(arr, 4) << endl;
    system("pause");
    return 0;
}
