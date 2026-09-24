#include <iostream>
#include <vector>

class Solution {

private:
    std::vector<std::vector<int>> result;
    std::vector<int> cur;
    void dfs(int idx, std::vector<int>& nums){
        if(idx==nums.size()) {
            result.push_back(cur);
            return;
        }
        
        cur.push_back(nums[idx]);
        dfs(idx+1, nums);
        cur.pop_back();

        dfs(idx+1, nums);
    }
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        
        dfs(0, nums);
        return result;
    }
};

int main() {
    Solution sol;
    std::vector<int> nums = {1, 2, 3};
    
    // 순열 실행
    std::vector<std::vector<int>> result = sol.subsets(nums);

    // 결과 출력
    std::cout << "[\n";
    for (const auto& vec : result) {
        std::cout << "  [";
        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << vec[i] << (i + 1 < vec.size() ? ", " : "");
        }
        std::cout << "]\n";
    }
    std::cout << "]\n";

    return 0;
}