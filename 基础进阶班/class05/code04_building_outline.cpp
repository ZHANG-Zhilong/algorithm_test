#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <map>
#include <algorithm>

using namespace std;

constexpr bool UP = true;
constexpr bool DOWN = false;

class Node {
public:
    bool isUp;
    int posi;
    int height;

    Node(int pos, int h, bool up) {
        posi = pos;
        height = h;
        isUp = up;
    }

    Node() {
        posi = 0;
        height = 0;
        isUp = UP;
    }

    bool operator()(const Node &n1, const Node &n2) const {
        return n1.posi < n2.posi;
    }
};

//buildings   pos_start, pos_end, building_height
class Building {
private:
    struct SortNode {
        bool operator()(const Node &n1, const Node &n2) const {
            if (n1.posi != n2.posi) {
                return n1.posi < n2.posi;
            } else {
                return n1.isUp;
            }
        }
    } SortNode;

public:
    vector<vector<int>> buildOutline(vector<vector<int>> buildings) {
        vector<Node> nodes(buildings.size() * 2);
        for (int i = 0; i < buildings.size(); i++) {
            nodes.at(i * (size_t) 2) = Node(buildings[i][0], buildings[i][2], UP);
            nodes.at(i * (size_t) 2 + 1) = Node(buildings[i][1], buildings[i][2], DOWN);
        }
        sort(begin(nodes), end(nodes), SortNode);
        map<int, int, greater<int>> htmap;  //height, count
        map<int, int> pmmap;  //heightest, pos
        for (int i = 0; i < nodes.size(); i++) {
            int height = nodes[i].height;
            if (nodes[i].isUp == UP) {
                if (htmap.count(height) == 0) {
                    htmap.insert(pair<int, int>(height, 1));
                } else {
                    htmap[height]++;
                }
            } else {
                if (htmap.count(height) > 0) {
                    if (htmap[height] == 1) {
                        htmap.erase(height);
                    } else {
                        htmap[height]--;
                    }
                }
            }
            if (htmap.empty()) {
                pmmap.insert(pair<int, int>(nodes[i].posi, 0));
            } else {
                pmmap.insert(pair<int, int>(nodes[i].posi, htmap.begin()->first));
            }
        }

        vector<vector<int>> rst;
        int preHeight = 0;
        int start = 0, end = 0;
        for (auto node : pmmap) {
            int curPosition = node.first;
            int curMaxHeight = node.second;
            if (preHeight != curMaxHeight) {
                if (preHeight != 0) {
                    end = curPosition;
                    vector<int> tmp = {start, end, preHeight};
                    rst.push_back(tmp);
                }
                start = curPosition;  //每一次currentMaxHeight发生变化的时候都更新数据
                preHeight = curMaxHeight;
            }
        }
        return rst;
        //要清楚的明白，想清楚ifelse的分支都意味着什么

        //if (preHeight != curMaxHeight) {
        //    if (preHeight == 0) {  //意味着当curMaxHeight发生变化时且preheight为0时才更新数据
        //        start = curPosition;
        //        preHeight = curMaxHeight;
        //    }
        //    else {
        //        end = curPosition;
        //        vector<int> tmp = { start, end, preHeight };
        //        rst.push_back(tmp);
        //    }
        //}
    }

};

//大楼轮廓问题
int main() {
    vector<vector<int>> myv = {{1, 6,  4},
                               {2, 4,  3},
                               {5, 8,  5},
                               {7, 10, 3}};
    Building building;

    vector<vector<int>> rst = building.buildOutline(myv);

    // [[2, 10], [3, 15], [7, 12], [12, 0], [15, 10], [20, 8], [24, 0]]
    system("pause");
    return 0;
}
