#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <stack>
#include <algorithm>

using namespace std;

/*
[1,2,4,5,3]  对于环形队列，每一个都代表一个山峰。

1）相邻的山峰可以看见
2）不相邻山峰中两条路径中的值均不大于两山峰最小值的山峰对可以看见。

求可以相互看见的山峰对。
         5   
     /      \
    4        3
     \      /
      2 -- 1


*/

class Pair {
public:
    int value;
    int times;

    Pair(int data) {
        value = data;
        times = 1;
    }

};

class NetEase {
private:
    int nextIndex(int size, int i) {
        return (i < size - 1) ? (i + 1) : 0;
    }

    long getIntegratalSum(int n) {
        return n == 1l ? 0l : ((long) n * ((long) n - 1) / 2l);
    }

public:
    int communication(vector<int> arr) {
        if (arr.size() < 2) {
            return 0;
        }

        int maxIndex = 0;
        int rst = 0;
        int size = arr.size();
        for (int i = 0; i < arr.size(); i++) {
            maxIndex = arr[maxIndex] > arr[i] ? maxIndex : i;
        }
        stack<Pair> monoStack;  //monotone
        monoStack.push(Pair(arr[maxIndex]));
        int index = nextIndex(size, maxIndex);
        while (index != maxIndex) {
            int value = arr[index];
            while (!monoStack.empty() && value > monoStack.top().value) {
                Pair zpair = monoStack.top();
                monoStack.pop();
                int times = zpair.times;
                //rst += getIntegratalSum(times) + times;
                //rst += monoStack.empty() ? 0 : times;
                rst = getIntegratalSum(times) + times * 2;
            }
            if (!monoStack.empty() && monoStack.top().value == value) { //each time check stack.empty()
                monoStack.top().times++;//这里是返回迭代器吗？
            } else {
                monoStack.push(Pair(value));
            }
            index = nextIndex(size, index);
        }

        while (!monoStack.empty()) {
            int times = monoStack.top().times;
            monoStack.pop();
            rst += getIntegratalSum(times);
            if (!monoStack.empty()) {
                rst += times;
                if (monoStack.size() > 1) {
                    rst += times;
                } else {
                    rst += monoStack.top().times > 1 ? times : 0;
                }
            }
        }
        return rst;
    }
};

int main() {
    vector<int> arr = {5, 3, 3, 4, 4, 5};
    NetEase netease;
    cout << netease.communication(arr);

    system("pause");
    return 0;
}
