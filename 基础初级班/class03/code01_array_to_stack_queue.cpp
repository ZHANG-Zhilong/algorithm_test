#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;
string err = "";

class ArrayStack {
public:
    ArrayStack(int size) {
        _size = size;
        _index = 0;
        v.assign(_size, 0);
    }

    int push(int obj) {
        if (_index == _size) {
            cout << "err push: the stack is full." << endl;
            return -1;
        }
        v[_index++] = obj;
        return 0;
    }

    int peek() {
        if (_index == 0) {
            cout << "the stack is empty." << endl;
            return NULL;
        }
        return v[_index - 1];
    }

    int pop() {
        if (_index == 0) {
            cout << "err pop: the stack is already empty." << endl;
            return -1;
        }
        return v[--_index];
    }

private:
    int _size;
    int _index;
    vector<int> v;
};

class ArrayQueue {
private:
    int _size;
    int _index;
    int _start;  //指向位置的是可以弹出元素的
    int _end;  // 指向的位置是可以插入元素的
    vector<int> v;
public:
    ArrayQueue(int initSize) {
        if (initSize <= 0) {
            cout << "the queue capacity is less then zero." << endl;
            return;
        }
        _size = 0;
        _index = 0;
        _start = 0;
        _end = 0;
        v.assign(initSize, 0);
    }

    int push(int obj) {
        if (_size == v.size()) {
            cout << "the queue is full." << endl;
            return -1;
        }
        _size++;
        v[_end] = obj;
        _end = nextIndex(_end);
        return 0;
    }

    int pull() {
        if (_size == 0) {
            cout << "the queue is empty." << endl;
            return -1;
        }
        _size--;
        int temp = _start;
        _start = nextIndex(_start);
        return v[temp];
    }

    int peek() {
        if (_size == 0) {
            cout << "the queue is empty." << endl;
            return -1;
        }
        cout << v[_start] << endl;
        return v[_start];
    }

    int nextIndex(int n) {
        return n == v.size() - 1 ? 0 : n + 1;
    }

};

int main() {
    bool succeed = false;

    ArrayStack stackz(4);
    stackz.push(5);
    cout << stackz.pop() << endl;
    stackz.pop();


    string str = succeed ? "nice" : "freaking fucking fuck!";
    cout << str << endl;
    system("pause");
}