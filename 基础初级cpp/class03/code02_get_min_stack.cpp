#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <stack>

using namespace std;

class MyStack1 {
private:
    stack<int> stackData;
    stack<int> stackMin;
public:
    int push(int obj) {
        if (stackMin.empty()) {
            stackMin.push(obj);
        } else if (obj < this->getMin()) {
            stackMin.push(obj);
        } else {
            stackMin.push(this->getMin());
        }
        stackData.push(obj);
        return 0;
    }

    int pop() {
        if (stackData.empty()) {
            cout << "pop failed, the stack is empty." << endl;
            return -1;
        }
        int temp = stackData.top();
        stackData.pop();
        stackMin.pop();
        return temp;
    }

    int getMin() {
        if (stackMin.size() == 0) {
            cout << "the minstack is empty.";
            return -1;
        }
        return stackMin.top();
    }


};

class MyStack2 {
private:
    stack<int> stackData;
    stack<int> stackMin;
public:
    int push(int obj) {
        if (stackMin.empty()) {
            stackMin.push(obj);
        } else if (obj <= this->getMin()) {
            stackMin.push(obj);
        }
        stackData.push(obj);
        return 0;
    }

    int pop() {
        if (stackData.empty()) {
            cout << "pop failed, the stack is empty." << endl;
            return -1;
        }
        int value = stackData.top();
        if (value == stackMin.top()) {
            stackMin.pop();
        }
        stackData.pop();
        return value;
    }

    int getMin() {
        if (stackMin.size() == 0) {
            cout << "the minstack is empty.";
            return -1;
        }
        return stackMin.top();
    }


};

int main() {
    bool succeed = false;

    MyStack2 mystack2;
    mystack2.push(1);
    mystack2.push(1);
    mystack2.push(2);
    cout << mystack2.getMin() << endl;
    cout << mystack2.pop() << endl;
    cout << mystack2.getMin() << endl;


    string str = succeed ? "\nnice" : "\nfreaking fucking fuck!";
    cout << str << endl;
    system("pause");
}