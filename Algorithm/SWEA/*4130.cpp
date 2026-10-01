#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void RotateMagnet(std::vector<std::deque<int>>& magnet, int rot_dir, int rot_num){
    int idx = rot_num-1;
    int dirs[4] = {0, 0, 0, 0};
    dirs[idx] = rot_dir;

    //자석 왼쪽 회전 여부
    for(int i=idx; i>0; --i){
        if(magnet[i][6]!=magnet[i-1][2]) dirs[i-1] = -dirs[i];
        else break;
    }

    //자석 오른쪽 회전 여부
    for(int i=idx; i<3; ++i){
        if(magnet[i][2]!=magnet[i+1][6]) dirs[i+1] = -dirs[i];
        else break;
    }

    //자석 실제 회전
    for(int i=0; i<4; ++i){
        if(dirs[i]==1){
            magnet[i].push_front(magnet[i].back());
            magnet[i].pop_back();
        }
        else if(dirs[i]==-1){
            magnet[i].push_back(magnet[i].front());
            magnet[i].pop_front();
        }
    }
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        int k;
        std::vector<std::deque<int>> magnet(4);

        cin>> k;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 8; ++j) {
                int tmp;
                cin >> tmp;
                magnet[i].push_back(tmp);
            }
        }

        for(int i=0; i<k; ++i){
            int rot_num, rot_dir;
            cin>>rot_num>>rot_dir;
            RotateMagnet(magnet, rot_dir, rot_num);
        }

        int score = 0;
        for (int i = 0; i < 4; ++i) {
            score |= (magnet[i][0] << i);
        }

        cout << "#" << test_case << " " <<score << '\n';
	}
	return 0;
}