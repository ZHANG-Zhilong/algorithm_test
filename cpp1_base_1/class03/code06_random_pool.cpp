#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;


template<typename K>
class Pool {
private:
    unordered_map<K, int> _keyIndexMap;
    unordered_map<int, K> _indexKeyMap;
    int _size;
public:
    Pool();

    void pop(K key);

    void insert(K key);

    K getRandom();
};

template<typename K>
Pool<K>::Pool() {
    _size = 0;
}

template<typename K>
void Pool<K>::pop(K key) {
    if (_keyIndexMap.count(key) > 0) {
        int deleteIndex = _keyIndexMap.at(key);
        int lastIndex = --_size;
        K lastkey = _indexKeyMap.at(lastIndex);
        _keyIndexMap.at(lastkey) = deleteIndex;
        _indexKeyMap.at(deleteIndex) = lastkey;
        _keyIndexMap.erase(key);
        _indexKeyMap.erase(lastIndex);
    }
}

template<typename K>
void Pool<K>::insert(K key) {
    if (_keyIndexMap.count(key) == 0) {
        _keyIndexMap.insert(pair<K, int>(key, _size));
        _indexKeyMap.insert(make_pair(_size++, key));
    }
}

template<typename K>
K Pool<K>::getRandom() {
    if (_size == 0) {
        return 0;
    }
    random_device rd;
    int randomI = rd() % _size;
    K key = _indexKeyMap.at(randomI);
    cout << key << endl;
    return key;
}


int main() {

    /**
     * Definition for singly-linked list.
     * struct ListNode {
     *     int val;
     *     ListNode *next;
     *     ListNode(int x) : val(x), next(NULL) {}
     * };
     */

    Pool<char> pool;
    pool.insert('a');
    pool.insert('z');
    pool.insert('c');
    pool.pop('a');
    pool.getRandom();

    system("pause");
}