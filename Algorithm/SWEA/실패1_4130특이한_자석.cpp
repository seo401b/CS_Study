#include <iostream>
#include <vector>
#include <deque>

using namespace std;

void RotateMagnet(std::vector<std::deque<int>>& magnet, int rot_dir, int rot_num){
    if(rot_num==1 && rot_dir==1){
        if(magnet[0][2]!=magnet[1][6]) RotateMagnet(magnet, -1, 2);
        magnet[0].push_front(magnet[0].back());
        magnet[0].pop_back();
    }
    if(rot_num==1 && rot_dir==-1){
        if(magnet[0][2]!=magnet[1][6]) RotateMagnet(magnet, 1, 2);
        magnet[0].push_back(magnet[0].front());
        magnet[0].pop_front();
    }

    if(rot_num==2 && rot_dir==1){
        if(magnet[1][6]!=magnet[0][2]) RotateMagnet(magnet, -1, 0);
        if(magnet[1][2]!=magnet[2][6]) RotateMagnet(magnet, -1, 3);
        magnet[1].push_front(magnet[1].back());
        magnet[1].pop_back();
    }
    if(rot_num==2 && rot_dir==-1){
        if(magnet[1][6]!=magnet[0][2]) RotateMagnet(magnet, 1, 0);
        if(magnet[1][2]!=magnet[2][6]) RotateMagnet(magnet, 1, 3);
        magnet[1].push_back(magnet[1].front());
        magnet[1].pop_front();
    }

    if(rot_num==3 && rot_dir==1){
        if(magnet[2][6]!=magnet[1][2]) RotateMagnet(magnet, -1, 2);
        if(magnet[2][2]!=magnet[3][6]) RotateMagnet(magnet, -1, 4);
        magnet[2].push_front(magnet[2].back());
        magnet[2].pop_back();
    }
    if(rot_num==3 && rot_dir==-1){
        if(magnet[2][6]!=magnet[1][2]) RotateMagnet(magnet, 1, 2);
        if(magnet[2][2]!=magnet[3][6]) RotateMagnet(magnet, 1, 4);
        magnet[2].push_back(magnet[2].front());
        magnet[2].pop_front();
    }

    if(rot_num==4 && rot_dir==1){
        if(magnet[4][6]!=magnet[3][2]) RotateMagnet(magnet, -1, 3);
        magnet[3].push_front(magnet[3].back());
        magnet[3].pop_back();
    }
    if(rot_num==4 && rot_dir==-1){
        if(magnet[4][6]!=magnet[3][2]) RotateMagnet(magnet, 1, 3);
        magnet[3].push_back(magnet[3].front());
        magnet[3].pop_front();
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
        int score = 0;

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
        score << magnet[3].front();
        score << magnet[2].front();
        score << magnet[1].front();
        score << magnet[0].front();

        cout << "#" << test_case << score << '\n';
	}
	return 0;
}
//시계 방향 1이면 00100100 -> 00010010 앞에 맨뒤엣걸 붙임
//화살표를 움직이는 방법으로 풀겠다


//무한 재귀함수 호출 및 자석을 먼저 바꾸고 값을 읽어 오류 발생
//값을 먼저 읽자니 돌아가는지 안돌아가는지 여부가 중요해 문제가 생김
//그럼 회전여부를 어딘가에 저장하고 돌려보자 