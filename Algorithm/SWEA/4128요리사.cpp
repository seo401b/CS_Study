#include <iostream>
#include <vector>
#include <algorithm>

int n; int min_diff;
std::vector<std::vector<int>> table;
std::vector<bool> used;

void dfs(int idx, int count){
    if(count==n/2){
        std::vector<int> groupA;
        std::vector<int> groupB;
        for(int i=0; i<n; ++i){
            if(used[i]) groupA.push_back(i);
            else groupB.push_back(i);
        }
        int sumA = 0; int sumB = 0;
        for(int i=0; i<n/2; ++i){
            for(int j=i+1; j<n/2; ++j){
                sumA += table[groupA[i]][groupA[j]]+table[groupA[j]][groupA[i]];
                sumB += table[groupB[i]][groupB[j]]+table[groupB[j]][groupB[i]];
            }
        }

        int diff = std::abs(sumA-sumB);
        if(diff<min_diff) min_diff=diff;
        return;
    }

    for(int i=idx; i<n; ++i){
        used[i]=1;
        dfs(i+1, count+1);
        used[i]=0;
    }
    return;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	std::cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        std::cin >> n;
        table.assign(n, std::vector<int>(n));
        used.assign(n, 0);
        min_diff=1e9;

        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                std::cin >> table[i][j];
            }
        }

        used[0]=1;
        dfs(1, 1);
        std::cout << "#" << test_case << " " << min_diff << '\n';
	}
	return 0;
}

