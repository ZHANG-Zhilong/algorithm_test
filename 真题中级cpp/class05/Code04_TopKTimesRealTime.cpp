//
// Created by 张志龙 on 2020/6/18.
//
#include <iostream>
#include <algorithm>
#include <utility>
#include <map>
#include <vector>
#include <functional>
#include <memory>

namespace Code04_TopKTimesRealTime {

    class Node {
    public:
        std::string str;
        int times;
    public:
        explicit Node(std::string str = "", int times = 0) :
                str(std::move(str)), times(times) {}

        struct Compare {
            bool operator()(const Node &a, const Node &b);
        };
    };

    bool Node::Compare::operator()(const Node &a, const Node &b) {
        return a.str < b.str;
    }


    class TopKTimesRealTime {
    public:
        explicit TopKTimesRealTime(int k);

        void add(const std::string &str);

        void printTopK();

    private:

        int heapSiz_;
        std::vector<std::shared_ptr<Node>> minHeap_;
        std::map<std::string, std::shared_ptr<Node>> strNodeMap;
        std::map<std::shared_ptr<Node>, int> nodeIndexMap;

        void heapInsert(int index);

        void heaptify(int index, int heapsiz);

        void swap(int index1, int index2);

    };


    void TopKTimesRealTime::heapInsert(int index) {
        while (index > 0) {
            int pindex = (index - 1) / 2;
            if (pindex >= 0) {
                if (minHeap_[index]->times < minHeap_[pindex]->times) {
                    swap(index, pindex);
                    index = pindex;
                } else {
                    break;
                }
            }
        }
    }

    TopKTimesRealTime::TopKTimesRealTime(const int k) :
            heapSiz_(0) {
        minHeap_.resize(k);
    }

    void TopKTimesRealTime::heaptify(int index, int heapsiz) {
        if (heapsiz < 1 || index < 0) { return; }
        int smallest = index;
        int l = smallest * 2 + 1;
        int r = smallest * 2 + 2;
        while (l < heapsiz) {
            if (minHeap_[l]->times < minHeap_[index]->times) {
                swap(l, index);
                smallest = l;
            }
            if (r < heapsiz && minHeap_[smallest]->times > minHeap_[r]->times) {
                smallest = r;
            }
            if (smallest == index) {
                break;
            } else {
                swap(index, smallest);
                std::swap(index, smallest);
            }
            index = smallest;
            l = smallest * 2 + 1;
            r = smallest * 2 + 2;
        }

    }

    void TopKTimesRealTime::add(const std::string &str) {
        int preIndex = -1;
        std::shared_ptr<Node> curNode = std::make_shared<Node>();
        if (strNodeMap.find(str) == strNodeMap.end()) {  //first occur.
            curNode = std::make_shared<Node>(str, 1);
            nodeIndexMap[curNode] = -1;
            strNodeMap[str] = curNode;
        } else {                                        //not first occur.
            curNode = strNodeMap.find(str)->second;
            curNode->times++;
            preIndex = nodeIndexMap.find(curNode)->second;
        }

        if (preIndex == -1) {    //not in heap.
            if ((size_t) heapSiz_ == minHeap_.size()) {  //heap is full.
                if (curNode->times > minHeap_[0]->times) {
                    nodeIndexMap[minHeap_[0]] = -1;
                    nodeIndexMap[curNode] = 0;
                    minHeap_[0] = curNode;
                    heaptify(0, heapSiz_);
                }
            } else {        //heap is not full.
                nodeIndexMap[curNode] = heapSiz_;
                minHeap_[heapSiz_] = curNode;
                heapInsert(heapSiz_++);
            }
        } else {        //already in heap.
            heaptify(preIndex, heapSiz_);
        }
    }

    void TopKTimesRealTime::swap(int index1, int index2) {
        nodeIndexMap[minHeap_[index1]] = index2;
        nodeIndexMap[minHeap_[index2]] = index1;
        std::swap(minHeap_[index1], minHeap_[index2]);
    }

    void TopKTimesRealTime::printTopK() {
        for (auto &node: minHeap_) {
            if (node == nullptr) { break; }
            printf("%s: %d\n", node->str.c_str(), node->times);
        }
    }
}

using namespace Code04_TopKTimesRealTime;

using std::cout;
using std::endl;

int main() {
    std::string str{};
    TopKTimesRealTime trt(3);
    while (str != "fuck") {
        std::cin >> str;
        trt.add(str);
        trt.printTopK();
    }
    std::cout << endl;
    return 0;
}

