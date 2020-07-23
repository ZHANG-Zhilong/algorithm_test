#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include<unordered_map>
#include <algorithm>

using namespace std;

/*
    二叉树中
*/

class Node {
public:
    int huo;
    vector<Node *> nexts;

    Node(int value = 0) {
        huo = value;
    }
};

class MaxHappy {

private:
    typedef struct ReturnType {
        int lai_huo;
        int bu_lai_huo;

        ReturnType(int lai, int bulai) : lai_huo(lai), bu_lai_huo(bulai) {};
    } ReturnType;

    ReturnType process(Node head) {
        int bulai_huo = 0;
        int lai_huo = 1;

        for (int i = 0; i < head.nexts.size(); i++) {
            Node *node = head.nexts.at(i);
            ReturnType rsti = process(*node);
            lai_huo += rsti.bu_lai_huo;
            bulai_huo += max(rsti.lai_huo, rsti.bu_lai_huo);
        }

        return ReturnType(lai_huo, bulai_huo);

    }

public:
    int getMaxHappy(Node head) {
        ReturnType rst = process(head);
        return max({rst.lai_huo, rst.bu_lai_huo});
    }
};

int main() {

    system("pause");
    return 0;
}
