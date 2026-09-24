#include <iostream>
#include <vector>

class Solution {
private:
    std::vector<std::vector<int>> result_;

    void dfs(int idx, std::vector<int>& nums_){
        if(idx==nums_.size()) {
            result_.push_back(nums_);
            return;
        }

        for(int i = idx; i < nums_.size(); ++i){
            std::swap(nums_[i], nums_[idx]);
            dfs(idx+1, nums_);
            std::swap(nums_[i], nums_[idx]);
        }
    }
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        result_.clear();

        dfs(0, nums);
        return result_;
    }
};

int main() {
    Solution sol;
    std::vector<int> nums = {1, 2, 3};
    
    // 순열 실행
    std::vector<std::vector<int>> result = sol.permute(nums);

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