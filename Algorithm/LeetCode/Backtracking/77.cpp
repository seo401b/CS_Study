#include <iostream>
#include <vector>

class Solution {
private:
    void dfs(int n, int k, std::vector<std::vector<int>>& result, std::vector<int>& cur, int idx){
        if(cur.size()==k){
            result.push_back(cur);
            return;
        }
        for(int i = idx; i < n+1; ++i){
            cur.push_back(i);
            dfs(n , k, result, cur, i+1);
            cur.pop_back();
        }
    }
public:
    std::vector<std::vector<int>> combine(int n, int k) {
        std::vector<std::vector<int>> result;
        std::vector<int> cur;

        dfs(n, k, result, cur, 1);   
        return result;
    }
};

int main() {
    Solution sol;

    // 예시 실행 (1부터 4까지의 숫자 중 2개를 선택하는 조합)
    int n = 4;
    int k = 2;

    std::vector<std::vector<int>> ans = sol.combine(n, k);

    std::cout << "combine(" << n << ", " << k << ") 결과:" << std::endl;
    for (const auto& comb : ans) {
        std::cout << "[ ";
        for (int num : comb) {
            std::cout << num << " ";
        }
        std::cout << "]" << std::endl;
    }

    return 0;
}