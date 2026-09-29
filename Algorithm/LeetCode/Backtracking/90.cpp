#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
private:
    void dfs(std::vector<int>& nums, std::vector<std::vector<int>>& result, std::vector<int>& cur, std::vector<bool>& used, int idx){
        result.push_back(cur);

        for(int i = idx; i < nums.size(); ++i){
            if(i > 0 && nums[i-1]==nums[i] && !used[i-1]) continue;
            used[i] = true;
            cur.push_back(nums[i]);
            dfs(nums, result, cur, used, i+1);
            cur.pop_back();
            used[i] = false;
        }//used 배열은 순서가 중요한 순열 문제에 필요하다. 여기선 nums[i]==nums[i-1]만으로도 충분
        
    }
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> cur;
        std::vector<bool> used;
        used.assign(nums.size(), false);
        sort(nums.begin(), nums.end());

        dfs(nums, result, cur, used, 0);
        return result;
    }
};

int main() {
    Solution sol;
    
    // 테스트용 입력 데이터
    std::vector<int> nums = {1, 2, 2};
    
    // 함수 실행
    std::vector<std::vector<int>> result = sol.subsetsWithDup(nums);

    // 결과 출력
    std::cout << "Subsets result:\n";
    for (const auto& subset : result) {
        std::cout << "[ ";
        for (int num : subset) {
            std::cout << num << " ";
        }
        std::cout << "]\n";
    }

    return 0;
}