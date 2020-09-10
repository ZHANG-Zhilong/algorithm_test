#include <iostream>

using namespace std;

#include <unordered_map>
#include <vector>
#include <algorithm>

namespace q01_stickers_spell_words {
    //最少需要几张贴纸
    class StickersSpellWords {
    public:

        //method2->silly cache.
        int minStickers(
                const vector<string> &stickers,
                string &target) {

            //词频统计  map
            vector<vector<int> > stickersMap(stickers.size(), vector<int>(26, 0));
            unordered_map<string, int> dp;

            for (int i = 0; i < stickers.size(); i++) {
                for (char c : stickers[i]) {
                    stickersMap[i][(int64_t) c - 'a']++;  //词频统计
                }
            }
            dp[""] = 0;  //basecase
            return process2(dp, stickersMap, target);
        }

        //dp 傻缓存，如果t已经算过了，直接返回dp中所得值
        //t  剩余的目标
        // 0...N 每一个字符串所含字符词频统计
        //假设每一个字符都是小写字母
        int process2(
                unordered_map<string, int> dp,
                vector<vector<int> > stickersMap,
                string target) {

            if (dp.find(target) != dp.end()) {
                return dp[target];
            }

            int retval = INT32_MAX;

            //目标串词频
            vector<int> tmap(26, 0);
            for (char c : target) {
                tmap[(int64_t) c - 'a']++;  //char frequency.
            }

            for (int i = 0; i < stickersMap.size(); i++) {
                //第i个stickers， 搞定目标串target

                //没有搞定target，假定stickers中
                if (stickersMap[i][(int64_t) target[0] - 'a'] == 0) {
                    continue;
                }

                string rest2;

                for (int j = 0; j < 26; j++) {
                    if (tmap[j] > 0) {  //j位置字符是target需要的
                        for (int k = 0; k < max(0, tmap[j] - stickersMap[i][j]); k++) {  //词频统计上减掉被搞定的字符
                            rest2.push_back((char) 'a' + j);  //目标串被搞定后剩余的字符存入sb中
                        }
                    }
                }

                int tmp = process2(dp, stickersMap, rest2);
                if (tmp != -1) {
                    retval = min(retval, tmp + 1);
                }
            }

            dp[target] = retval == INT32_MAX ? -1 : retval;
            return dp[target];
        }
        //method1->暴力递归
        //rest, changeable param.
        //arr, fixed param
        //return, 搞定rest需要几张贴纸

        int f(string &rest, vector<string> &arr) {
            if (rest.size() < 1) {
                return 0;
            }
            int next = INT32_MAX;
            for (string first : arr) {
                //把在first中搞定的字符，在rest中裁减掉，剩余字符串为rest2
                //int next = min(next, f(rest2, arr));
            }
            return next + 1;
        }


    };

    void play() {
        vector<string> arr;
        arr = {"ba", "c", "abcd"};
        string str = "babac";
        StickersSpellWords ssw;
        cout << ssw.minStickers(arr, str) << endl;

    }
}

//返回matrix中最大递增链长度
#include <algorithm>

