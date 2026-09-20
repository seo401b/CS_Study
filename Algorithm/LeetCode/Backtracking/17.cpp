#include <iostream>
#include <vector>
class Solution{
    private:
        std::vector<std::string> pad {
            "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
        };

        void dfs(const std::string& digits, int idx, std::string current, std::vector<std::string>& result){
            if(idx==digits.length()){
                result.push_back(current);
                return;
            }

            int digit = digits[idx] -'0';
            for(char letter: pad[digit]){
                dfs(digits, idx+1, current+letter, result);
            }
        }

    public:
        std::vector<std::string> letterCombinations(std::string digits){
            std::vector<std::string> result;

            dfs(digits, 0, "", result);
            return result;
        }
};
