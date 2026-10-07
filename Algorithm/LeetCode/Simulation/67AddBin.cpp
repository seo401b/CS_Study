#include <iostream>
#include <algorithm>
#include <bitset>

class Solution {
private:
    std::string CarryAdder(std::string a, std::string b) {
        std::string result ="";
        int i = a.length()-1;
        int j = b.length()-1;
        int carry = 0;
        while(i>=0 || j>=0 || carry>0){
            int sum = carry;
            if(i>=0) sum += a[i]-'0';
            if(j>=0) sum += b[j]-'0';
            carry = sum/2;
            result += (sum%2)+'0';
            i--; j--;
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    std::string Stoull(std::string a, std::string b){
        unsigned long long num1 = std::stoull(a, nullptr, 2);
        unsigned long long num2 = std::stoull(b, nullptr, 2);
        unsigned long long sum = num1 + num2;

        if(sum==0) return "0";

        std::string res = std::bitset<64>(sum).to_string();
        return res.substr(res.find_first_not_of('0'));
    }
public:
    std::string addBinary(std::string a, std::string b) {
        //return CarryAdder(a,b);
        //return Stoull(a, b); 통과 못함
        
    }
};

int main(){
    std::string a = "1010";
    std::string b = "1011";

    Solution sol;
    std::string result = sol.addBinary(a, b);
    std::cout << result << '\n';
    return 0;
}