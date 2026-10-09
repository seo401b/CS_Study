#include <iostream>
#include <vector>
#include <string>

class Solution {
private:
    bool isValid(const std::vector<std::string>& board, int row, int col, int n) {
        //같은 열
        for(int i=0; i<row; ++i){
            if(board[i][col]=='Q') return false;
        }
        //왼쪽 대각선
        for(int i=row-1, j=col-1; i>=0&&j>=0; --i, --j){
            if(board[i][j]=='Q') return false;
        }
        //오른쪽 대각선
        for(int i=row-1, j=col+1; i>=0&&j<n; --i, ++j){
            if(board[i][j]=='Q') return false;
        }
        return true;
    }
    void dfs(std::vector<std::vector<std::string>>& result, std::vector<std::string>& board, int n, int row){
        if(row==n){
            result.push_back(board);
            return;
        }
        for(int col=0; col<n; ++col){
            if(isValid(board, row, col, n)){
                board[row][col]='Q';
                dfs(result, board, n, row+1);
                board[row][col]='.';
            }
        }
    }
public:
    std::vector<std::vector<std::string>> solveNQueens(int n){
        std::vector<std::vector<std::string>> result;
        std::vector<std::string> board(n, std::string(n, '.'));
        dfs(result, board, n, 0);
        return result;
    }
};

int main() {
    Solution solver;
    int n = 2;

    std::vector<std::vector<std::string>> solutions = solver.solveNQueens(n);

    std::cout << "N = " << n << " 일 때 해의 개수: " << solutions.size() << "\n\n";

    // 결과 출력
    // for (size_t i = 0; i < solutions.size(); ++i) {
    //     std::cout << "[Solution " << i + 1 << "]\n";
    //     for (const std::string& row : solutions[i]) {
    //         std::cout << row << "\n";
    //     }
    //     std::cout << "\n";
    // }

    return 0;
}