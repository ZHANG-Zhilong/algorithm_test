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

//求直方图中最大矩形面积
int maxRecFromBottom(vector<int> height) {
    if (&height == nullptr || height.empty()) {
        return 0;
    }
    int maxArea = 0;
    stack<int> singleStack;
    for (int i = 0; i < height.size(); i++) {
        while (!singleStack.empty() && height[i] < height[singleStack.top()]) {
            int j = singleStack.top();
            singleStack.pop();
            int k = singleStack.empty() ? -1 : singleStack.top();
            int currArea = height[j] * (i - k - 1);
            maxArea = max(currArea, currArea);
        }
        singleStack.push(i);
    }

    while (!singleStack.empty()) {
        int j = singleStack.top();
        singleStack.pop();
        int k = singleStack.empty() ? -1 : singleStack.top();
        int currArea = (height.size() - k - 1) * height[j];
        maxArea = max(currArea, maxArea);
    }
    return maxArea;
}

int maxRecSize(vector<vector<int>> map) {
    if (&map == nullptr || map.size() < 1 || map[0].size() < 1) {
        return 0;
    }
    vector<int> help(map[0].size(), 0);
    int maxArea = INT_MIN;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            help[j] = map[i][j] == 0 ? 0 : help[j] + 1;
        }
        maxArea = max(maxArea, maxRecFromBottom(help));
    }
    return maxArea;
}

int main() {


    system("pause");
    return 0;
}
