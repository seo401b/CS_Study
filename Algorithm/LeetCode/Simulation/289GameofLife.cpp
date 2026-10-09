#include <iostream>
#include <vector>
#include <utility>

class Solution {
private:
    int neighbors_num(std::vector<std::vector<int>>& board, int row, int col){
        int cnt = 0;
        for(int dr = -1; dr<2; ++dr){
            for(int dc = -1; dc<2; ++dc){
                if(dr==0&&dc==0) continue;
                int r = row+dr;
                int c = col+dc;
                if(r<0 || r>board.size()-1 || c<0 || c>board[0].size()-1) continue;

                if(board[r][c]==1) cnt++;
            }
        }
        return cnt;
    }
public:
    void gameOfLife(std::vector<std::vector<int>>& board) {
        std::vector<std::vector<int>> result(board.size(), std::vector<int>(board[0].size(), 0));
        for(int r=0; r<board.size(); ++r){
            for(int c=0; c<board[0].size(); ++c){
                int neigh_num = neighbors_num(board, r, c);
                if(board[r][c]==1){
                    if(2<=neigh_num&&neigh_num<=3) result[r][c]=1;
                    else result[r][c] = 0;
                }
                else{
                    if(neigh_num==3) result[r][c]=1;
                    else result[r][c]=0;
                }
            }
        }
        board = std::move(result);
    }
};

// 1. 살아 있는 셀이 살아 있는 이웃 셀의 수가 2개 미만이면, 인구 부족으로 인해 죽는다.
// 2. 살아 있는 셀이 살아 있는 이웃 셀의 수가 2개 또는 3개이면, 다음 세대에도 살아남는다.
// 3. 살아 있는 셀이 살아 있는 이웃 셀의 수가 3개를 초과하면, 인구 과잉으로 인해 죽는다.
// 4. 죽어 있는 셀이 살아 있는 이웃 셀을 정확히 3개 가지고 있으면, 번식을 통해 살아 있는 셀로 바뀐다.

int main() {
    std::vector<std::vector<int>> board = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1},
        {0, 0, 0}
    };

    Solution sol;
    sol.gameOfLife(board);

    for (const auto& row : board) {
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << '\n';
    }

    return 0;
}