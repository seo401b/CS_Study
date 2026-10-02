#include <iostream>
#include <vector>

class Solution {
public:
    void setZeroes(std::vector<std::vector<int>>& matrix) {
        bool isverzero = false;
        bool ishorzero = false;
        for(int i = 0; i < matrix.size(); ++i){
            if(matrix[i][0] == 0) {
                isverzero = true;
                break;
            }
        }

        for(int j = 0; j < matrix[0].size(); ++j){
            if(matrix[0][j] == 0) {
                ishorzero = true;
                break;
            }
        }
        
        for(int i=0; i<matrix.size(); ++i){
            for(int j=0; j<matrix[0].size(); ++j){
                if(matrix[i][j]==0){
                    matrix[i][0]=0;
                    matrix[0][j]=0;
                }
            }
        }

        for(int i=1; i<matrix.size(); ++i){
            if(matrix[i][0]==0) matrix[i].assign(matrix[0].size(), 0);
        }
        for(int i=1; i<matrix[0].size(); ++i){
            if(matrix[0][i]==0){
                for(int j=1; j<matrix.size(); ++j) matrix[j][i]=0;
            }
        }
        if(isverzero) {
            for(int i=0; i<matrix.size(); ++i) matrix[i][0]=0;
        }
        if(ishorzero){
            for(int i=0; i<matrix[0].size(); ++i) matrix[0][i]=0;
        }
    }
};


int main() {
    // 테스트용 2차원 벡터 (3x3 매트릭스, 중앙에 0이 있는 경우)
    std::vector<std::vector<int>> matrix = {
        {0,1,2,0},
        {3,4,5,2},
        {1,3,1,5}
    };

    std::cout << "--- 변경 전 매트릭스 ---\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    Solution sol;
    sol.setZeroes(matrix);

    std::cout << "\n--- 변경 후 매트릭스 ---\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    return 0;
}