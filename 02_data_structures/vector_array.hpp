#ifndef VECTOR_ARRAY_HPP
#define VECTOR_ARRAY_HPP

#include "preallocated_array.hpp"

template <typename T>
class VectorArray : public PreallocatedArray<T>
{
  public:
    VectorArray() : VectorArray(2){};

    VectorArray(size_t step) : step_(step){};

  protected:
    bool mustGrow() const override
    {
        return this->size_ == this->capacity_;
    }

    bool mustShrink() const override
    {
        return this->size_ == this->capacity_ - this->step_;
    }

    // resize увеличивает или снижает размер внутреннего массива на постоянное число (step_) элементов
    void resize(ResizeMode mode)
    {
        auto old_ = this->array_;
        switch (mode) {
        case Grow:
            this->array_ = new T[this->capacity_ += this->step_];
            break;
        case Shrink:
            this->array_ = new T[this->capacity_ -= this->step_];
            break;
        default:
            throw "unexpected resize mode";
        }
        copyPointerArray<T>(old_, this->array_, this->size_);
        delete[] old_;
    }

  private:
    const size_t step_;
};

#endif