#include <iostream>
#include <vector>

class Solution {
private:
    void dfs(const std::vector<int>& candidate, const int& target, int add_num, int idx, std::vector<int>& current, std::vector<std::vector<int>>& result){
        if(add_num == target){
            result.push_back(current);
            return;
        }

        if(add_num > target || idx >= candidate.size()){
            return;
        }

        //1
        current.push_back(candidate[idx]);
        dfs(candidate, target, add_num+candidate[idx], idx, current, result);
        current.pop_back();

        //2
        dfs(candidate, target, add_num, idx+1, current, result);
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