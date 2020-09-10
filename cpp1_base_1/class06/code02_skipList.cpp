#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;
//https://lotabout.me/2018/skip-list/

class SkipListNode {
public:
    int value;
    vector<SkipListNode *> nextNodes;

    SkipListNode(int data = 0) {
        value = data;
    }
};

class SkipList {
private:
    SkipListNode *head;
    double PROBABILITY;
    int size;
    int maxLevel;
public:
    SkipList() {
        maxLevel = 0;
        size = 0;
        PROBABILITY = 0.5;
        head = new SkipListNode();
        SkipListNode *newNode = nullptr;
        head->nextNodes.push_back(newNode);
    }

    SkipListNode getHead() {
        return *head;
    }

    int getSize() {
        return size;
    }

    void add(int newValue) {
        if (!contains(newValue)) {
            size++;
            int level = 0;
            random_device rd;
            while ((double) rd() / rd.max() < PROBABILITY) {
                level++;
            }
            while (level > maxLevel) {
                SkipListNode *nullNode = nullptr;
                head->nextNodes.push_back(nullNode);
                maxLevel++;
            }
            SkipListNode *newNode = new SkipListNode(newValue);
            SkipListNode *current = head;
            do {
                current = findNext(newValue, current, level);
                newNode->nextNodes.insert(begin(newNode->nextNodes), current->nextNodes.at(level));
                current->nextNodes.at(level) = newNode;

            } while (level-- > 0);
        }
    }

    void remove(int deleteValue) {
        if (contains(deleteValue)) {
            SkipListNode deleteNode = *find(deleteValue);
            size--;
            int level = maxLevel;
            SkipListNode *current = head;
            do {
                current = findNext(deleteValue, current, level);
                if (deleteNode.nextNodes.size() > level) {
                    current->nextNodes.at(level) = deleteNode.nextNodes.at(level);
                }
            } while (level-- > 0);
        }
    }

    //return the skiplist node with greatest value <=e
    SkipListNode *find(int e) {
        return find(e, head, maxLevel);
    }

private:

    bool contains(int value) {
        SkipListNode *node = nullptr;
        node = find(value);

        return node != nullptr && node->value == value;
        //return node != null && node.value != null && equalTo(node.value, value);
        //return node != nullptr && &node->value != nullptr;//not complete.
    }

    //find the greatest skiplist node with value <=e
    //start at the node start and level
    SkipListNode *find(int e, SkipListNode *current, int level) {
        do {
            current = findNext(e, current, level);
        } while (level-- > 0);
        return current;
    }

    //return the node at a given level, with the highest value < e
    SkipListNode *findNext(int e, SkipListNode *current, int level) {
        SkipListNode *next = nullptr;
        next = current->nextNodes.at(level);
        while (next != nullptr) {
            int value = next->value;
            if (e < value) {
                break;
            }
            current = next;
            next = current->nextNodes.at(level);
        }
        return current;
    }
};

int main() {

    SkipList skiplist;
    skiplist.add(1);
    skiplist.add(9);
    skiplist.add(3);

    system("pause");
    return 0;
}
