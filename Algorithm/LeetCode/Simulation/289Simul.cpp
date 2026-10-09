#include <iostream>
#include <vector>
#include <utility>
#include <random>
#include <chrono>
#include <thread>

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

int main() {
    const int ROWS = 25;
    const int COLS = 50;

    std::vector<std::vector<int>> board(
        ROWS, std::vector<int>(COLS, 0)
    );

    // 무작위 초기 상태 생성
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);

    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            board[r][c] = dist(rng);
        }
    }

    Solution sol;
    int generation = 0;

    while (true) {
        // 터미널 화면 지우기
        std::cout << "\033[2J\033[H";

        std::cout << "Conway's Game of Life\n";
        std::cout << "Generation: " << generation++ << "\n\n";

        // 현재 세대 출력
        for (const auto& row : board) {
            for (int cell : row) {
                std::cout << (cell == 1 ? "■ " : "  ");
            }
            std::cout << '\n';
        }

        std::cout << "\nCtrl+C to stop\n";
        std::cout.flush();

        // 다음 세대 계산
        sol.gameOfLife(board);

        // 0.7초 대기
        std::this_thread::sleep_for(
            std::chrono::milliseconds(700)
        );
    }

    return 0;
}