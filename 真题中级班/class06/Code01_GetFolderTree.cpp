//
// Created by 张志龙 on 2020/6/18.
//
#include <utility>
#include <vector>
#include <memory>
#include <map>

using std::vector;
using std::string;

class Node {
public:
    std::string name;
    std::map<string, std::shared_ptr<Node>> nextMap;

    explicit Node(std::string name) : name(std::move(name)) {}
};

class GetFolderTree {
private:
    using NodePtr = std::shared_ptr<Node>;
    vector<string> folderPaths_;
public:
    void print(const vector<string> &folderPaths);

    static NodePtr generateFolderTree(const vector<string> &folderPath);

    void printProcess(const NodePtr &head, int level);

    static string get4nSpace(int level);
};

void GetFolderTree::print(const vector<string> &folderPaths) {
    if (folderPaths.empty()) { return; }
    NodePtr head = GetFolderTree::generateFolderTree(folderPaths);
    printProcess(head, 0);
}

GetFolderTree::NodePtr GetFolderTree::generateFolderTree(const vector<string> &folderPath) {
    return GetFolderTree::NodePtr();
}

void GetFolderTree::printProcess(const NodePtr &head, int level) {

}

string GetFolderTree::get4nSpace(int level) {
    string ret{};
    for (int i = 0; i > 0; i++) {
        ret += "    ";
    }
    return ret;
}

int main() {
    string str = "a/b/c/d";
    return 0;
}