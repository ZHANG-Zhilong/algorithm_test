#include <iostream>

using namespace std;

#include <vector>
#include <algorithm>

namespace q01_min_length_for_sort {
    class MinLengthForSort {
    public:
        vector<int> minLengthForSort(vector<int> &arr) {
            if (arr.size() < 1) {
                return {};
            }
            int lmax = 0, rmin = arr.size() - 1;
            int posr = 0, posl = 0;
            for (int i = 0; i < arr.size(); i++) {
                if (arr.at(i) < arr.at(lmax)) {
                    posr = i;
                } else {
                    lmax = i;
                }
            }

            for (int i = arr.size() - 1; i >= 0; i--) {
                if (arr.at(i) > arr.at(rmin)) {
                    posl = i;
                } else {
                    rmin = i;
                }
            }
            sort(arr.begin() + posl, arr.begin() + posr + 1);
            return arr;
        }
    };

    void play() {
        vector<int> play0 = {1, 2, 4, 7, 10, 11, 7, 12, 6, 7, 16, 18, 19};
        vector<int> play = {1, 2, 5, 4, 2, 7, 6, 8, 9};
        vector<int> play1 = {3, 4, 5, 6, 7, 1, 2, 3};
        MinLengthForSort mlfs;
        auto m = mlfs.minLengthForSort(play1);
        for (auto n : m) {
            cout << n << " ";
        }
        cout << endl;
    }
}

#include <vector>
#include <array>

namespace q02_smallest_unformed_sum {
    //arr中均为正数
    //背包问题，从左往右的尝试模型，他之前怎么样，他自己怎么决策，往下推。
    class SmallestUnformedSum {
    public:
        int smallestUnformedSum(const vector<int> &arr) {
            //check input
            if (arr.size() < 1) {
                return -1;
            }
            int arrmin = INT32_MAX, arrsum = 0;
            for (int i = 0; i < arr.size(); i++) {
                arrmin = arrmin < arr.at(i) ? arrmin : arr.at(i);
                arrsum += arr.at(i);
            }
            vector<vector<bool>> dp(arr.size(), vector<bool>(arrsum + 1, false));
            dp[0][arr.at(0)] = true;
            for (int i = 0; i < dp.size(); i++) {
                dp[i][0] = true;
            }

            for (int i = 1; i < dp.size(); i++) {
                for (int j = 1; j < dp[0].size(); j++) {
                    if (dp[(size_t) i - 1][j] || j - arr[i] >= 0 && dp[(size_t) i - 1][(size_t) j - arr[i]]) {
                        dp[i][j] = true;
                    }
                }
            }
            for (int i = arrmin; i < dp[0].size(); i++) {
                if (dp[dp.size() - 1][i] == false) {
                    return i;
                }
            }
            return arrsum + 1;
        }

        int smallestUnformedSumMAGIC(vector<int> &arr) {
            if (arr.size() < 1) {
                return -1;
            }
            //假设数组被排序，并且其中含有元素1，确保range搞定的范围是连续的空间，没有空洞
            //range means 0~i范围内可以搞定0~rang范围的数例如
            //arr.at(i)为x
            //x为20， range为20，x=range+1, x+range可以搞定0(1)~x+range范围内的数
            //那么当x>range+1的时候，x为22，range为20，搞不定21
            stable_sort(arr.begin(), arr.end());
            int range = 1;
            for (int i = 1; i < arr.size(); i++) {
                if (arr.at(i) <= range + 1) {
                    range += arr.at(i);
                } else {
                    return range + 1;
                }
            }
            return range + 1;
        }
    };

    void play() {
        vector<int> arr{2, 5, 3, 9, 1};
        SmallestUnformedSum sus;
        cout << sus.smallestUnformedSum(arr) << endl;
        cout << sus.smallestUnformedSumMAGIC(arr) << endl;
    }
}

#include <vector>

namespace q03_min_patches {
    class MinPatches {
    public:
        //arr有序且且为正数
        //touch只要有变化，就看他有没有完成总目标
        int minPatches(const vector<int> &arr, int range) {
            if (range < 0) {
                return -1;
            }
            long touch = 0;  // [1,touch]
            int patches = 0; //需要额外数组的个数

            //use arr element economically
            for (int i = 0; i < arr.size(); i++) {
                //[1，touch]
                //arr.at(i)
                //[1, arr.at(i)]
                while (arr.at(i) > touch + 1) { // [1，arr.at(i)-1]
                    touch += touch + 1;     //lack element is {touch+1}
                    patches++;
                    if (touch > range) {
                        return patches;
                    }
                }
                touch += arr.at(i);
                if (touch > range) {
                    return patches;
                }
            }
            while (range >= touch + 1) {
                touch += touch + 1;
                patches++;
            }
            return patches;

        }
    };

    void play() {
        vector<int> arr{};
        int k1 = 10;
        vector<int> arr1{5, 2, 7, 9, 3, 3};
        int k2 = 100;

        MinPatches mp;
        cout << mp.minPatches(arr, 20) << endl;
        cout << mp.minPatches(arr1, 20) << endl;


    }
}


#include <memory>
#include <vector>
#include <unordered_map>
#include <algorithm>

namespace q04_largest_component_size_by_common_factor {

    class Node {
    public:
        int value;

        bool operator==(const Node &n2) const {
            return this->value == n2.value;
        }

        bool operator!=(const Node &n2) const {
            return !(*this == n2);
        }
    };

    struct hashNode {
        size_t operator()(const Node &node) const {
            //return node.value;
            return hash<int>()(node.value);
        }
    };

    struct equalNode {
        bool operator()(const Node &n1, const Node &n2) const {
            return n1.value == n2.value;
        }
    };

