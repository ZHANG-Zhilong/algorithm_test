#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>

using namespace std;

class Interval {
public:
    int begin = 0;
    int end = 0;

    Interval(int begin, int end) {
        this->begin = begin;
        this->end = end;
    }
};

class InsertIntervals {
public:
    static list<shared_ptr<Interval>>
    insertIntervals(
            list<shared_ptr<Interval>> items,
            const Interval &newItem
    ) {

        list<shared_ptr<Interval>> ret;
        if (items.empty()) {
            return ret;
        }
        auto it = items.begin();
        while (it != items.end() && (*it)->end < newItem.begin) {
            ret.push_back(*it);
            it++;
        }
        int left = INT32_MAX, right = INT32_MIN;
        //ATTENTION HERS'S PRED
        while (it != items.end() && (*it)->begin <= newItem.end) {
            left = min(left, (*it)->begin);
            right = max(right, (*it)->end);
            it++;
        }
        ret.push_back(make_shared<Interval>(left, right));
        while (it != items.end()) {
            ret.push_back(*it);
            it++;
        }
        return ret;
    }
};

void play() {
    list<shared_ptr<Interval>> items;
    items.push_back(make_shared<Interval>(1, 3));
    items.push_back(make_shared<Interval>(6, 9));
    list<shared_ptr<Interval>> rst1 = InsertIntervals::insertIntervals(items, Interval(2, 5));  //[1,5],[6,9]
    for (const auto &interval: rst1) {
        cout << interval->begin << " " << interval->end << endl;
    }
}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
