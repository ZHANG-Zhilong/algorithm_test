#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

using namespace std;

class Node {
public:
    shared_ptr<Node> up;
    shared_ptr<Node> down;
    int key;
    int value;
    int time;

    Node(int key, int value, int time) {
        this->key = key;
        this->value = value;
        this->time = time;
        up = nullptr;
        down = nullptr;
    }
};

class NodeList {

public:
    shared_ptr<Node> head;
    shared_ptr<Node> tail;
    shared_ptr<NodeList> pre;
    shared_ptr<NodeList> next;

public:
    NodeList(shared_ptr<Node> node) {
        head = node;
        tail = node;
    }

    int addNodeFromHead(shared_ptr<Node> node) {
        if (node == nullptr) {
            return -1;
        }
        head->up = node;
        node->down = head;
        head = node;
        return 0;
    }

    int remove(shared_ptr<Node> node) {
        if (node == nullptr || empty()) {
            return -1;
        }
        if (head == tail) {
            head = nullptr;
            tail = nullptr;
        } else if (node == head) {
            head = head->down;
            head->up = nullptr;
        } else if (node == tail) {
            tail = tail->up;
            tail->down = nullptr;
        } else {
            node->up->down = node->down;
            node->down->up = node->up;
        }
        node->up = nullptr;
        node->down = nullptr;
        return 0;
    }

    bool empty() {
        return head == nullptr;
    }
};

class LFUCache {
private:
    int capacity;
    int size;
    unordered_map<int, shared_ptr<Node>> records;
    unordered_map<shared_ptr<Node>, shared_ptr<NodeList>> head;
    shared_ptr<NodeList> headList;

public:
    LFUCache(int capacity) {
        if (capacity < 3) {
            capacity = 3;
            cout << "default min capacity is 3." << endl;
        }
        this->capacity = capacity;
        this->size = 0;
    }

    int set(int key, int value) {
        if (records.find(key) != records.end()) {
            auto node = records[key];
            auto nodeList = head[node];
            node->value = value;
            node->time++;
            move(node, nodeList);
        } else {
            if (this->size == this->capacity) {
                auto node = headList->tail;
                records.erase(node->key);
                head.erase(node);
                headList->remove(node);
                this->modify(headList);
                size--;
            }
            auto newNode = make_shared<Node>(key, value, 1);
            if (headList == nullptr) {
                headList = make_shared<NodeList>(newNode);
            }
            if (headList->head->time != 1) {
                auto newList = make_shared<NodeList>(newNode);
                headList->pre = newList;
                newList->next = headList;
                headList = newList;
            } else {
                headList->addNodeFromHead(newNode);
            }
            records[key] = newNode;
            head[newNode] = headList;
            size++;
        }
        return 0;
    }

    int get(int key) {
        if (records.find(key) == records.end()) {
            return INT32_MIN;
        }
        shared_ptr<Node> node = records[key];
        shared_ptr<NodeList> nodeList = head[node];
        node->time++;
        move(node, nodeList);
        return node->value;
    }

private:
    int modify(shared_ptr<NodeList> targetNodeList) {
        if (targetNodeList == nullptr) {
            cout << "targetNodeList is nullptr." << endl;
            return -1;
        }
        if (targetNodeList->empty()) {
            if (targetNodeList == headList) {
                headList = targetNodeList->next;
                if (headList != nullptr) {
                    headList->pre = nullptr;
                }
            } else {
                targetNodeList->pre->next = targetNodeList->next;
                if (targetNodeList->next != nullptr) {
                    targetNodeList->next->pre = targetNodeList->pre;
                }
            }
            return 1;
        }
        return 0;
    }

    int move(shared_ptr<Node> node, shared_ptr<NodeList> oldNodeList) {
        if (node == nullptr || oldNodeList == nullptr) {
            cout << "move error" << endl;
            return -1;
        }
        oldNodeList->remove(node);
        shared_ptr<NodeList> preList = modify(oldNodeList) == 0 ? oldNodeList->pre : oldNodeList;
        auto nextList = oldNodeList->next;
        if (nextList == nullptr) {
            shared_ptr<NodeList> newList = make_shared<NodeList>(node);
            head[node] = newList;
            newList->pre = preList;
            if (preList != nullptr) {
                preList->next = newList;
            }
            if (headList == nullptr) {
                headList = nextList;
            }
        } else {
            if (nextList->head->time = node->time) {
                nextList->addNodeFromHead(node);
                head[node] = nextList;
            } else {
                auto newList = make_shared<NodeList>(node);
                head[node] = newList;

                newList->pre = preList;
                if (preList != nullptr) {
                    preList->next = newList;
                }
                newList->next = nextList;
                nextList->pre = newList;
                if (headList == nextList) {
                    headList = newList;
                }
            }
        }
        return 0;
    }
};

void play() {
    LFUCache lfu(3);
    lfu.set(1, 5);
    cout << lfu.get(1) << endl;
    lfu.set(2, 9);
    lfu.set(3, 4);
    lfu.set(5, 9);
    cout << lfu.get(1) << endl;
    cout << lfu.get(3) << endl;
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