namespace q02_longest_increasing_path {
    class LongestIncreasingPath {
    public:
        int maxPath1(vector<vector<int> > &matrix) {
            int maxval = INT32_MIN;
            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix[0].size(); j++) {
                    maxval = max(process1(matrix, i, j), maxval);
                }
            }
            return maxval;
        }

        int maxPath2(vector<vector<int> > &matrix) {
            int maxv = INT32_MIN;
            vector<vector<int> > dp(matrix.size(), vector<int>(matrix[0].size(), 0));
            for (int i = 0; i < matrix.size(); i++) {
                for (int j = 0; j < matrix[0].size(); j++) {
                    maxv = max(process2(matrix, i, j, dp), maxv);
                }
            }
            return maxv;
        }

    private:
        //假设matrix从【i，j】位置出发能够走出的最长递增链
        //暴力递归
        static int process1(vector<vector<int> > &matrix, int i, int j) {

            if (i < 0 || i > matrix.size() || j < 0 || j > matrix[0].size()) {
                return -1;
            }

            int next1 = 0, next2 = 0, next3 = 0, next4 = 0;
            if (i - 1 >= 0 && matrix[i - 1][j] > matrix[i][j]) {
                next1 = process1(matrix, i - 1, j);
            }
            if (i + 1 < matrix.size() && matrix[i + 1][j] > matrix[i][j]) {
                next2 = process1(matrix, i + 1, j);
            }
            if (j - 1 >= 0 && matrix[i][j - 1] > matrix[i][j]) {
                next3 = process1(matrix, i, j - 1);
            }
            if (j + 1 < matrix[0].size() && matrix[i][j + 1] > matrix[i][j]) {
                next4 = process1(matrix, i, j + 1);
            }
            int value = max(max(next1, next2), max(next3, next4)) + 1;
            return value;
        }

        //silly cache
        int process2(vector<vector<int> > &matrix,
                     int i,
                     int j,
                     vector<vector<int> > &dp) {
            if (i < 0 || i > matrix.size() || j < 0 || j > matrix[0].size()) {
                return -1;
            }
            if (dp[i][j] != 0) {
                return dp[i][j];
            }
            int next1 = 0, next2 = 0, next3 = 0, next4 = 0;
            if (i - 1 > 0 && matrix[i - 1][j] > matrix[i][j]) {
                next1 = process1(matrix, i - 1, j);
            }
            if (i + 1 < matrix.size() && matrix[i + 1][j] > matrix[i][j]) {
                next2 = process1(matrix, i + 1, j);
            }
            if (j - 1 > 0 && matrix[i][j - 1] > matrix[i][j]) {
                next3 = process1(matrix, i, j - 1);
            }
            if (j + 1 < matrix[0].size() && matrix[i][j + 1] > matrix[i][j]) {
                next4 = process1(matrix, i, j + 1);
            }

            dp[i][j] = max(max(next1, next2), max(next3, next4)) + 1;
            return dp[i][j];
        }
    };

    void play() {
        vector<vector<int>> matrix{{5, 4, 3},
                                   {3, 1, 2},
                                   {2, 1, 3}};  //ans = 5
        LongestIncreasingPath lip;
        cout << lip.maxPath1(matrix) << endl;
        cout << lip.maxPath2(matrix) << endl;
    }

}

#include <vector>
#include <set>
#include <algorithm>

namespace q03_max_sub_array_sum_less_or_equal_k {
    //子矩阵问题->子数组问题
    //返回距离k最近的子数组累加和
    class MaxSubArraySumLessOrEqualK {
    public:
        //返回arr之子数组中累加和最大的，<=k的子数组
        //arr中数组有正、负、0、不可用双指针
        static int getMaxLessOrEqual(const vector<int> &arr, int k) {
            if (arr.empty()) {
                return -1;
            }
            int sumsub = 0;  //0...i位置前缀累加和
            int maxvalue = INT32_MIN;
            set<int> subset;
            subset.insert(0);  //一个数也没有的累加和为0

            //求解以i位置结尾的，和最大的，<=k的子数组 累加和
            for (int i : arr) {
                sumsub += i;
                //返回首个大于sumsub-k的子数组累加和
                if (subset.upper_bound(sumsub - k) != subset.end()) {
                    int temp = sumsub - *subset.upper_bound(sumsub - k);
                    maxvalue = max(maxvalue, temp);
                }
                subset.insert(sumsub);  //将当前的前缀和添加到set中
            }
            return maxvalue;
        }

        //子矩阵->子数组->压缩子数组
    };


    void play() {
        vector<int> arr{1, 2, 3, 9, 100, 5, 4, 9, 4};
        cout << MaxSubArraySumLessOrEqualK::getMaxLessOrEqual(arr, 20);
    }
}

#include <memory>
#include <list>
#include <unordered_set>

namespace q04_word_serach {

    class TrieNode {
    public:
        int path;  //有多少个字符串划过我
        int end;   //我是多少个字符串的结尾
        vector<shared_ptr<TrieNode>> nexts;  //我有多少条边
    public:
        TrieNode() {
            path = 0;
            end = 0;
            nexts.resize(26);
        }

    };

    class TrieTree {
    public:
        shared_ptr<TrieNode> root;
    public:
        TrieTree() {
            root = make_shared<TrieNode>();
        }

