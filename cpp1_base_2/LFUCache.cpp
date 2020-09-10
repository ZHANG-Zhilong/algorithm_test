#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include<unordered_map>
#include <algorithm>

using namespace std;

class LFU {

    class Node {
    public:
        int value;
        int times;
        int key;
        Node *up;
        Node *down;

        Node(int key, int value, int times) {
            this->key = key;
            this->value = value;
            this->times = times;
            up = nullptr;
            down = nullptr;
        }
    };

    class NodeList {  // 2 dimensions double linked list.
    public:
        Node *head;
        Node *tail;
        NodeList *pre;
        NodeList *next;
    public:
        NodeList(Node *head = nullptr) {  //设计理念是必须给我一个东西我才建立，简化内部逻辑
            this->head = head;  //up
            this->tail = head;  //down
            this->pre = nullptr;  //left
            this->next = nullptr;  //right
        }

        void addNodeFromHead(Node *newNode) {  //头插法，尾部的元素为早期插入
            head->up = newNode;
            newNode->down = head;
            head = newNode;
        }

        bool empty() {
            return head == nullptr;
        }

        void removeNode(Node *node) {
            if (head == tail) {
                head = nullptr;
                tail = nullptr;
            } else {
                if (node == head) {
                    head = head->down;
                    head->up = nullptr;
                } else if (node == tail) {
                    tail = tail->up;
                    tail->down = nullptr;
                } else {
                    node->down->up = node->up;
                    node->up->down = node->down;
                }
            }
            node->up = nullptr;
            node->down = nullptr;
        }
    };

    class LFUCache {
    public:
        int capacity;
        int size;
    private:
        NodeList *headList;
        unordered_map<int, Node *> record;
        unordered_map<Node *, NodeList *> heads;
    public:
        LFUCache(int capacity = 3) {  // initializition headList's head and its tail are nullptr.
            if (capacity < 1) {
                capacity = 3;
            }
            this->capacity = capacity;
            this->size = 0;
            this->headList = nullptr;
        }

        void set(int key, int value) {
            if (record.count(key) > 0) {
                Node *node = record[key];  // 查找该结点记录，是否曾加入过
                node->value = value;
                node->times++;
                NodeList *nodeList = heads[node];  //查找该节点对应的大链表
                move(node, nodeList);  //将该结点与当前大链表解耦，并将结点移动到频次+1的大链表上面
            } else {
                if (size == capacity) {
                    Node *node = headList->tail;
                    headList->removeNode(node);  // 删除node结点
                    modifyHeadList(headList);   //处理node结点的环境，包括headlist、record，heads
                    record.erase(node->key);    //消除node的影响
                    heads.erase(node);
                    size--;
                }
                Node *newNode = new Node(key, value, 1);
                if (headList == nullptr) {
                    headList = new NodeList(newNode);
                } else {
                    if (newNode->times == headList->head->times) {
                        headList->addNodeFromHead(newNode);
                    } else {
                        NodeList *nodelist = new NodeList(newNode);
                        headList->pre = nodelist;
                        nodelist->next = headList;
                        headList = nodelist;
                    }
                }
                record[key] = newNode;
                heads[newNode] = headList;
                size++;
            }


        }

        void move(Node *node, NodeList *oldNodeList) {
            oldNodeList->removeNode(node);
            NodeList *preList = modifyHeadList(oldNodeList) ? oldNodeList->pre : oldNodeList; //for newNodeList
            NodeList *nextList = oldNodeList->next;  //for newNodeList
            if (nextList == nullptr) {  //newNodeList is highest word frequency.
                NodeList *newNodeList = new NodeList(node);
                if (preList != nullptr) {
                    preList->next = newNodeList;
                }
                newNodeList->pre = preList;
                if (headList == nullptr) {
                    headList = newNodeList;
                }
                heads[node] = newNodeList;
            } else {
                if (nextList->head->times == node->times) {
                    nextList->addNodeFromHead(node);  //add node, modify its environment
                    heads[node] = nextList;
                } else {
                    NodeList *newNodeList = new NodeList(node);
                    if (preList != nullptr) {
                        preList->next = newNodeList;
                    }
                    newNodeList->pre = preList;
                    newNodeList->next = nextList;
                    nextList->pre = newNodeList;
                    if (headList == nextList) {   //<=> newNodeList->pre == nullptr
                        headList = newNodeList;
                    }
                    heads[node] = newNodeList;
                }
            }
            //把结点从nodelist分离出来，挂在词频+1的大链表上
        }

        //return weather delete this head
        bool modifyHeadList(NodeList *nodelist) {
            //大链表如果没有东西了，要消除大链表自己的影响
            if (nodelist->empty()) {
                if (nodelist == headList) {
                    headList = headList->next;
                    if (headList != nullptr) {
                        headList->pre = nullptr;
                    }
                } else {
                    nodelist->pre->next = nodelist->next;
                    if (nodelist->next != nullptr) {
                        nodelist->next->pre = nodelist->pre;
                    }
                }
                return true;
            }
            return false;
            //检查headlist环境，看是否需要删除headlist
        }

        int get(int key) {
            if (record.count(key) == 0) {
                return INT_MIN;
            }
            Node *rst = record[key];
            rst->times++;
            NodeList *nodeList = heads[rst];
            move(rst, nodeList);
            return rst->value;
        }


    };


};


int main() {
    system("pause");
    return 0;
}
