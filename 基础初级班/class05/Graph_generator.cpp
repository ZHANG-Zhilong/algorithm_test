#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <typeinfo>

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
};

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
                Edge edge(weight, fromNode, toNode);
                fromNode->in++;
                toNode->out++;
                fromNode->nexts.insert(pair<int, Node>(to, *toNode));
                fromNode->edges.insert(edge);
                graph.edges.insert(edge);
            }
        }
        return graph;
    }

};


class BFS {
public:
    void bfs(Node head) {
        //判断参数有效性
        if (&head == nullptr) {
            return;
        }
        queue<Node> myqueue;
        unordered_set<Node, nodeHash, nodeEqual> myset;

        myqueue.push(head);
        myset.insert(head);

        while (!myqueue.empty()) {
            Node node = myqueue.front();
            cout << node.value << endl;
            myqueue.pop();

            for (auto n : node.nexts) {
                if (myset.count(n.second) == 0) {
                    myqueue.push(n.second);  // 注册该结点，是否加入过队列
                    myset.insert(n.second);
                }
            }
        }
    }

};

int main() {

    vector<vector<int>> matrix = {{1, 1, 2},
                                  {1, 1, 3},
                                  {1, 1, 4},
                                  {1, 2, 7},
                                  {1, 7, 3},
                                  {1, 3, 5},
                                  {1, 4, 6}};
    Graph graph;
    GraphGenerator gg;
    graph = gg.createGraph(matrix);
    Node head = graph.nodes[1];
    BFS bfs;
    bfs.bfs(head);
    system("pause");
    return 0;
}