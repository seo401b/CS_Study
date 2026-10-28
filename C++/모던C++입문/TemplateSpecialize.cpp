//Full Specialization
#include <iostream>
#include <string>

template <typename T>
class Printer {
public:
    void print(T val) {
        std::cout << "General Type: " << val << "\n";
    }
};

template <>
class Printer<bool> {
public:
    void print(bool val){
        std::cout << "specialized for bool" << '\n';
    }
};

//함수 템플릿 특수화는 금지
//컴파일러 동작 순서
//1. 일반 템플릿 중 가장 적합한 후보 적용
//2. 없다면 템플릿 특수화 버젼 확인
//일반 템플릿이 적용될 가능성이 있음 -> 유지보수 지옥

//대안으로 일반 함수 오버로딩을 추천


//Partial Specialization

template <typename T1, typename T2>
struct Pair {
    void print() { std::cout << "General Version\n"; }
};

template <typename T1>
struct Pair<T1, int>{
    void print() {std::cout << "Partial Specialization\n";}
};