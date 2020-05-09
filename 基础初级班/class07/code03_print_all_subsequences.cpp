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

class PrintAllSubSequence {
public:
    void printAllSub(const string &str) {
        string pre = "";
        process1(str, 0, pre);
    }

private:
    void process1(const string &str, int i, string preStr) {
        if (i == str.size()) {
            cout << preStr << endl;
        } else {
            process1(str, i + 1, preStr);
            process1(str, i + 1, preStr + str[i]);
        }
    }
};

int main() {
    PrintAllSubSequence pass;
    string str = "abc";
    pass.printAllSub(str);
    system("pause");
    return 0;
}