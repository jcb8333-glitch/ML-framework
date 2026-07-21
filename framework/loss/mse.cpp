#include "../tensor/tensor.hpp"
#include <cmath>

template <typename T>
class MSEloss{

    public:
        MSEloss(){

        }

        Tensor<T> loss(Tensor<T>& actual, Tensor<T>& prediction){
            Tensor<T> diff = Tensor<T>::subtract(prediction, actual);

            Tensor<T> square = diff;
            auto& data = square.data();
            for(auto i = 0uz; i < data.size(); ++i){
                data[i] = d[i] * d[i];
            }
            return Tensor<T>::mean(square);
        }
};