#include <iostream>
#include <string>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <typeinfo>
#include <list>
#include <set>

using namespace std;

class ReverseStackUseRecursive {

public:
    void reverse(stack<int> mystack) {
        if (mystack.empty()) {
            return;
        }
        int last = getAndPopLastElement(mystack);
        reverse(mystack);
        mystack.push(last);
    }

private:
    int getAndPopLastElement(stack<int> &mystack) {

        int result = INT_MIN;
        if (!mystack.empty()) {
            result = mystack.top();
            mystack.pop();
        }

        if (mystack.empty()) {
            return result;
        } else {

            int last = getAndPopLastElement(mystack);
            mystack.push(result);
            return last;
        }
    }
};

int main() {

    stack<int> mystack;
    mystack.push(1);
    mystack.push(2);
    mystack.push(3);
    ReverseStackUseRecursive rsur;
    rsur.reverse(mystack);
    cout << mystack.top();


    system("pause");
    return 0;
}