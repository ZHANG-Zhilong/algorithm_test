#include <iostream>
#include <random>
#include <vector>
#include <stack>
#include <queue>
#include <typeinfo>

using namespace std;

class PaperFolding {
public:
    void printAllFolders(int N) {
        printProcess(1, N, true);
    }

private:
    void printProcess(int i, int N, bool down) {
        if (i > N) {
            return;
        }
        printProcess(i + 1, N, true);
        string str = down ? "down" : "up";
        cout << str << "  ";
        printProcess(i + 1, N, false);

    }

};

int main() {
    PaperFolding paperFolding;
    paperFolding.printAllFolders(3);

    system("pause");
}