    class UnionFindSet {
    public:
        //node key 的父亲节点是  node value
        unordered_map<int, int> fatherMap;
        unordered_map<int, int> rankMap;
    public:
        void makeSets(vector<int> nodes) {
            fatherMap.clear();
            rankMap.clear();
            for (auto n : nodes) {
                fatherMap[n] = n;
                rankMap[n] = 1;
            }
        }

        int findFather(int node) {  //递归找父亲，同时打平一长串
            int father = fatherMap.find(node)->second;
            if (node != father) {
                father = findFather(father);
            }
            fatherMap[node] = father;
            return father;
        }

        void unionSet(int a, int b) {  //把小的代表结点挂到大的代表结点上面
            //把两个元素所在的集合，连同
            int &&fa = findFather(a);
            int &&fb = findFather(b);
            if (fa != fb) {
                int fasiz = rankMap.find(fa)->second;
                int fbsiz = rankMap.find(fb)->second;
                if (fasiz < fbsiz) {
                    fatherMap[fa] = fb;
                    rankMap[fb] = fasiz + fbsiz;
                } else {
                    fatherMap[fb] = fa;
                    rankMap[fa] = fasiz + fbsiz;
                }
            }
        }

        bool isSameSet(int a, int b) {
            //return findFather(a).value== findFather(b).value;
            return findFather(a) == findFather(b);
        }
    };

    class UnionFindSet2 {
    public:
        //node key 的父亲节点是  node value
        unordered_map<int, int> fatherMap;
        unordered_map<int, int> rankMap;
    public:
        void makeSets(int size) {
            fatherMap.clear();
            rankMap.clear();
            for (int i = 0; i < size; i++) {
                fatherMap[i] = i;
                rankMap[i] = 1;
            }
        }

        int findFather(int node) {  //递归找父亲，同时打平一长串
            int father = fatherMap.find(node)->second;
            if (node != father) {
                father = findFather(father);
            }
            fatherMap[node] = father;
            return father;
        }

        void unionSet(int a, int b) {  //把小的代表结点挂到大的代表结点上面
            //把两个元素所在的集合，连同
            int &&fa = findFather(a);
            int &&fb = findFather(b);
            if (fa != fb) {
                int fasiz = rankMap.find(fa)->second;
                int fbsiz = rankMap.find(fb)->second;
                if (fasiz < fbsiz) {
                    fatherMap[fa] = fb;
                    rankMap[fb] = fasiz + fbsiz;
                } else {
                    fatherMap[fb] = fa;
                    rankMap[fa] = fasiz + fbsiz;
                }
            }
        }

        bool isSameSet(int a, int b) {
            //return findFather(a).value== findFather(b).value;
            return findFather(a) == findFather(b);
        }

        int maxSize() {
            int maxsiz = INT32_MIN;
            for (auto n : fatherMap) {
                maxsiz = max(maxsiz, rankMap[n.second]);
            }
            return maxsiz;
        }

    };

    class LargestComponentSizeByCommonFactor {
    private:
        int gcd(int a, int b) {
            return b == 0 ? a : gcd(b, a % b);
        }

    public:
        int largestComponentSize(const vector<int> &arr) {
            if (arr.size() < 1) {
                return -1;
            }

            UnionFindSet2 ufs;
            int len = arr.size();
            ufs.makeSets(len);

            for (int i = 0; i < arr.size(); i++) {
                for (int j = i; j < arr.size(); j++) {
                    if (gcd(arr.at(i), arr.at(j)) > 1) {
                        ufs.unionSet(i, j);
                    }
                }
            }
            return ufs.maxSize();
        }
    };

    //数组中没有1值
    void play() {
        vector<int> t{1, 2, 4, 5, 8};
        LargestComponentSizeByCommonFactor lcscf;
        cout << lcscf.largestComponentSize(t) << endl;
    }
}


#include <vector>
#include <queue>

namespace q05_max_length_covers {
    class Line {
    public:
        int start;
        int end;

        Line(int start, int end) {
            this->start = start;
            this->end = end;
        }
    };

    class MaxLengthCovers {
    private:
        struct compLine {
            bool operator()(const Line &l1, const Line &l2) const {
                return l1.start > l2.start;
            }
        };

    public:
        int maxLengthCovers(const vector<int> &arr) {
            if (arr.size() < 1 || ((arr.size() & 1) == 1)) {
                return -1;
            }

            priority_queue <Line, vector<Line>, compLine> minStartHeap;
            priority_queue<int, vector<int>, greater<int>> minEndHeap;
            int len = arr.size();
            for (int i = 0; i < len / 2; i++) {
                minStartHeap.push(Line(arr.at(2 * i), arr.at(2 * i + 1)));
            }


            int retval = 0;
            while (!minStartHeap.empty()) {
                auto line = minStartHeap.top();
                minStartHeap.pop();
                if (minEndHeap.empty()) {
                    minEndHeap.push(line.end);
                } else {
                    while (!minEndHeap.empty() && minEndHeap.top() <= line.start) {
                        minEndHeap.pop();
                    }
                    minEndHeap.push(line.end);
                    retval = retval > minEndHeap.size() ? retval : minEndHeap.size();
                }
            }
            return retval;
        }
    };

    void play() {
        vector<int> arr = {1, 7, 1, 9, 5, 10, 2, 13, 1, 4};
        MaxLengthCovers mlc;

        int len = mlc.maxLengthCovers(arr);
        cout << "the result is:" << len << endl;
    }
}

int main() {
    //q01_min_length_for_sort::play();
    //q02_smallest_unformed_sum::play();
    //q03_min_patches::play();
    q05_max_length_covers::play();


    std::cout << "\nHello World!\n";
    return 0;
}
