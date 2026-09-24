#include <iostream>
#include <vector>

class Solution {
private:
    std::vector<int> dx = {-1, 1, 0, 0};
    std::vector<int> dy = {0, 0, -1, 1};
    std::vector<std::vector<char>> board_;
    std::string word_;
    std::vector<std::vector<bool>> visited;
    bool result;

    bool is_inside(int x, int y, int rowsize, int colsize){
        return(0<=x&&x<rowsize && 0<=y&&y<colsize);
    }

    void dfs(int posx, int posy, int idx){
        if(word_[idx-1] == board_[posx][posy] && idx == word_.length()){
            result = true;
            return;
        }
        else if(word_[idx-1]!=board_[posx][posy]) return;

        if(idx > word_.length()){
            return;
        }

        for(int i = 0; i < 4; ++i){
            int x = posx+dx[i];
            int y = posy+dy[i];
            if(is_inside(x, y, board_.size(), board_[0].size()) && !visited[x][y]){
                visited[x][y] = 1;
                dfs(x, y, idx+1);
                visited[x][y] = 0;
            }
        }
    }
public:
    bool exist(std::vector<std::vector<char>>& board, std::string word) {
        board_=board;
        word_=word;
        result = false;

        int rows = board.size();
        int cols = board[0].size();
        visited = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));

        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j){
                if(word[0]==board[i][j]){
                    visited[i][j] = 1;
                    dfs(i, j, 1);
                    visited[i][j] = 0;
                }
            }
        }
        return result;
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