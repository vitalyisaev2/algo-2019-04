#ifndef FACTOR_ARRAY_HPP
#define FACTOR_ARRAY_HPP

#include "preallocated_array.hpp"
#include <iostream>

template <typename T>
class FactorArray : public PreallocatedArray<T>
{
  public:
    FactorArray() : PreallocatedArray<T>(), factor_(2) {}

  protected:
    bool mustGrow() const override
    {
        return this->size_ == this->capacity_;
    }

    bool mustShrink() const override
    {
        return this->size_ == this->capacity_ / this->factor_;
    }

    // resize увеличивает или снижает размер внутреннего массива на постоянное число (step_) элементов
    void resize(ResizeMode mode) override
    {
        switch (mode) {
        case Grow:
            if (this->capacity_ == 0) {
                this->capacity_ = 1;
            } else {
                this->capacity_ *= this->factor_;
            }
            break;
        case Shrink:
            if (this->capacity_ == 0) {
                throw "zero capacity reached, cannot shrink more";
            } else {
                this->capacity_ /= this->factor_;
            }
            break;
        default:
            throw "unexpected resize mode";
        }
        auto old_ = this->array_;
        this->array_ = new T[this->capacity_];
        copyPointerArray<T>(old_, this->array_, this->size_);
        if (old_ != nullptr) {
            delete[] old_;
        }
    }

  private:
    const size_t factor_;
};

#endif