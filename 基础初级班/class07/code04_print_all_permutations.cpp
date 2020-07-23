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

class PrintAllPermutation {
public:
    void printAllPermutations(string str) {
        process1(str, 0);
    }

    void printAllPermutations2(string str) {
        process2(str, 0);
    }

private:
    void process1(string str, int i) {
        if (i == str.size()) {
            cout << str << endl;
            return;
        }

        for (int j = i; j < str.size(); j++) {
            swap(str[i], str[j]);
            process1(str, i + 1);
            //swap(str[j], str[i]);
        }
    }

    void process2(string str, int i) {
        if (i == str.size()) {
            cout << str << endl;
            return;
        }

        unordered_set<char> strset;
        for (int j = i; j < str.size(); j++) {
            if (strset.count(str[j]) == 0) {
                strset.insert(str[j]);
                swap(str[i], str[j]);
                process2(str, i + 1);
                //swap(str[j], str[i]);
            }
        }
    }
};

int main() {
    PrintAllPermutation pap;
//    pap.printAllPermutations("abc");

    pap.printAllPermutations2("acc");
    system("pause");
    return 0;
}