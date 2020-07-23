#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <typeinfo>

using namespace std;

class Edge;

class Node {
public:
    int value;
    int in;
    int out;
    unordered_map<int, Node> nexts;  //value, Node
    unordered_map<int, int> weights;  //value, Node
public:
    Node(int v = 0) {
        value = v;
        in = 0;
        out = 0;
    }

    bool operator()(const Node &node1, const Node &node2) const {
        return node1 == node2;
    }

    bool operator==(const Node &node) const {
        return this->value == node.value;
    }
};

struct nodeHash {
    size_t operator()(const Node &n) const {
        return hash<int>()(n.value);
    }
};

struct nodeEqual {
    bool operator()(const Node &n1, const Node &n2) const {
        return n1 == n2;
    }
};

class Edge {
public:
    Node from;
    Node to;
    int weight;

    Edge(int weight, Node &from, Node &to) {
        this->from = from;
        this->to = to;
        this->weight = weight;
    }

    bool operator()(const Edge &edge1, const Edge &edge2) const {
        return edge1 == edge2;
    }

    bool operator==(const Edge &edge) const {
        return ((this->weight == edge.weight) &&
                (this->from == edge.from) && (this->to == edge.to));
    }
};

struct edgeHash {
    size_t operator()(const Edge &edge) const {
        size_t value1 = hash<int>()(edge.from.value);
        size_t value2 = hash<int>()(edge.to.value);
        return hash<int>()(edge.weight + value1 + value2);
    }
};

struct edgeEqual { //obselete
    bool operator()(const Edge &lhs, const Edge &rhs) const {
        return lhs == rhs;
    }
};

class Graph {
public:
    unordered_map<int, Node> nodes;
    unordered_set<Edge, edgeHash> edges;
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
                Node &fromNode = graph.nodes[from];
                Node &toNode = graph.nodes[to];
                Edge edge(weight, fromNode, toNode);
                fromNode.out++;
                toNode.in++;
                fromNode.nexts.insert(pair<int, Node>(to, toNode));
                fromNode.weights.insert(pair<int, int>(toNode.value, weight));
                graph.edges.insert(edge);
            }
        }
        return graph;
    }

};


class BFS {
public:
    void bfs(Graph graph) {
        //判断参数有效性
        if (&graph == nullptr || graph.nodes.size() == 0) {
            return;
        }
        queue<Node> myqueue;
        unordered_set<Node, nodeHash, nodeEqual> myset;

        Node head = graph.nodes[1];
        myqueue.push(head);
        myset.insert(head);

        while (!myqueue.empty()) {
            Node node = myqueue.front();
            cout << node.value << endl;
            myqueue.pop();

            for (pair<int, Node> n : node.nexts) {
                if (myset.count(n.second) == 0) {
                    myqueue.push(graph.nodes[n.first]);  // 注册该结点，是否加入过队列
                    myset.insert(graph.nodes[n.first]);
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
    bfs.bfs(graph);
    system("pause");
    return 0;
}