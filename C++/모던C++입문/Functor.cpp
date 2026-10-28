#include <iostream>
#include <cmath>

double fin_diff(double f(double), double x, double h){
    return (f(x+h)-f(x))/h;
}

double sin_plus_cos(double x){
    return sin(x)+cos(x);
}

// int main(){
//     std::cout << fin_diff(sin_plus_cos, 1., 0.001) << '\n';
//     std::cout << fin_diff(sin_plus_cos, 0., 0.001) << '\n';
// }
//n계도함수에서 n의 값을 알아내거나 fin_diff(fin_diff)처럼 이계도함수를 못구하는 상황
//functor/functional obj 사용 -> 매개변수 내부 상태 유지

class psc_f
{
private: double alpha;
public:
    psc_f(double alpha) : alpha(alpha) { }
    double operator() (double x) const{
        return sin(alpha * x) + cos(x);
    }
};

int main(){
    psc_f my_f(2.0);

    double result = my_f(1.0);
}