        int insert(string word) {
            if (word.empty()) {
                return -1;
            }
            shared_ptr<TrieNode> node = root;
            int index = 0;
            for (int i = 0; i < word.size(); i++) {
                index = word[i] - 'a';
                if (node->nexts[index] == nullptr) {
                    node->nexts[index] = make_shared<TrieNode>();
                }
                node = node->nexts[index];
                node->path++;
            }
            node->end++;
            return 0;
        }
    };

    class WordSearch {

        //board[row][col]位置的字符出发
        //之前的路径上，走过的字符，记录在path中
        //cur还没有登上，有待检查能不能登上去的前缀树节点
        //如果找到words的某个str，就记录在str中
        //返回值，从row，col出发，一共找到了多少个str
    public:
        int process(
                vector<vector<char>> &board,
                int row, int col,
                string &path,
                shared_ptr<TrieNode> node,
                list<string> &res) {

            char cha = board[row][col];
            if (cha == '\0') {
                return 0;    //this [row, col] has walked
            }
            int index = cha - 'a';
            //if there is no way or the path has been added into res.
            if (node->nexts[index] == nullptr || node->nexts[index]->path == 0) {
                return 0;
            }
            //没有走回头路，并且可以登陆上去
            shared_ptr<TrieNode> cur = node->nexts[index];
            path.push_back(cha);  //当前位置字符添加到path中
            int fix = 0;  //row，col位置连同上下左右四个方向搞定字符串的数量
            if (cur->end > 0) {    //来到[row,col]位置后如果不往后走，已经搞定了多少个字符串
                res.push_back(path);  //-----------------------------
                cur->end--;
                fix++;
            }

            board[row][col] = '\0';

            //上下左右四个方向尝试
            if (row > 0) {
                fix += process(board, row - 1, col, path, cur, res);
            }
            if (row + 1 < board.size()) {
                fix += process(board, row + 1, col, path, cur, res);
            }
            if (col - 1 >= 0) {
                fix += process(board, row, col - 1, path, cur, res);
            }
            if (col + 1 < board.front().size()) {
                fix += process(board, row, col + 1, path, cur, res);
            }
            board[row][col] = cha;
            path.clear();    //here is important.
            cur->path -= fix;   //do not walk the same path in trie tree.
            return fix;
        }

        list<string> findWords(
                vector<vector<char>> &board,
                vector<string> words) {
            //把words添加前缀树中，记录每一个位置出发的答案集合
            TrieTree head;    //Trie Tree
            unordered_set <string> wordSet;
            for (string word : words) {
                if (wordSet.find(word) == wordSet.end()) {
                    head.insert(word);
                    wordSet.insert(word);
                }
            }
            list <string> res;
            //collect word along path, saved into path.
            string path;
            for (int row = 0; row < board.size(); row++) {
                for (int col = 0; col < board.front().size(); col++) {
                    //enum board's each position.
                    //collect answer in every position as home position.
                    process(board, row, col, path, head.root, res);
                }
            }
            return res;
        }
    };

    void play() {

        vector<vector<char>> board = {
                {'o', 'a', 'a', 'n'},
                {'e', 't', 'a', 'e'},
                {'i', 'h', 'k', 'r'},
                {'i', 'f', 'l', 'v'}
        };
        vector<string> words = {"oath", "pea", "eat", "rain"};
        WordSearch ws;
        auto result = ws.findWords(board, words);
        cout << endl;
    }
}

#include <vector>
#include <memory>
#include <algorithm>

namespace q05_binary_tree_height_morris {
    template<typename T>
    class BitNode {
    public:
        shared_ptr<BitNode<T>> left;
        shared_ptr<BitNode<T>> right;
        T value;

        BitNode(T value) {
            this->value = value;
        }
    };

    template<typename T>
    class MinHeight {
    public:
        int minHeight1(shared_ptr<BitNode<T>> head) {
            if (head == nullptr) {
                return 0;
            }
            return process(head);
        }

        int minHeight2(shared_ptr<BitNode<T>> head) {
            if (head == nullptr) {
                return 0;
            }
            return process2(head, 1);
        }

        int minHeight3(shared_ptr<BitNode<T>> head) {
            if (head == nullptr) {
                return 0;
            }
            return process3morris(head);
        }

