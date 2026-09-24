#include <iostream>
#include <vector>

class Solution {
private:
    std::vector<int> nums_;
    std::vector<std::vector<int>> result_;
    std::vector<int> current_;
    std::vector<bool> visited;

    void dfs(int cur_idx){
        if(current_.size()==nums_.size()){
            result_.push_back(current_);
            return;
        }

        for(int i = 0; i < nums_.size(); ++i){
            if(!visited[i]){
                visited[i] = 1;
                current_.push_back(nums_[i]);
                dfs(i);
                current_.pop_back();
                visited[i] = 0;
            }
        }
    }
public:
    std::vector<std::vector<int>> permute(std::vector<int>& nums) {
        nums_ = nums;
        result_.clear();
        current_.clear();
        visited.assign(nums.size(), 0);

        dfs(0);
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