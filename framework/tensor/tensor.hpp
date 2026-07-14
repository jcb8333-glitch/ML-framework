#pragma once

#include <vector>
#include <ostream>


enum class DType {
    Float64,
    Float32,
    Float16,
    Int64,
    Int32,
    Int16,
    Bool,
    Unknown
};

template <typename T>

class Tensor {
    private:
        DType dType;
        std::vector<size_t> shape_;
        std::vector<T> data_;

    public:
        Tensor(std::vector<size_t> shape, const T& initial_val = T()) : shape_(std::move(shape)){
            size_t size = 1;
            for(auto dim : shape_) size *= dim;
            data_.assign(size, initial_val);
        };

        std::vector<T> data() const{
            return this->data_;
        };

        size_t size(){
            return data_.size();
        }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Tensor<T>& t){
        const auto& d = t.data();
        os << "[";
        for(size_t i = 0; i < d.size(); i++){
            os << d[i];
            if (i+1 < d.size()) os << ", ";
        }
        os << "]";
        return os;
    };