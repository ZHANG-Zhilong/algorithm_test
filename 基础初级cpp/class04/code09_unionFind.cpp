#include <iostream>
#include <random>
#include <stack>
#include <unordered_map>
#include <typeinfo>

using namespace std;

typedef struct Data {
    //whatever u like.

} Data;

int main() {
    unordered_map<char, int> umap;
    umap.insert(make_pair('a', 3));
    cout << umap['a'] << endl;
    umap['a'] = 9;
    cout << umap['a'] << endl;
    system("pause");
}