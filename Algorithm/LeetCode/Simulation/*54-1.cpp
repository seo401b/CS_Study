#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        std::vector<int> result;
        int row=matrix.size();
        int col=matrix[0].size();

        int right = col-1;
        int bottom = row-1;
        int left = 0;
        int top = 0;

        if(matrix.empty() || matrix[0].empty()) return result;
        
        while(top<=bottom && left<=right){
            for(int i=left; i<=right; ++i){
                result.push_back(matrix[top][i]);
            }
            top++;

            for(int i=top; i<=bottom; ++i){
                result.push_back(matrix[i][right]);
            }
            right--;
            
            if(top<=bottom){
                for(int i=right; i>=left; --i){
                    result.push_back(matrix[bottom][i]);
                }
                bottom--;
            }

            if(left<=right){
                for(int i=bottom; i>=top; --i){
                    result.push_back(matrix[i][left]);
                }
                left++;
            }
        }

        return result;
    }
};




int main() {
    Solution sol;
    
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    std::vector<int> result = sol.spiralOrder(matrix);

    // 결과 출력
    std::cout << "Spiral Order Result: ";
    for (int val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}