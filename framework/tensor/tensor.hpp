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
        std::vector<size_t> strides_;
        std::vector<T> data_;

        void computeStrides() {
            strides_.resize(shape_.size());
            size_t acc = 1;
            for(size_t i = shape_.size(); i-- > 0;){
                strides_[i] = acc;
                acc *= shape_[i];
            }
        }

    public:
        // Constructor
        Tensor(std::vector<size_t> shape, const T& initial_val = T()) : shape_(std::move(shape)){
            size_t size = 1;
            for(auto dim : shape_) size *= dim;
            data_.assign(size, initial_val);
            computeStrides();
        };  

        // Indexing non-const
        template <typename... Idx>
        T& operator()(Idx... idx) {
            std::vector<size_t> indices{static_cast<size_t>(idx)...};
            size_t offset = 0;
            for (size_t i = 0; i < indices.size(); ++i){
                offset += indices[i] * strides_[i];
            }
            return data_[offset];
        }
        // Indexing const
        template <typename... Idx>
        const T& operator()(Idx... idx) const {
            std::vector<size_t> indices{static_cast<size_t>(idx)...};
            size_t offset = 0;
            for (size_t i = 0; i < indices.size(); ++i){
                offset += indices[i] * strides_[i];
            }
            return data_[offset];
        }

        //Get data stored in tensor
        std::vector<T> data() const{
            return this->data_;
        };

        // Get size of tensor
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