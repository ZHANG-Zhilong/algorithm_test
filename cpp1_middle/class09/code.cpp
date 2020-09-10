#include <iostream>

using namespace std;

#include <memory>
#include <unordered_map>

namespace q01_lru {

    template<typename K, typename V>
    class Node {
    public:
        K key;
        V value;
        shared_ptr<Node<K, V>> pre;
        shared_ptr<Node<K, V>> next;

        Node(K key, V value) {
            this->key = key;
            this->value = value;
            pre = nullptr;
            next = nullptr;
        }
    };

    template<typename K, typename V>
    class DoubleLinkedList {
    private:
        shared_ptr<Node<K, V>> head;
        shared_ptr<Node<K, V>> tail;
    public:
        DoubleLinkedList() {
            head = nullptr;
            tail = nullptr;
        }

        void addNode(shared_ptr<Node<K, V>> node) {
            if (node == nullptr) { return; }
            if (head == nullptr) {
                head = node;
                tail = node;
            } else {
                tail->next = node;
                node->pre = tail;
                node->next = nullptr;
                tail = node;
            }
        }

        void moveNodeToTail(shared_ptr<Node<K, V>> node) {
            if (node == tail || node == nullptr) {
                return;
            } else if (node == head) {
                head = head->next;
                head->pre = nullptr;
                node->next = nullptr;
                addNode(node);
            } else {
                node->pre->next = node->next;
                node->next->pre = node->pre;
                node->next = nullptr;
                addNode(node);
            }
        }

        shared_ptr<Node<K, V>> removeHead() {
            if (head == nullptr) {
                return nullptr;
            } else {
                auto node = head;
                if (head->next) {
                    head = head->next;
                    head->pre = nullptr;
                    node->next = nullptr;
                } else {   //双向链表中只有一个原元素，头尾元素相同
                    head = nullptr;
                    tail = nullptr;
                }
                return node;
            }
        }

        void print() {
            auto node = head;
            while (node) {
                cout << "Key: " << node->key << "  Value: " << node->value << endl;
                node = node->next;
            }
            cout << endl;
        }
    };

    template<typename K, typename V>
    class MyCache {
    private:
        unordered_map<K, shared_ptr<Node<K, V>>> keyNodeMap;
        DoubleLinkedList<K, V> cacheList;
        int capacity;
    public:
        MyCache(int capacity) {
            if (capacity < 3) {
                capacity = 3;
            }
            this->capacity = capacity;
        }

        V getValue(K key) {
            if (keyNodeMap.count(key) == 0) {
                return NULL;
            } else {
                Node<K, V> rst = keyNodeMap.find(key);
                rst.value;
            }
        }

        void set(K key, V value) {
            if (keyNodeMap.count(key) == 0) {
                auto node = make_shared<Node<K, V>>(key, value);
                cacheList.addNode(node);
                keyNodeMap.insert(make_pair(key, node));
            } else {
                auto nodeptr = keyNodeMap.find(key);

                nodeptr->second->value = value;
                cacheList.moveNodeToTail(nodeptr->second);
            }
            if (keyNodeMap.size() == capacity + 1) {
                removeMostUnUsedCache();
            }
        }

        void print() {
            cacheList.print();
        }

    private:
        void removeMostUnUsedCache() {
            auto node = cacheList.removeHead();
            keyNodeMap.erase(keyNodeMap.find(node->key));
        }

    };


    void play() {
        /* DoubleLinkedList<int, int> dl;
        shared_ptr<Node<int, int>> mp;
        for (int i = 0; i < 4; i++) {
            auto node = make_shared <Node<int, int >> (i, i + 1);
            dl.addNode(node);
            if (i == 1)  mp = node;
        }
        dl.print();
        dl.removeHead();
        dl.print();
        dl.moveNodeToTail(mp);
        dl.print();*/

        MyCache<char, int> mc(4);
        mc.set('a', 1);
        mc.print();

        mc.set('b', 2);
        mc.print();

        mc.set('c', 3);
        mc.print();

        mc.set('d', 4);
        mc.print();

        mc.set('d', 5);
        mc.print();

        mc.set('g', 6);
        mc.print();

        mc.set('h', 7);
        mc.print();


        mc.print();
        mc.print();

    }
}

#include <vector>
#include <algorithm>

namespace q02_roll_cover {
    //绳子最多覆盖几个点,数组有序，每一个点代表其所在の位置，表示从左往右有哪些点，用绳子去盖点，最多可盖几个点
    //数轴上从左到右有n个点，a[0] ,a[1],…,a[n-1]，给定一根长度为L绳子，求绳子最多覆盖其中几个点？
    //窗口更新
    class RollCover {
    public:
        int rollCover1(vector<int> &vec, int L) {
            if (vec.empty()) {
                return vec.size();
            }
            int retval = 0;
            int l = 0, r = 0;
            while (r < vec.size()) {
                if (vec.at(r) - vec.at(l) < L) {
                    r++;
                } else {
                    retval = max(retval, r - l);
                    l++;
                }
            }
            return retval;
        }

    };

