#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <typeinfo>
#include <list>

using namespace std;

class Node;

class Edge {
public:
    Node *from;
    Node *to;
    int weight;

    Edge() {
        weight = 0;
        from = nullptr;
        to = nullptr;
    }

    Edge(int w, Node *f, Node *t) {
        from = f;
        to = t;
        weight = w;
    }

    bool operator==(const Edge &e) {
        return e.weight == weight;
    }
};

//https://cloud.tencent.com/developer/article/1480532  // 自定义比较器和类型，哈希
struct edgeHash {
    size_t operator()(const Edge &edge) const {
        return hash<int>()(edge.weight);
    }
};

struct edgeEqual {
    bool operator()(const Edge &lhs, const Edge &rhs) const {
        return lhs.weight == rhs.weight;
    }
};


class Node {
public:
    int value;
    int in;
    int out;
    unordered_map<int, Node> nexts;
    //unordered_set<Edge, edgeHash, edgeEqual> edges;
    unordered_set<Edge, edgeHash, edgeEqual> edges;
public:
    Node(int v) {
        value = v;
        in = 0;
        out = 0;
    }

    Node() {
        value = 0;
        in = 0;
        out = 0;
    }

    Node operator=(const Node &node) {
        this->value = node.value;
        this->in = node.in;
        this->out = node.out;
        for (auto n : nexts) {
            this->nexts.insert(pair<int, Node>(n.first, n.second));
        }
        for (auto n : edges) {
            this->edges.insert(n);
        }
    }

};

struct nodeHash {
    size_t operator()(const Node &n) const {
        return hash<int>()(n.value);
    }
};

struct nodeEqual {
    bool operator()(const Node &n1, const Node &n2) const {
        return n1.value == n2.value;
    }
};

class Graph {
public:
    unordered_map<int, Node> nodes;
    unordered_set<Edge, edgeHash, edgeEqual> edges;
};

class GraphGenerator {
public:
    //   weight1, node1, node2
    //   weight2, node1, node3
    //   ...      ...    ...   matrix[][]
    Graph createGraph(vector<vector<int>> matrix) {
        Graph graph;
        for (int i = 0; i < matrix.size(); i++) {
            if (matrix[i].size() == 3) {
                int weight = matrix[i][0];
                int from = matrix[i][1];
                int to = matrix[i][2];
                if (graph.nodes.count(from) == 0) {
                    graph.nodes.insert(pair<int, Node>(from, Node(from)));
                }
                if (graph.nodes.count(to) == 0) {
                    graph.nodes.insert(pair<int, Node>(to, Node(to)));
                }
                Node *fromNode = &graph.nodes[from];
                Node *toNode = &graph.nodes[to];
                Edge *edge = new Edge(weight, fromNode, toNode);
                fromNode->out++;
                toNode->in++;
                fromNode->nexts.insert(pair<int, Node>(to, *toNode));
                fromNode->edges.insert(*edge);
                graph.edges.insert(*edge);
            }
        }
        return graph;
    }

};

class TypologySort {

public:
    list<Node> sortedTypology(const Graph &graph) {
        queue<Node> myqueue;
        unordered_map<Node, int, nodeHash, nodeEqual> mymap;
        list<Node> rst;
        for (auto n : graph.nodes) {
            mymap.insert(pair<Node, int>(n.second, n.first));
            if (n.second.in == 0) {
                myqueue.push(n.second);
            }
        }

        while (!myqueue.empty()) {
            Node node = myqueue.front();
            myqueue.pop();
            rst.push_back(node);

            for (auto n : node.nexts) {
                mymap[n.second]--;
                if (n.second.in == 0) {
                    myqueue.push(n.second);
                }
            }
        }
        return rst;
    }
};

int main() {

    vector<vector<int>> matrix = {{1, 2, 1},
                                  {1, 3, 1},
                                  {1, 4, 1},
                                  {1, 3, 2},
                                  {1, 6, 3},
                                  {1, 5, 2}};
    Graph graph;
    GraphGenerator gg;
    graph = gg.createGraph(matrix);
    TypologySort ts;
    list<Node> nl = ts.sortedTypology(graph);
    system("pause");
    return 0;
}