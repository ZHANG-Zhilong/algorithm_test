#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include<unordered_map>
#include <algorithm>

using namespace std;

template<typename K, typename V>
class Node {
public:
    K key;
    V value;
    Node *pre;
    Node *next;

    Node(K key = 0, V value = 0) {
        this->key = key;
        this->value = value;
        pre = (Node<K, V> *) nullptr;
        next = (Node<K, V> *) nullptr;
    }
};

template<typename K, typename V>
class NodeDoubleLinkedList {
public:
    Node<K, V> *head;
    Node<K, V> *tail;

    NodeDoubleLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void addNode(Node<K, V> &newNode) {
        if (&newNode == nullptr) {
            return;
        }
        Node<K, V> *node = &newNode;
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->pre = tail;
            tail = tail->next;
        }

    }

    void moveToTail(Node<K, V> &node) {
        if (&node == this->tail) {
            return;
        }
        Node<K, V> *cur = &node;
        if (cur == this->head) {
            head = head->next;
            head->pre = nullptr;
        } else {
            cur->pre->next = cur->next;
            cur->next->pre = cur->pre;
        }
        cur = tail->next;
        cur->pre = tail;
        cur->next = nullptr;
        tail = tail->next;
    }

    Node<K, V> removeHead() {
        Node<K, V> *rst = this->head;
        if (this->head == nullptr) {
            return *rst;
        }
        if (this->head == this->tail) {
            this->head = nullptr;
            this->tail = nullptr;
        } else {
            this->head = this->head->next;
            this->head->pre = nullptr;
            rst->next = nullptr;
        }
        return *rst;
    }

    void printList() {
        Node<K, V> *node = head;
        while (node != nullptr) {
            cout << node->value << " ";
            node = node->next;
        }
        cout << endl;
    }
};

template<typename K, typename V>
class MyCache {
private:
private:
    unordered_map<K, Node<K, V> *> keyNodeMap;
    NodeDoubleLinkedList<K, V> nodeList;
    int capacity;
public:
    MyCache(int capacity = 3) {
        if (capacity < 1) {
            cout << "set capacity error, default setted as 3";
            capacity = 3;
        }
        this->capacity = capacity;
    }

    V get(K key) {
        if (keyNodeMap.count(key) > 0) {
            Node<K, V> *node = keyNodeMap[key];
            nodeList.moveToTail(node);
            return node->value;
        }
        return nullptr;
    }

    void set(K key, V value) {
        if (keyNodeMap.count(key) > 0) {
            Node<K, V> *node = keyNodeMap[key];
            node->value = value;
            nodeList.moveToTail(*node);
        } else {
            Node<K, V> *node = new Node<K, V>(key, value);
            keyNodeMap[key] = node;
            nodeList.addNode(*node);
            if (keyNodeMap.size() > 3) {
                removeMostUnusedCache();
            }
        }
    }

    void removeMostUnusedCache() {
        Node<K, V> node = nodeList.removeHead();
        K removeKey = node.key;
        keyNodeMap.erase(removeKey);
    }

    void printCache() {
        nodeList.printList();
    }


};

int main() {


    Node<int, int> node(5);
    MyCache<int, int> mycache;
    mycache.set(1, 2);
    mycache.printCache();
    mycache.set(2, 3);
    mycache.printCache();
    mycache.set(3, 5);
    mycache.printCache();
    mycache.set(6, 8);
    mycache.printCache();
    system("pause");
    return 0;
}
