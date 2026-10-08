#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// DP
int solveDP(const vector<int>& charge, const vector<int>& useplan) {
    vector<int> dp(12, 0);

    // 1월 달 초기화 (1일 이용권 vs 1달 이용권)
    dp[0] = min(useplan[0] * charge[0], charge[1]);

    for (int i = 1; i < 12; ++i) {
        // 옵션 A: 이전 달까지의 최솟값 + (이번 달 1일 이용권 vs 1달 이용권 중 최선)
        int option_1month = dp[i - 1] + min(useplan[i] * charge[0], charge[1]);

        // 옵션 B: 3달 전까지의 최솟값 + 3달 이용권
        // (i가 2 이하일 때: 0~i월 전체를 3달 이용권 1장으로 덮는 경우)
        int prev = (i >= 3) ? dp[i - 3] : 0;
        int option_3month = prev + charge[2];

        dp[i] = min(option_1month, option_3month);
    }

    // 12개월 DP 최선책 vs 1년 이용권
    return min(dp[11], charge[3]);
}

// 재귀
int solveRecursion(const vector<int>& charge, const vector<int>& useplan, int month = 0, int current_cost = 0) {
    if (month >= 12) {
        return current_cost;
    }
    int opt1 = solveRecursion(charge, useplan, month+1, current_cost+charge[0]*useplan[month]);
    int opt2 = solveRecursion(charge, useplan, month+1, current_cost+charge[1]);
    int opt3 = solveRecursion(charge, useplan, month+3, current_cost+charge[2]);

    return std::min({opt1, opt2, opt3});
}

int main(int argc, char** argv) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (!(cin >> T)) return 0;

    for (int test_case = 1; test_case <= T; ++test_case) {
        vector<int> charge(4);
        vector<int> useplan(12);

        for (int i = 0; i < 4; ++i) {
            cin >> charge[i];
        }
        for (int i = 0; i < 12; ++i) {
            cin >> useplan[i];
        }

        // DP
        //int ans_dp = solveDP(charge, useplan);

        // 재귀
        int ans_rec = min(solveRecursion(charge, useplan), charge[3]);

        cout << "#" << test_case << " " << ans_rec << '\n';
    }

    return 0;
}