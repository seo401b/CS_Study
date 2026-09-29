#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
private:
    void dfs(std::vector<int>& nums, std::vector<std::vector<int>>& result, std::vector<int>& cur, int idx, bool choosed){
        if(idx==nums.size()){
            result.push_back(cur);
            return;
        }

        dfs(nums, result, cur, idx+1, false);

        if(idx>0 && nums[idx]==nums[idx-1] && !choosed) return;

        cur.push_back(nums[idx]);
        dfs(nums, result, cur, idx+1, true);
        cur.pop_back();
        //이렇게 choose를 visit처럼 쓰는 방법도 있는데
        //그냥 중복을 visit 체크없이 전부 때려 박은 뒤에 
        //출력 전에 중복을 밀고 출력하는 방법도 있다.
    }
public:
    std::vector<std::vector<int>> subsetsWithDup(std::vector<int>& nums) {
        std::vector<std::vector<int>> result;
        std::vector<int> cur;
        sort(nums.begin(), nums.end());

        dfs(nums, result, cur, 0, false);
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