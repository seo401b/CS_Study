#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> subsets(std::vector<int>& nums) {
        std::vector<std::vector<int>> result = {{}};

        for(auto n: nums){
            int result_size = result.size();
            for(int i = 0; i < result_size; ++i){
                std::vector<int> tmp = result[i];
                tmp.push_back(n);
                result.push_back(tmp);
            }
        }
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