#include <iostream>
#include <string>
#include <utility>

// ==========================================
// [1단계] 기본 함수 템플릿과 암시적 인스턴스화
// ==========================================
// TODO: T 타입을 매개변수로 받아 두 수의 합을 리턴하는 함수 템플릿 'add'를 작성하세요.
template <typename T> T add(T a, T b){
    return a+b;
}


// ==========================================
// [2단계] 다중 템플릿 매개변수와 auto 리턴 타입
// ==========================================
// TODO: T1, T2를 매개변수로 받고, auto 리턴 타입을 이용해 두 값의 곱을 리턴하는 함수 템플릿 'multiply'를 작성하세요.
template <typename T1, typename T2>
auto multiply(T1 a, T2 b){
    return a*b;
}


// ==========================================
// [3단계] 레퍼런스 매개변수와 const 제약
// ==========================================
// TODO 1: const T&를 받아 값을 출력하는 템플릿 함수 'printValue' 작성
template <typename T>
void printValue(const T& x){
    std::cout << x << '\n';
}

// TODO 2: T&를 받아 값을 100으로 수정하는 템플릿 함수 'modifyValue' 작성
template <typename T>
void modifyValue(T& x){
    x = 100;
}


// ==========================================
// [4단계] 포워드 레퍼런스와 완벽한 전달
// ==========================================
void targetFunction(int& x) {
    std::cout << " [타겟] Lvalue 버전 호출됨!\n";
}

void targetFunction(int&& x) {
    std::cout << " [타겟] Rvalue 버전 호출됨!\n";
}

// TODO: T&& (포워드 레퍼런스)를 매개변수로 받고, std::forward를 이용해 targetFunction으로 완벽하게 전달하는 wrapper 함수 작성
template <typename T>
void wrapper(T&& arg){
    targetFunction(std::forward<T>(arg));
}


int main() {
    std::cout << "=== 1단계 테스트 ===" << std::endl;
    std::cout <<add(3, 5)<< std::endl;
    std::cout <<add(3.14, 2.71)<< std::endl;
    std::cout <<add(std::string("Hello "), std::string("Template!"))<< std::endl;


    std::cout << "\n=== 2단계 테스트 ===" << std::endl;
    std::cout <<multiply(3, 3.14) << std::endl;


    std::cout << "\n=== 3단계 테스트 ===" << std::endl;
    int a = 10;
    const int b = 20;
    printValue(a);
    printValue(b);
    modifyValue(a);
    printValue(a);
    //modifyValue(b); 오류 발생


    std::cout << "\n=== 4단계 테스트 ===" << std::endl;
    int val = 5;
    wrapper(val);
    wrapper(10);
    return 0;
}