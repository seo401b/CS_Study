#include <iostream>
#include <vector>

class Solution {

private:
    std::vector<std::vector<int>> result;
    std::vector<int> cur;
    void dfs(int mask, std::vector<int>& nums){
        if(mask>= (1 << nums.size())) return;

        for(int i = 0; i < nums.size(); ++i){
            if(mask&(1 << i)){
                cur.push_back(nums[i]);
            }
        }
        result.push_back(cur);
        cur.clear();
        dfs(mask+1, nums);
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