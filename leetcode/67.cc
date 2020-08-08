#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Solution {
public:
    int strToInt(string str) {
        if( str.empty()) return 0;
        char c = NULL;
        int flag = 1;
        int ret = 0;
        for(int i = 0; i< str.size(); i++){
            c = str[i];
            if( isdigit(c)){
                if(ret >= INT32_MAX/10){
                    return INT32_MAX;
                }else if (ret <= INT32_MIN/10){
                    return INT32_MIN;
                }
                ret = ret*10 + static_cast<int>(c-'0');
            }else if (c == '-'){
                if (i +1< str.size() && isdigit(str[i+1]) && ret ==0){
                    flag = -1;
                }
            }else if (!isdigit(c) && ret !=0){
                break;
            }
        }
        return ret; 
    }
};

int main(){
    Solution so;
    cout<<so.strToInt("   -41");

