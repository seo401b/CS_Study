#include <iostream>
#include <vector>
class Solution {
private:
    bool BinarySearch(std::vector<std::vector<int>>& matrix, int target){
        int m = matrix.size();
        int n = matrix[0].size();
        for(int i=0; i<m; ++i){
            int low = 0;
            int high = n-1;
            while(low<=high){
                int mid = (low+high)/2;
                if(matrix[i][mid]==target) return true;

                else if(matrix[i][mid]<target) low = mid+1;
                else high = mid-1;
            }
        }
        return false;
    }

    bool SizeDown(std::vector<std::vector<int>>& matrix, int target, int row1, int col1, int row2, int col2){
        if(row1>row2 || col1>col2) return false;
        if(matrix[row1][col1] > target || target > matrix[row2][col2]) return false;
        for(int i=0; i<matrix[0].size(); ++i){
            if(matrix[row1][i] ==target || matrix[row2][i]==target){
                return true;
            }
        }
        for(int i=0; i<matrix.size(); ++i){
            if(matrix[i][col1]==target || matrix[i][col2]==target){
                return true;
            }
        }
        return SizeDown(matrix, target, row1+1, col1+1, row2-1, col2-1);
    }

    bool TwoPointer(std::vector<std::vector<int>>& matrix, int target){
        int row=0;
        int col=matrix[0].size()-1;
        //0,0에서 시작하면 row++,col++ 모두 숫자가 커짐(일방향성) -> 기준이 없게 됨
        //0, n-1에서 시작해 row++은 숫자가 커지고, col--는 숫자가 작아지도록
        while(row<matrix.size() && col >=0){
            if(target == matrix[row][col]) return true;
            else if(target < matrix[row][col]) col--;
            else row++;
        }
        return false;
    }

    bool DivideConq(std::vector<std::vector<int>>& matrix, int target, int row1, int col1, int row2, int col2){
        if(row1 > row2 || col1 > col2) return false;
        if(target<matrix[row1][col1] || target>matrix[row2][col2]) return false;

        int midRow = row1 + (row2-row1) / 2;
        int midCol = col1 + (col2-col1) / 2;
        int pivot = matrix[midRow][midCol];

        if(pivot==target) return true;

        if(target<pivot){ //4사분면 제외
            if(DivideConq(matrix, target, row1, col1, midRow-1, midCol-1)) return true;
            if(DivideConq(matrix, target, row1, midCol, midRow-1, col2)) return true;
            if(DivideConq(matrix, target, midRow, col1, row2, midCol-1)) return true;
        }
        else{ //1사분면 제외
            if(DivideConq(matrix, target, row1, midCol+1, midRow, col2)) return true;
            if(DivideConq(matrix, target, midRow+1, col1, row2, midCol)) return true;
            if(DivideConq(matrix, target, midRow+1, midCol+1, row2, col2)) return true;
        }
        return false;
    }
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        //return BinarySearch(matrix, target);
        //return SizeDown(matrix, target, 0,0, matrix.size()-1,matrix[0].size()-1);
        //return TwoPointer(matrix, target);
        return DivideConq(matrix, target, 0,0, matrix.size()-1,matrix[0].size()-1);
    }
};

int main() {
    Solution solution;

    // 전달해주신 입력 예시
    std::vector<std::vector<int>> matrix = {
        {1,  4,  7,  11, 15},
        {2,  5,  8,  12, 19},
        {3,  6,  9,  16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };
    int target = 5;

    // 결과 출력
    std::cout << std::boolalpha;
    bool result = solution.searchMatrix(matrix, target);

    std::cout << "Input: matrix, target = " << target << std::endl;
    std::cout << "Output: " << result << std::endl;

    return 0;
}