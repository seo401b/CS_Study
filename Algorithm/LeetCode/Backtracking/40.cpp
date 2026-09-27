#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
private:
    void sort_vec(std::vector<int>& candidates){
        sort(candidates.begin(), candidates.end());
    }
    void dfs(std::vector<int>& candidates, int target, std::vector<std::vector<int>>& result, std::vector<int>& cur, int idx){
        if(target==0){
            result.push_back(cur);
            return;
        }
        for(int i = idx; i < candidates.size(); ++i){
            if(candidates[i]>target) break;
            if(i>idx && candidates[i]==candidates[i-1]) continue;
            cur.push_back(candidates[i]);
            dfs(candidates, target - candidates[i], result, cur, i+1);
            cur.pop_back();
        }
    }
public:
    std::vector<std::vector<int>> combinationSum2(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> result;
        std::vector<int> cur;

        sort_vec(candidates);
        dfs(candidates, target, result, cur, 0);
        return result;
    }
};

int main() {
    Solution sol;
    
    // 테스트 케이스 설정
    std::vector<int> candidates = {10,1,2,7,6,1,5};
    int target = 8;

    // 함수 호출
    std::vector<std::vector<int>> result = sol.combinationSum2(candidates, target);

    // 결과 출력
    std::cout << "--- Combination Sum 결과 ---\n";
    for (const auto& combination : result) {
        std::cout << "[ ";
        for (int num : combination) {
            std::cout << num << " ";
        }
        std::cout << "]\n";
    }

    return 0;
}