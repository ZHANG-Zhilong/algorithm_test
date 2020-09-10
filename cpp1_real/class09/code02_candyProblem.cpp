#include <iostream>
#include <vector>

using namespace std;

class CandyProblem {
public:
    static vector<int> candy1(const vector<int> &arr) {
        if (arr.empty()) {
            cout << "Input array is empty" << endl;
            return {};
        }
        vector<int> arrLeft(arr.size(), 0);
        vector<int> arrRight(arr.size(), 0);
        arrLeft.front() = 1;
        arrRight.back() = 1;
        for (int i = 1; i < arr.size(); i++) {
            arrLeft[i] = arr[i] > arr[i - 1] ? arrLeft[i - 1] + 1 : 1;
        }
        for (int i = arr.size() - 2; i >= 0; i--) {
            arrRight[i] = arr[i] > arr[i + 1] ? arrRight[i + 1] + 1 : 1;
        }
        for (int i = 0; i < arr.size(); i++) {
            arrLeft[i] = max(arrLeft[i], arrRight[i]);
        }
        return arrLeft;
    }

    static vector<int> candy2(const vector<int> &arr) {
        if (arr.empty()) {
            cout << "Input array is empty." << endl;
            return {};
        }
        vector<int> arrLeft(arr.size(), 0);
        vector<int> arrRight(arr.size(), 0);
        arrLeft.front() = 1;
        arrRight.back() = 1;
        for (int i = 1; i < arr.size(); i++) {
            int diff = arr[i] - arr[i - 1];
            if (diff == 0) {
                arrLeft[i] = arrLeft[i];
            } else if (diff > 0) {
                arrLeft[i] = arrLeft[i - 1] + 1;
            } else {
                arrLeft[i] = 1;
            }
        }
        for (int i = arr.size() - 2; i >= 0; i--) {
            int diff = arr[i] - arr[i + 1];
            if (diff == 0) {
                arrRight[i] = arrRight[i + 1];
            } else if (diff > 0) {
                arrRight[i] = arrRight[i + 1] + 1;
            } else {
                arrRight[i] = 1;
            }
        }
        for (int i = 0; i < arr.size(); i++) {
            arrLeft[i] = max(arrLeft[i], arrRight[i]);
        }
        return arrLeft;
    }

    static void printArr(const vector<int> &arr) {
        int sumValue = 0;
        for (const auto &n : arr) {
            sumValue += n;
            cout << n << " ";
        }
        cout << endl;
        cout << sumValue << endl << endl;
    }
};

void playCandy() {
    vector<int> arr{3, 0, 5, 5, 4, 4, 0};
    auto rst1 = CandyProblem::candy1(arr);
    CandyProblem::printArr(rst1);
    auto rst2 = CandyProblem::candy2(arr);
    CandyProblem::printArr(rst2);
}

int main(int argc, char *argv[]) {
    playCandy();
    return 0;
}