    void play() {
        vector<int> tst{3, 5, 12, 16, 39};
        RollCover rc;
        cout << rc.rollCover1(tst, 10);
    }
}

#include <vector>
#include <unordered_map>

namespace q02_max_points_one_line {

    //分情况讨论问题，并进行处理
    //维护一个二级表，格外处理斜率的问题（最简形式）
    //提前想好测试案例，处理好极端输入情况，逻辑明确，先写框架
    class LineCrossPoint {
    private:
        unordered_map<int, unordered_map<int, int>> ktables;

        inline int gcd(int a, int b) {
            return b == 0 ? a : gcd(b, a % b);
        }

    public:
        int MaxPointsOneLine(vector<int> &vec) {
            if (vec.size() < 1 || (vec.size() & 1) == 1) {
                cout << "invalid input" << endl;
                return -1;
            }
            int retval = 0;
            int len = vec.size() / 2;
            for (int j = 0; j < len; j++) {
                int x0 = vec.at(2 * j);
                int y0 = vec.at(2 * j + 1);
                int same = 0, k0 = 0, k00 = 0, k = 0;  //same position, k==0, k==infinite, k= other
                ktables.clear();
                for (int i = j; i < len; i++) {
                    int x = vec.at(2 * i) - x0;
                    int y = vec.at(2 * i + 1) - x0;
                    if (x == 0 && y == 0) {
                        same++;
                    } else if (y == 0) {
                        k00++;
                    } else if (x == 0) {
                        k0++;
                    } else {
                        int ggcd = gcd(x, y);
                        x /= ggcd;
                        y /= ggcd;
                        ktables[x][y]++;
                        k = max(k, ktables[x][y]);
                    }
                    retval = max({k, k0, k00}) + same;
                }
            }
            return retval;
        }
    };

    void play() {
        vector<int> test1{0, 0, 1, 1, 2, 1};  //ans=2
        vector<int> test2{0, 0, 1, 1, 2, 1, 2, 2};  //ans = 3
        vector<int> test3{0, 0};  //ans=1
        LineCrossPoint lcp;
        cout << lcp.MaxPointsOneLine(test3) << endl;
    }
}

#include <vector>

namespace q03_jump_game {
    //列表中元素值代表本次可跳跃的最大步数
    //目标是跳跃到终点位置
    //分为两个区域，当前步数范围内可达区域，本区域内可达下一区域最大值
    class JumpGame {
    public:
        int jumpGame(vector<int> &vec) {
            if (vec.empty()) {
                return -1;
            }
            //cur jump步内右边界，next jump+1步内右边界
            int cur = 0, jump = 0, next = 0;
            for (int i = 0; i < vec.size(); i++) {
                if (i > cur) {
                    cur = next;
                    jump++;
                }
                next = max(next, i + vec.at(i));
            }
            return jump;
        }

    };

    void play() {
        vector<int> vec{3, 6, 1, 1, 1, 1, 1, 9, 1, 1};
        vector<int> vec2{1};
        JumpGame jp;
        cout << jp.jumpGame(vec2) << endl;
    }
}

#include <memory>
#include <queue>
#include <vector>
#include <algorithm>

namespace q04_top_sum_cross_two_arrays {
    //O(K*log(K))
    //类似广度优先，但不完全是。大根堆弹出元素，压入弹出元素的左侧、右侧元素（如有），同时不重复压入
    class Node {
    public:
        int index1;
        int index2;
        int sum;

        Node(int index1, int index2, int sum) {
            this->index1 = index1;
            this->index2 = index2;
            this->sum = sum;
        }
    };

    class TopSumCrossTwoArrays {
    private:
        struct comp {
            bool operator()(const shared_ptr<Node> n1, const shared_ptr<Node> n2) const {
                return n1->sum < n2->sum;
            }
        };

        priority_queue<shared_ptr<Node>,
                vector<shared_ptr<Node>>,
                comp> maxHeap;

    public:

