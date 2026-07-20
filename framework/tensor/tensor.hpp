#pragma once

#include <vector>
#include <string>
#include <ostream>
#include <algorithm>

enum class DType {
    Float64, Float32, Float16,
    Int64, Int32, Int16,
    Bool, Unknown
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

            for (size_t i = 0; i < dimSize; ++i){
                if (dim == shape_.size() - 1){
                    out += std::to_string(data_[offset + i]);
                } else {
                    out += dimParse(dim + 1, offset + i * innerStride, innerStride);
                }
                if (i + 1 < dimSize) out += ", ";
            }
            out += "]";
            return out;
        }

    public:
        Tensor(std::vector<size_t> shape, const T& initial_val = T()) : shape_(std::move(shape)){
            size_t size = 1;
            for(auto dim : shape_) size *= dim;
            data_.assign(size, initial_val);
            computeStrides();
        }

        static Tensor<T> clone(const Tensor<T>& t){
            return t;
        }

        static Tensor<T> transpose(const Tensor<T>& t){
            std::vector<size_t> newShape = t.shape();
            std::reverse(newShape.begin(), newShape.end());
            Tensor<T> transposed(newShape);
            for(size_t i = 0; i < t.size(); ++i){
                std::vector<size_t> indices(t.shape().size());
                size_t offset = i;
                for(size_t j = 0; j < t.shape().size(); ++j){
                    indices[j] = offset / t.strides_[j];
                    offset %= t.strides_[j];
                }
                std::reverse(indices.begin(), indices.end());
                size_t newOffset = 0;
                for(size_t j = 0; j < indices.size(); ++j){
                    newOffset += indices[j] * transposed.strides_[j];
                }
                transposed.data()[newOffset] = t.data()[i];
            }
            return transposed;
        }

        template <typename... Idx>
        T& operator()(Idx... idx) {
            std::vector<size_t> indices{static_cast<size_t>(idx)...};
            size_t offset = 0;
            for (size_t i = 0; i < indices.size(); ++i){
                offset += indices[i] * strides_[i];
            }
            return data_[offset];
        }

        template <typename... Idx>
        const T& operator()(Idx... idx) const {
            std::vector<size_t> indices{static_cast<size_t>(idx)...};
            size_t offset = 0;
            for (size_t i = 0; i < indices.size(); ++i){
                offset += indices[i] * strides_[i];
            }
            return data_[offset];
        }

        std::vector<T>& data() {
            return data_;
        }
        const std::vector<T>& data() const {
            return data_;
        }

        size_t size() const {
            return data_.size();
        }

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
    os << "Tensor(" << t.toString() << ")";
    return os;
}