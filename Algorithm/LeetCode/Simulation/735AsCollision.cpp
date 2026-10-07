#include <iostream>
#include <vector>

class Solution {
private:
    std::vector<int> StackSolver(std::vector<int>& asteroids) {
        std::vector<int> result;

        for(int a: asteroids){
            bool isdestroyed = false;

            while(!result.empty() && result.back()>0 && a<0){
                if(result.back()< -a){
                    result.pop_back();
                    continue;
                }
                else if(result.back()==-a){
                    result.pop_back();
                }
                isdestroyed = true;
                break;
            }

            if(!isdestroyed){
                result.push_back(a);
            }
        }
        return result;
    }

public:
    std::vector<int> asteroidCollision(std::vector<int>& asteroids) {
        return StackSolver(asteroids);
    }
};

/*
수행이 아니라 시나리오
조건문으로 모든 상황을 수행하려하면 꼬임
여기서 플래그 변수를 두면
지금 보는 a의 행성이 어떻게 되는지만 집중해보자.
플래그 변수에 따라 푸쉬하냐 마냐
그리고 플래그 변수 산출과정 중 기존 result를 팝하든 푸쉬하든
여기서 두개의 로직으로 갈린다

상태가 여러개 꼬인다면 컴퓨터에게 플래그를 하나 쥐어주고 
에잇몰라 탈출시키자
그럼 밖에서 플래그만 보고 판단 가능하다.
*/