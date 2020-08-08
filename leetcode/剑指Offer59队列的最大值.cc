//剑指 Offer 59 - II. 队列的最大值
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class MaxQueue {
public:
    queue<int> q;
    deque<int> d;

    MaxQueue() {   }

    int max_value() {
		if(q.empty()){
			return -1;
		}else{
			return d.front();
		}
    }

    void push_back(int value) {
        if(value == NULL) return ;
        q.push(value);
        while(!d.empty() && value > d.back()){
            d.pop_back();
        }
		d.push_back(value);
    }

    int pop_front() {
        if(q.empty()) return -1;
        int value = q.front();
        q.pop();
        if(value == d.front()) d.pop_front();
        return value;
    }
};

/**
 * Your MaxQueue object will be instantiated and called as such:
 * MaxQueue* obj = new MaxQueue();
 * int param_1 = obj->max_value();
 * obj->push_back(value);
 * int param_3 = obj->pop_front();
 */
int main(){
	return 0;
}
