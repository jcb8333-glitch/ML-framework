#include <vector>
#include "../tensor/tensor.hpp"
#include <iostream>

class NeuralNet{
    private:

    public:
        template <typename T>
        Tensor<T> ReLU(Tensor<T> x){
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

    NeuralNet nn = NeuralNet();
    std::cout << x << std::endl;
    std::cout << nn.ReLU(x) << std::endl;
}