#include <iostream>
#include <vector>

class Solution {
private:
    void dfs(const std::vector<int>& candidate, const int& target, int add_num, int start_idx, std::vector<int>& current, std::vector<std::vector<int>>& result){
        if(add_num > target){
            return;
        }

        else if(add_num==target) {
            result.push_back(current);
            return;
        }

        for(int i = start_idx; i < candidate.size(); ++i){
            current.push_back(candidate[i]);
            dfs(candidate, target, add_num+candidate[i], i, current, result);
            current.pop_back();
        }
    }

public:
    std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
        std::vector<std::vector<int>> result;
        std::vector<int> current;

        dfs(candidates, target, 0, 0, current, result);
        return result;
    }
};

int main() {
    Solution sol;
    
    // 테스트 케이스 설정
    std::vector<int> candidates = {2, 3, 5};
    int target = 8;

    // 함수 호출
    std::vector<std::vector<int>> result = sol.combinationSum(candidates, target);

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