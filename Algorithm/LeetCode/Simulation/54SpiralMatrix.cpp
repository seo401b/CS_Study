#include <iostream>
#include <vector>
//TimeLimit code
//shitty Readable code
class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        std::vector<int> result;
        int row=matrix.size();
        int col=matrix[0].size();
        int idx = 0;

        while(result.size()!=row*col){
            for(int i=idx; i < col-idx; ++i){
                result.push_back(matrix[idx][i]);
                if(result.size()==row*col) return result;
            }
            
            for(int i=idx+1; i < row-idx-1; ++i){
                result.push_back(matrix[i][col-idx-1]);
                if(result.size()==row*col) return result;
            }
            
            for(int i=row-idx-1; i > idx; --i){
                result.push_back(matrix[row-idx-1][i]);
                if(result.size()==row*col) return result;
            }

            for(int i=col-idx-2; i >idx; --i){
                result.push_back(matrix[i][idx]);
                if(result.size()==row*col) return result;
            }

            idx++;
        }
        return result;
    }
};




int main() {
    Solution sol;
    
    // 테스트용 3x3 행렬
    std::vector<std::vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
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