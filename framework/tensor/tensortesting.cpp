#include <iostream>
#include <vector>
#include "tensor.hpp"

int main(){

    Tensor t0 = Tensor({0}, 0);
    Tensor t1 = Tensor({1}, 0);
    Tensor t2 = Tensor({2,2}, 0);
    Tensor t3 = Tensor({2,3}, 0);
    Tensor t4 = Tensor({3,3,3}, 0);
    Tensor t5 = Tensor({2,4,3}, 0);
    Tensor t6 = Tensor({4,4,4,4}, 0);
    std::cout << t0 << std::endl;
    std::cout << t1 << std::endl;
    std::cout << t2 << std::endl;
    std::cout << t3 << std::endl;
    std::cout << t4 << std::endl;
    std::cout << t5 << std::endl;
    std::cout << t6 << std::endl;
}