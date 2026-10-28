#include <iostream>

template<typename T>
T sum(const T* array, int n)
{
    T sum(0);
    for(int i = 0; i<n; ++i)
        sum+= array[i];
    return sum;
}

/*
T sum(0); 이유:
지역 변수 sum을 선언하고 0으로 초기화함.

배열의 크기를 n으로 전달하는 이유:
Pointer Decay 
배열을 인자로 넘길 때, 배열의 시작 주소만 전달함
*/

template<typename T>
struct list_entry
{
    list_entry(const T& value) : value(value), next(0) { }
    T   value;
    list_entry<T>* next;
};

template<typename T>
struct list
{
    list() : first(0), last(nullptr){ }
    ~list()
    {
        while(first){
            list_entry<T>* tmp = first->next;
            delete first;
            first = tmp;
        }
    }
    void append(const T& x)
    {
        last = (first ? last->next : first) = new list_entry<T>(x);
    }
    list_entry<T> *first, *last;
};


//++i vs i++
template<typename T>
class list_iterator {
private:
    list_entry<T>* entry;
public:
    list_iterator(list_entry<T>* e) : entry(e) {}
    //++i
    list_iterator<T>& operator++(){
        entry = entry -> next;
        return *this;
    }
    //i++
    list_iterator<T> operator++(int){
        list_iterator<T> temp = *this;
        ++(*this);
        return temp;
    }
};
//사전증가가 사후증가보다 성능이 좋다.

