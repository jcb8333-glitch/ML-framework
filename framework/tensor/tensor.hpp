#pragma once

#include <vector>
#include <string>
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

        std::string dimParse(size_t dim, size_t offset, size_t stride) const{
            std::string out = "[";
            size_t dimSize = shape_[dim];
            size_t innerStride = stride / dimSize;

            bool isInner = (dim == shape_.size() - 1);
            
            for( size_t i = 0; i < dimSize; ++i){
                if (isInner){
                    out += std::to_string(data_[offset + i]);
                } else {
                    out += dimParse(dim+1, offset + i * innerStride, innerStride);
                }
                if (i + 1 < dimSize){
                    out += isInner ? ", " : ",\n ";
                }
            }
            out += "]";
            return out;
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
            return data_;
        };

        // Get size of tensor
        size_t size(){
            return data_.size();
        }

        // Get vector describing shape of tensor
        const std::vector<size_t>& shape() const {
            return shape_;
        }

        std::string toString() const {
            if (shape_.empty()) return "[]";
            return dimParse(0, 0, data_.size());
        }
    };
template <typename T>
std::ostream& operator<<(std::ostream& os, const Tensor<T>& t) {
    os << t.toString();
    return os;
};  