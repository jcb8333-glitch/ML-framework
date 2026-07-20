#include <vector>
#include "../tensor/tensor.hpp"
#include <iostream>

class Model {
    private:
        Tensor<double> data;
};

class Linear {

    private:
        Tensor<double> weights_;
        double bias_;

    public:
        Linear(size_t inFeats, size_t outFeats, bool bias=true)
            : weights_({inFeats}, 0.0), bias_(0.5) {
        }

        template <typename T>
        Tensor<T> activate(Tensor<T>& x){
            Tensor<T> y = Tensor<T>::multiply(x, Tensor<T>::transpose(weights_));
            auto& d = y.data();
            for(size_t i = 0; i < y.size(); ++i){
                d[i] += bias_;
            }
            return y;
        }

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

}