    private:
        //递归遍历
        int process(shared_ptr<BitNode<T> > head) {

            //把叶子节点作为basecase
            if (head->left == nullptr && head->right == nullptr) {
                return 1;
            }

            //左右子树不都为空
            int leftHeight = 0;
            int rightHeight = 0;

            if (head->left != nullptr) {
                leftHeight = process(head->left);
            }
            if (head->right != nullptr) {
                rightHeight = process(head->right);
            }

            return 1 + min(rightHeight, leftHeight);  //自己还占一层
        }

        //分治
        int process2(shared_ptr<BitNode<T>> head, int level) {
            if (head->left == nullptr && head->right == nullptr) {
                return level;
            }
            int retval = INT32_MAX;
            if (head->left != nullptr) {
                retval = min(process2(head->left, level + 1), retval);
            }
            if (head->right != nullptr) {
                retval = min(process2(head->right, level + 1), retval);
            }
            return retval;
        }

        //morris
        int process3morris(shared_ptr<BitNode<T>> head) {
            //return min height of the leaf-nodes.
            //分清楚逻辑关系，怎样在morris遍历过程中得到每一个节点的的正确层数
            //第一次来到节点 level++
            //第二次来到 level-左子树右边界节点数量
            //只来到一次 level++
            //判断叶子节点的时机：第二次来到节点，其左子树最右节点的左孩子为空
            if (head->left == nullptr && head->right == nullptr) {
                return 1;
            }
            shared_ptr<BitNode<T>> cur = head, mostRight = nullptr;
            int curLevel = 0, minHeight = INT32_MAX;
            while (cur != nullptr) {
                mostRight = cur->left;
                if (mostRight != nullptr) {
                    int leftHeight = 1;  //左子树有边界数量  left subtree right-boundary node counts.
                    while (mostRight->right != nullptr && mostRight->right != cur) {
                        leftHeight++;
                        mostRight = mostRight->right;
                    }
                    if (mostRight->right == nullptr) {  //第一次到达
                        curLevel++;
                        mostRight->right = cur;
                        cur = cur->left;
                        continue;
                    } else {
                        if (mostRight->left == nullptr) {  //第二次到达
                            minHeight = min(minHeight, curLevel);
                        }
                        curLevel -= leftHeight;  //从左子树最右孩子回来的
                        mostRight->right = nullptr;
                        cur = cur->right;
                        continue;
                    }
                } else {  //只有一次到达
                    curLevel++;
                    cur = cur->right;
                }

            }

            //process most right node of the tree-head
            int finalRight = 1;
            cur = head;
            while (cur->right != nullptr) {
                finalRight++;
                cur = cur->right;
            }
            if (cur->left == nullptr && cur->right == nullptr) {
                minHeight = min(minHeight, finalRight);
            }
            return minHeight;
        }

    };

    template<typename T>
    class MorrisTraverse {
    public:
        //先序遍历：第一次来到节点打印
        //中序遍历：第二次来到节点打印
        //后序遍历：第三次来到节点打印
        static void morrisOrder(shared_ptr<BitNode<T>> head) {
            if (head == nullptr) {
                return;
            }
            shared_ptr<BitNode<T>> cur = head;
            shared_ptr<BitNode<T>> mostRight;
            int curLevel = 0;
            while (cur != nullptr) {
                mostRight = cur->left;
                if (mostRight != nullptr) {
                    int leftBound = 1;
                    while (mostRight->right != nullptr && mostRight->right != cur) {
                        leftBound++;
                        mostRight = mostRight->right;
                    }
                    if (mostRight->right == nullptr) {
                        curLevel++;
                        cout << cur->value << "-" << curLevel << "  ";
                        mostRight->right = cur;
                        cur = cur->left;
                        continue;
                    } else {
                        curLevel = curLevel - leftBound;
                        cout << cur->value << "-" << curLevel << "  ";
                        mostRight->right = nullptr;
                        cur = cur->right;
                        continue;
                    }
                } else {
                    curLevel++;
                    cout << cur->value << "-" << curLevel << "  ";
                    cur = cur->right;
                    continue;
                }
            }

        }

        static void morrisPre(shared_ptr<BitNode<T>> head) {
            if (head == nullptr) {
                return;
            }
            shared_ptr<BitNode<T>> cur = head;
            shared_ptr<BitNode<T>> mostRight;
            while (cur != nullptr) {
                mostRight = cur->left;
                if (mostRight != nullptr) {
                    while (mostRight->right != nullptr && mostRight->right != cur) {
                        mostRight = mostRight->right;
                    }
                    if (mostRight->right == nullptr) {
                        mostRight->right = cur;
                        cout << cur->value << " ";
                        cur = cur->left;
                        continue;
                    } else {
                        mostRight->right = nullptr;
                        cur = cur->right;
                        continue;
                    }
                } else {
                    cout << cur->value << " ";
                    cur = cur->right;
                    continue;
                }
            }
        }

