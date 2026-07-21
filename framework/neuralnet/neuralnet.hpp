#pragma once

#include <vector>
#include "../tensor/tensor.hpp"
#include <iostream>

template <typename T>
class Linear {

    private:
        Tensor<T> weights_;
        T bias_;

    public:
        Linear(size_t inFeats, size_t outFeats, bool bias=true)
            : weights_({inFeats}, T(0.0)), bias_(T(0.5)) {
        }

        Tensor<T> activate(Tensor<T>& x){
            Tensor<T> y = Tensor<T>::multiply(x, Tensor<T>::transpose(weights_));
            auto& data = y.data();
            for(size_t i = 0; i < y.size(); ++i){
                data[i] += bias_;
            }
            return y;
        }

};

template <typename T>
class ReLU {

    public:
        ReLU(){}

        Tensor<T> relu(Tensor<T> x){
            auto& data = x.data();
            for(size_t i = 0; i < x.size(); ++i){
                if(data[i] < 0) data[i] = 0;
            }
            return x;
        }

};