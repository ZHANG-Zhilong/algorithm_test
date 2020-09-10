#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Code06_RandToRand {
public:
    // 底层依赖一个等概率返回1~5的随机函数f，
    // 如何加工出等概率返回1~7的随机函
    static int g(int a, int b, int c, int d) {
        int range = d - c;
        unsigned int num = 1;
        while (((unsigned int) 1 << num) - 1 < range) {
            num++;
        }
        int ret = 0;
        do {
            ret = 0;
            for (int i = 0; i < num; i++) {
                int p = rand01(a, b);
                ret += (p << i);
            }
        } while (ret > range);
        return ret + c;
    }

    // 底层依赖一个等概率返回1~5的随机函数f，
    static int f(int a, int b) {
        //[a, b)  integer
        random_device rd;
        double p = (double) rd() / rd.max();
        return a + (b - a) * p;
    }

    // 底层依赖一个等概率返回1~5的随机函数f，
    static int rand01(int a, int b) {
        int range = b - a;
        bool odd = range % 2 != 0;
        int mid = range / 2;
        int ret = 0;
        do {
            ret = f(a, b) - a;
        } while (odd && ret == mid);
        return ret < mid ? 0 : 1;
    }

    // 底层依赖一个以p概率返回0，以1-p概率返回1的随机函数rand01p
    // 如何加工出等概率返回0和1的函
    static int rand01(double p) {
        //走一遍，非常巧妙的roll两次
        int num = 0;
        do {
            num = rand01p(p);
        } while (num == rand01p(p));
        return num;
    }

    static int rand01p(double p) {
        random_device rd;
        double p2 = (double) rd() / rd.max();
        return p2 < p ? 0 : 1;
    }

};

void play() {
    int a = 1, b = 8, c = 3, d = 11;
    vector<int> fre(d, 0);
//    for(int i = 0; i< 100000; i++){
//        int ret = Code06_RandToRand::rand01p(0.4);
//        fre[ret]++;
//    }

//    for(int i = 0; i< 100000; i++){
//        int ret = Code06_RandToRand::f(a, b);
//        fre[ret]++;
//    }

    for (int i = 0; i < 100000; i++) {
        int ret = Code06_RandToRand::g(a, b, c, d);
        fre[ret]++;
    }

    for (int i = 0; i < fre.size(); i++) {
        cout << i << ":\t" << fre[i] << endl;
    }

}

int main(int argc, char *argv[]) {
    play();
    return 0;
}
