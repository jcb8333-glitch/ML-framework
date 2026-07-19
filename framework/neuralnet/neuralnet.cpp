#include <vector>
#include "../tensor/tensor.hpp"
#include <iostream>

class module{
    private:

    public:

};

class ReLU {

    public:
        ReLU(){}

        template <typename T>
        Tensor<T> relu(Tensor<T> x){
            auto& data = x.data();
            for(size_t i = 0; i < x.size(); ++i){
                if(data[i] < 0) data[i] = 0;
            }
            return x;
        }

};

int main(){
    Tensor x = Tensor({2,2}, 0);
    x(0,0) = 1;
    x(0,1) = -2;
    x(1,0) = 3;
    x(1,1) = -4;
    std::cout << x << std::endl;
}