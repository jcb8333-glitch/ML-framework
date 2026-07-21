#pragma once

#include "../tensor/tensor.hpp"
#include <cmath>


template <typename T>
class MSEloss{
    private:
        Tensor<float> lastDiff_;
    public:
        MSEloss() : lastDiff_({1}, T(0)){}

        Tensor<T> loss(Tensor<T>& actual, Tensor<T>& prediction){
            Tensor<T> diff = Tensor<T>::subtract(prediction, actual);

            lastDiff_ = diff;

            Tensor<T> square = diff;
            auto& data = square.data();
            for(size_t i = 0; i < data.size(); ++i){
                data[i] = data[i] * data[i];
            }
            return Tensor<T>::mean(square);
        }
};