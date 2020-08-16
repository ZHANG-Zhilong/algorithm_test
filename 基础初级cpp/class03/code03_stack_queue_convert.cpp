#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <stack>
#include <queue>

using namespace std;

class StackByQueue {
private:
    queue<int> queueData;
    queue<int> queueHelp;
public:
    int push(int obj);

    int pop();

    int peek();
};

int StackByQueue::push(int obj) {
    queueData.push(obj);
    return 0;
}

int StackByQueue::pop() {
    if (queueData.size() == 0) {
        cout << "the stack is empty." << endl;
        return -1;
    }
    while (queueData.size() > 1) {
        queueHelp.push(queueData.front());
        queueData.pop();
    }
    int value = queueData.front();
    queueData.pop();
    swap(queueData, queueHelp);
    return value;
}

int StackByQueue::peek() {
    if (queueData.size() == 0) {
        cout << "the stack is empty";
        return NULL;
    }
    while (!queueData.size() == 1) {
        queueHelp.push(queueData.front());
        queueData.pop();
    }
    int value = queueData.front();
    queueHelp.push(value);
    queueData.pop();
    swap(queueData, queueHelp);
    return value;
}


class QueueByStack {
private:
    stack<int> stackPush;
    stack<int> stackPop;
public:
    int push(int obj);

    int pop();

    int peek();

    int pure2pop();
};

int QueueByStack::push(int obj) {
    while (stackPop.size() > 0) {
        stackPush.push(stackPop.top());
        stackPop.pop();
    }
    stackPush.push(obj);
    pure2pop();
    return 0;
}


int QueueByStack::peek() {
    if (stackPush.size() == 0 && stackPop.size() == 0) {
        cout << "the stack is empty." << endl;
        return -1;
    }
    if (stackPush.size() != 0) {
        pure2pop();
    }
    return stackPop.top();
}

int QueueByStack::pop() {
    if (stackPush.size() == 0 && stackPop.size() == 0) {
        cout << "the stack is empty." << endl;
        return -1;
    }
    if (stackPush.size() != 0) {
        pure2pop();
    }
    int value = stackPop.top();
    stackPop.pop();
    return value;
}

int QueueByStack::pure2pop() {
    if (stackPush.size() > 0) {
        while (stackPush.size() > 0) {
            stackPop.push(stackPush.top());
            stackPush.pop();
        }
    }
    return 0;
}

int main() {
    bool succeed = false;
    StackByQueue stackq;

    stackq.push(1);
    stackq.push(2);
    stackq.push(3);

    cout << stackq.pop() << endl;
    cout << stackq.pop() << endl;
    cout << stackq.pop() << endl;

    cout << "-----------" << endl;
    QueueByStack queues;
    queues.push(1);
    queues.push(2);
    queues.push(3);

    cout << queues.pop() << endl;
    cout << queues.pop() << endl;
    cout << queues.pop() << endl;


    string str = succeed ? "\nnice" : "\nfreaking fucking fuck!";
    cout << str << endl;
    system("pause");
}