        static void morrisIn(shared_ptr<BitNode<T>> head) {
            if (head == nullptr) {
                return;
            }
            shared_ptr<BitNode<T>> cur = head;
            shared_ptr<BitNode<T>> mostRight;
            while (cur != nullptr) {
                mostRight = cur->left;
                if (mostRight != nullptr) {
                    while (mostRight->right != nullptr && mostRight->right != cur) {
                        mostRight = mostRight->right;
                    }
                    if (mostRight->right == nullptr) {
                        mostRight->right = cur;
                        cur = cur->left;
                        continue;
                    } else {
                        mostRight->right = nullptr;
                        cout << cur->value << " ";
                        cur = cur->right;
                        continue;
                    }
                } else {
                    cout << cur->value << " ";
                    cur = cur->right;
                    continue;
                }
            }
        }

        static void morrisPost(shared_ptr<BitNode<T>> head) {
            if (head == nullptr) {
                return;
            }
            shared_ptr<BitNode<T>> cur = head;
            shared_ptr<BitNode<T>> mostRight;

            while (cur != nullptr) {
                mostRight = cur->left;
                if (mostRight != nullptr) {
                    while (mostRight->right != nullptr && mostRight->right != cur) {
                        mostRight = mostRight->right;
                    }
                    if (mostRight->right == nullptr) {
                        mostRight->right = cur;
                        cur = cur->left;
                        continue;
                    } else {
                        mostRight->right = nullptr;
                        printEdge(cur->left);
                        cur = cur->right;
                        continue;
                    }
                } else {
                    cur = cur->right;
                    continue;
                }
            }
            printEdge(head);
        }

        static void printEdge(shared_ptr<BitNode<T>> head) {
            if (head == nullptr) {
                return;
            }
            auto tail = reverseEdge(head);
            auto cur = tail;
            while (cur != nullptr) {
                cout << cur->value << " ";
                cur = cur->right;
            }
            reverseEdge(tail);
        }

        static shared_ptr<BitNode<T>> reverseEdge(shared_ptr<BitNode<T>> head) {
            if (head == nullptr) {
                return nullptr;
            }

            shared_ptr<BitNode<T>> pre, cur, next;
            cur = head;

            while (cur != nullptr) {
                next = cur->right;
                cur->right = pre;
                pre = cur;
                cur = next;
            }
            return pre;
        }
    };

    void playmorris(shared_ptr<BitNode<int>> head) {
        MorrisTraverse<int>::morrisOrder(head);
        cout << endl;

        MorrisTraverse<int>::morrisIn(head);
        cout << endl;

        MorrisTraverse<int>::morrisPre(head);
        cout << endl;

        MorrisTraverse<int>::morrisPost(head);
        cout << endl;

    }

    void playMinHeight(shared_ptr<BitNode<int>> head) {

        MinHeight<int> mh;

        cout << mh.minHeight1(head) << endl;

        cout << mh.minHeight2(head) << endl;

        cout << mh.minHeight3(head) << endl;

    }

    void play() {
        //最小子树，最大子树
        shared_ptr<BitNode<int>> head = make_shared<BitNode<int>>(1);
        head->left = make_shared<BitNode<int>>(2);
        head->left->left = make_shared<BitNode<int>>(4);
        head->left->right = make_shared<BitNode<int>>(5);
        //head->left->left->left = make_shared<BitNode<int>>(8);

        head->right = make_shared<BitNode<int>>(3);
        head->right->left = make_shared<BitNode<int>>(6);
        head->right->right = make_shared<BitNode<int>>(7);

        //playmorris(head);

        playMinHeight(head);

    }
}

int main(int argc, char *argv[]) {

    //q01_stickers_spell_words::play();
    //q02_longest_increasing_path::play();
    //q03_max_sub_array_sum_less_or_equal_k::play();
    q04_word_serach::play();
    q05_binary_tree_height_morris::play();
    return 0;
}