#include <iostream>
#include <string>


std::string text = "Hello C++";
const std::string& ref = text;

auto a = ref;          // 타입은 std::string (const와 &가 모두 떨어지고 복사됨)
const auto b = ref;    // 타입은 const std::string (const는 유지되지만 복사됨)
auto& c = ref;         // 타입은 const std::string& (const와 레퍼런스가 모두 유지됨)




int A = 10;
int& Ref = A; // ref는 int& (레퍼런스)

auto B = Ref;          // b의 타입은 int (레퍼런스와 const가 탈락하고 복사됨)
decltype(Ref) C = A;   // c의 타입은 int& (레퍼런스 속성이 그대로 유지됨)



//Trailing Return Type (C++11)
template <typename T1, typename T2>
auto add(T1 a, T2 b) -> decltype(a + b) {
    return a + b; // a와 b를 더한 연산의 결과 타입으로 반환 타입이 결정됨
}

//decltype(x) 선언된 타입 그대로
//decltype((x)) x를 표현식으로 취급, 표현식은 Lvalue 판정, 해당 타입의 레퍼런스가 결과





// typedef 방식
typedef int (*FuncPtr)(int, int);

// using 방식
using FuncPtr = int(*)(int, int);

//using 만 Alias Template 가능
template <typename T>
using StringIntMap = std::map<T, int>;

int main() {
    // T 자리에 int를 넣으면 std::map<int, int>가 됩니다.
    StringIntMap<int> myMap; 
}