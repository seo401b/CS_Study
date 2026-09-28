#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
private:
    void dfs(std::vector<int>& nums, std::vector<std::vector<int>>& result, std::vector<int>& cur, std::vector<bool>& isvisit){
        if(cur.size()==nums.size()){
            result.push_back(cur);
            return;
        }
        for(int i = 0; i < nums.size(); ++i){
            if(i>0 && nums[i]==nums[i-1] && !isvisit[i-1]) continue;
            if(isvisit[i] == false){
                isvisit[i] = true;
                cur.push_back(nums[i]);
                dfs(nums, result, cur, isvisit);
                cur.pop_back();
                isvisit[i] = false;
            }
        }
    }
public:
    std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> cur;
        std::vector<bool> isvisit;
        isvisit.assign(nums.size(), false);
        sort(nums.begin(), nums.end());

        dfs(nums, result, cur, isvisit);
        return result;
    }
};

int main() {
    Solution sol;
    std::vector<int> nums = {1, 1, 2};
    
    // 순열 실행
    std::vector<std::vector<int>> result = sol.permuteUnique(nums);

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