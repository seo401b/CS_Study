#include <iostream>
#include <vector>

class Solution {
private:
    std::vector<int> dx = {-1, 1, 0, 0};
    std::vector<int> dy = {0, 0, -1, 1};

    bool is_inside(int x, int y, int rowsize, int colsize){
        return(0<=x&&x<rowsize && 0<=y&&y<colsize);
    }

    bool dfs(std::vector<std::vector<char>>& board, const std::string& word, int x, int y, int idx){
        if(idx == word.length()) return true;

        if(!is_inside(x, y, board.size(), board[0].size())||board[x][y]!=word[idx]){
            return false;
        }

        char temp = board[x][y];
        board[x][y] = '#';

        for(int i = 0; i < 4; ++i){
            if(dfs(board, word, x+dx[i], y+dy[i], idx+1)){
                board[x][y] = temp;
                return true;
            }
        }
        board[x][y] = temp;
        return false;
    }
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {

        int rows = board.size();
        int cols = board[0].size();

        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j){
                if(word[0]==board[i][j]){
                    if(dfs(board, word, i, j, 0)){
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

int main() {
    Solution sol;

    // 테스트용 보드 생성 (LeetCode Word Search 예시 형태)
    std::vector<std::vector<char>> board = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };

    std::string word = "ABCCED";

    bool ans = sol.exist(board, word);

    std::cout << "Word Search Result: " << (ans ? "true" : "false") << std::endl;

    return 0;
}