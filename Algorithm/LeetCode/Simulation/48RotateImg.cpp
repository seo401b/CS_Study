#include <iostream>
#include <vector>

class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        int n = matrix.size(); //It's n*n
        std::vector<std::vector<int>> result(n, std::vector<int>(n));
        
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                result[i][j] = matrix[n-j-1][i];
            }
        }
        matrix = result;
        return;
    }
};

int main() {
    std::vector<std::vector<int>> matrix = 
    {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    
    Solution().rotate(matrix);

    // 출력
    for(const auto& row : matrix) {
        for(int val : row) std::cout << val << " ";
        std::cout << "\n";
    }
    return 0;
}