        vector<int> topKSum(const vector<int> &arr1, const vector<int> &arr2, int topK) {
            if (arr1.empty() || arr2.empty() || topK < 1) {
                return {};
            }
            int len = arr1.size() * arr2.size();
            topK = min(topK, len);

            int index1 = arr1.size() - 1;
            int index2 = arr2.size() - 1;
            maxHeap.push(make_shared<Node>(index1, index2, arr1.at(index1) + arr2.at(index2)));
            vector<int> retval(topK, 0);

            vector<vector<bool>> entered(arr1.size(), vector<bool>(arr2.size(), false));  // false never pushed.
            //enter only once.
            //  3,4,5
            //  4,5,6
            entered.at(arr1.size() - 1).at(arr2.size() - 1) = true;

            for (int i = 0; i < topK; i++) {
                shared_ptr<Node> curNode = maxHeap.top();
                maxHeap.pop();
                retval.at(i) = curNode->sum;

                int i1 = curNode->index1;
                int i2 = curNode->index2;

                if (i1 - 1 >= 0 && !entered[i1 - 1][i2]) {
                    maxHeap.push(make_shared<Node>(i1 - 1, i2, arr1.at(i1 - 1) + arr2.at(i2)));
                    entered[i1 - 1][i2] = true;
                }
                if (i2 - 1 >= 0 && !entered[i1][i2 - 1]) {
                    maxHeap.push(make_shared<Node>(i1, i2 - 1, arr1.at(i1) + arr2.at(i2 - 1)));
                    entered[i1][i2 - 1] = true;
                }
            }
            return retval;
        }

    };

    void play() {
        vector<int> arr1{1, 2, 3};
        vector<int> arr2{2, 3};
        TopSumCrossTwoArrays tscta;
        auto rst = tscta.topKSum(arr1, arr2, 20);
        for (auto n : rst) {
            cout << n << endl;
        }
    }
}

#include <vector>
#include <unordered_map>

namespace q05_split_4parts {
    class Split4Parts {
    public:
        bool split4Parts(const vector<int> &arr) {
            if (arr.size() < 7) {
                return false;
            }
            //array elements are positive values. presum is not repeated
            unordered_map<int, int> preSum;  // sum, index
            int arrSum = 0;
            for (int i = 0; i < arr.size(); i++) {
                preSum[arrSum] = i;
                arrSum += arr.at(i);  // not include i
            }
            int checkSum = 0;
            int lsum = 0;
            for (int s1 = 1; s1 < arr.size() - 5; s1++) {
                lsum += arr.at(s1 - 1);  //s1 is the first knife pos.
                checkSum = lsum + arr.at(s1) + lsum;
                auto ite1 = preSum.find(checkSum);
                if (ite1 != preSum.end()) {
                    int s2 = ite1->second;
                    checkSum = ite1->first + arr[s2] + lsum;
                    auto ite2 = preSum.find(checkSum);
                    if (ite2 != preSum.end()) {
                        int s3 = ite2->second;
                        checkSum = ite2->first;
                        if (checkSum + arr.at(s3) + lsum == arrSum) {
                            return true;
                        }
                    }
                }
            }

            return false;
        }
    };

    void play() {
        vector<int> vec{3, 2, 4, 1, 4, 9, 5, 10, 1, 2, 2};
        vector<int> vec3{1, 3, 2, 4, 1, 4, 9, 5, 10, 1, 2, 2};
        vector<int> vec2{10, 1, 2, 2};
        Split4Parts s4p;
        vector<int> kni;
        cout << (bool) s4p.split4Parts(vec3) << endl;
        cout << (bool) s4p.split4Parts(vec) << endl;
    }
}

#include <vector>

namespace q06_string_cross {

    class StringCross {
    public:
        bool stringCross(const string &str1, const string &str2, const string &aim) {
            if (str1.size() + str2.size() != aim.size() ||
                aim.size() < 1 ||
                str1.size() < 1 && str2.size() < 1) {
                return false;
            }
            vector<vector<bool>> dp(str1.size() + 1, vector<bool>(str2.size() + 1, false));
            dp[0][0] = true;
            for (int i = 1; i < dp.size(); i++) {
                if (str1[i - 1] != aim[i - 1]) {
                    break;
                }
                dp[i][0] = true;
            }
            for (int j = 1; j < dp[0].size(); j++) {
                if (str2[j - 1] != aim[j - 1]) {
                    break;
                }
                dp[0][j] = true;
            }
            for (int i = 1; i < dp.size(); i++) {
                for (int j = 1; j < dp[0].size(); j++) {
                    if (dp[i - 1][j] && aim[i + j - 1] == str1[i - 1] ||
                        dp[i][j - 1] && aim[i + j - 1] == str2[j - 1]) {
                        dp[i][j] = true;
                    }
                }
            }
            return dp[str1.size()][str2.size()];
        }
    };

    void play() {

        string str1 = "1234";
        string str2 = "abcd";
        string aim = "1a2bcd34";
        StringCross sc;
        cout << sc.stringCross(str1, str2, aim) << endl;
    }
}

int main() {

    //q01_lru::play();
    //q02_roll_cover::play();
    //q02_max_points_one_line::play();
    //q03_jump_game::play();
    //q04_top_sum_cross_two_arrays::play();
    //q05_split_4parts::play();
    //q06_string_cross::play();

    std::cout << "\nHello World!\n";
    return 0;
}
