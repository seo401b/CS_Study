#include <iostream>
#include <algorithm>
#include <utility> // std::exchange 또는 std::move 사용 시 유용

class MyBuffer {
private:
    int* m_data;
    size_t m_size;

public:
    // 1. 기본 생성자 및 매개변수 생성자 (변환 생성자 방지를 위해 explicit 고려)
    explicit MyBuffer(size_t size = 0) 
        : m_size(size), m_data(size > 0 ? new int[size] {} : nullptr) {
        std::cout << "[Constructor] 기본/매개변수 생성자 호출\n";
    }

    // 2. 소멸자
    ~MyBuffer() {
        std::cout << "[Destructor] 소멸자 호출 (m_size: " << m_size << ")\n";
        // TODO: 할당된 자원(m_data) 해제하기
        delete[] m_data;
    }

    // 3. 복사 생성자 (깊은 복사)
    MyBuffer(const MyBuffer& other) 
        : m_size(other.m_size), m_data(other.m_size > 0 ? new int[other.m_size] : nullptr) {
        std::cout << "[Copy Constructor] 복사 생성자 호출 (깊은 복사)\n";
        // TODO: other.m_data의 내용을 새로 할당된 m_data로 복사하기 (std::copy 등 활용)
        std::copy(other.m_data, other.m_data+other.m_size, m_data);
    }

    // 4. 복사 대입 연산자 (Copy Assignment Operator)
    MyBuffer& operator=(const MyBuffer& other) {
        std::cout << "[Copy Assignment] 복사 대입 연산자 호출\n";
        
        // TODO 1: 자기 자신 대입(Self-Assignment) 방지 처리하기
        if(this == &other) return *this;
        // TODO 2: 기존 내 자원 해제 및 새 크기에 맞추어 깊은 복사 수행하기
        delete[] m_data;
        m_size = other.m_size;
        m_data = (m_size>0) ? new int[m_size] : nullptr;
        if(m_size>0) {
            std::copy(other.m_data, other.m_data+other.m_size, m_data);
        }
        // TODO 3: *this 반환하기
        return *this;
    }

    // 5. 이동 생성자 (Move Constructor)
    // 원본 객체의 자원을 훔쳐오고, 원본은 안전한 상태(nullptr 등)로 초기화
    MyBuffer(MyBuffer&& other) noexcept 
        : m_data(other.m_data), m_size(other.m_size) {
        std::cout << "[Move Constructor] 이동 생성자 호출\n";
        
        // TODO: 원본 객체(other)의 멤버를 비우기
        other.m_data = nullptr;
        other.m_size = 0;
    }

    // 6. 이동 대입 연산자 (Move Assignment Operator)
    MyBuffer& operator=(MyBuffer&& other) noexcept {
        std::cout << "[Move Assignment] 이동 대입 연산자 호출\n";
        
        // TODO 1: 자기 자신 대입 방지 처리하기
        if(this == &other) return *this;
        // TODO 2: 내 기존 자원 해제하기
        delete[] m_data;
        // TODO 3: other의 자원과 크기를 이전받기
        m_size = other.m_size;
        m_data = other.m_data;
        // TODO 4: other 객체 비우기 (m_data = nullptr, m_size = 0)
        other.m_data = nullptr;
        other.m_size = 0;
        // TODO 5: *this 반환하기
        return *this;
    }

    // 유틸리티 함수: 데이터 확인용
    size_t size() const { return m_size; }
    int* data() const { return m_data; }
};
//생성자에선 m_size(other.m_size) 등의 초기화 리스트 사용 -> 처음 생기기 때문
//대입연산자에선 일반 코드처럼 m_size = ...; 형태 -> 이미 잘 살고 있다 갑자기 호출

int main() {
    std::cout << "--- 1. 객체 생성 ---\n";
    MyBuffer buf1(100);

    std::cout << "\n--- 2. 복사 생성자 테스트 ---\n";
    MyBuffer buf2 = buf1; // 복사

    std::cout << "\n--- 3. 이동 생성자 테스트 ---\n";
    MyBuffer buf3(std::move(buf1)); // 이동

    std::cout << "\n--- 4. 복사 대입 테스트 ---\n";
    MyBuffer buf4(50);
    buf4 = buf2; // 복사 대입

    std::cout << "\n--- 5. 이동 대입 테스트 ---\n";
    MyBuffer buf5(10);
    buf5 = std::move(buf3); // 이동 대입

    std::cout << "\n--- 프로그램 종료 (소멸자 연쇄 호출) ---\n";
    return 0;
}