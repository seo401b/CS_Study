#include <iostream>
#include <vector>

class Solution {
private:
    std::vector<std::string> parenthesis {
        "(", ")"
    };
    void dfs(const int n, std::string current, int left, int right, std::vector<std::string>& result){
        if(current.length()==2*n) {
            result.push_back(current);
            return;
        }

        if(left < n){
            dfs(n, current+parenthesis[0], left+1, right, result);
        }

        if(left > right){
            dfs(n, current+parenthesis[1], left, right+1, result);
        }

    }
public:
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> result;

        dfs(n, "(", 1, 0, result);
        return result;
    }
};

int main() {
    Solution solution;
    int n = 3;
    
    std::vector<std::string> results = solution.generateParenthesis(n);
    
    std::cout << "n = " << n << std::endl;
    for (const std::string& s : results) {
        std::cout << s << std::endl;
    }

    return 0;
}

//"(" 하나를 +1 ")" 하나를 -1이라 하면 0이하로 내려가면 탐색 정지


