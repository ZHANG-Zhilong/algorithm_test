#include <iostream>
#include <random>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include<unordered_map>
#include <algorithm>

using namespace std;

class ExpressionCalculation {
private:
    vector<int> value(string str, int star) {
        list <string> que;
        int pre = 0;
        vector<int> bra;
        while (star < str.size() && str[star] != ')') {
            if (str[star] >= '0' && str[star] <= '9') {
                pre = 10 * pre + (int) (str[star++] - '0');
            } else if (str[star] != '(') {  // + - * /
                addNum(que, pre);
                string ope = "";
                ope = str[star++];
                que.push_back(ope);
                pre = 0;
            } else {  //  (
                bra = value(str, star + 1);
                pre = bra[0];
                star = bra[1] + 1;
            }
        }
        addNum(que, pre);
        return {getNum(que), star};
        //arr[0]代表计算的结果
        //arr[1]代表算到了哪个位置
    }

    void addNum(list <string> &que, int num) {
        if (!que.empty()) {
            int cur = 0;
            string top = que.back();
            que.pop_back();
            if (top == "+" || top == "-") {
                que.push_back(top);
            } else {
                cur = stoi(que.back());
                que.pop_back();
                num = top == "*" ? (cur * num) : (cur / num);
            }
        }
        que.push_back(to_string(num));
    }

    int getNum(list <string> &que) {
        int res = 0;
        bool add = true;
        string cur = "";
        int num = 0;
        while (!que.empty()) {
            cur = que.front();
            que.pop_front();
            if (cur == "+") {
                add = true;
            } else if (cur == "-") {
                add = false;
            } else {
                num = stoi(cur);
                res += add ? num : (-num);
            }
        }
        return res;
    }

public:
    int getvalue(string str) {
        return value(str, 0)[0];
    }

};

int main() {

    ExpressionCalculation ec;

    string exp = "48*((70-65)-43)+8*1";
    cout << ec.getvalue(exp) << endl;

    exp = "4*(6+78)+53-9/2+45*8";
    cout << ec.getvalue(exp) << endl;

    exp = "10-5*3";
    cout << ec.getvalue(exp) << endl;

    exp = "-3*4";
    cout << ec.getvalue(exp) << endl;

    exp = "3+1*4";
    cout << ec.getvalue(exp) << endl;

    system("pause");
    return 0;
}
