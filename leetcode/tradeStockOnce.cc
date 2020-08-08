#include <iostream>
#include <vector>
//假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖该股票一次可能获得的最大利润是多少？

using namespace std;
class Solution {
public:
    int maxProfit(vector<int>& prices) {

        int maxPrice = INT32_MIN;
        int minPrice = INT32_MAX;
        int minPos = 0;
        int maxPos = 0;
        //[7,1,5,3,6,4]
        //[2, 4, 1]
        for(int i = 0; i<prices.size(); i++){
            if(prices[i] < minPrice){
                minPrice = prices[i];
                minPos = i;
            }
            if(maxPos < minPos){  //这里格外注意，不可以等于
                maxPos = minPos;
                maxPrice = minPrice;
            }else
                maxPrice = max(maxPrice, prices[i]);
                maxPos = i;
            }
        }
        return maxPrice> minPrice? maxPrice - minPrice:0;
    }
};

int main(){
    vector<int> prices = {7,1,5,3,6,4};
    Solution solution;
    cout<<solution.maxProfit(prices);
}