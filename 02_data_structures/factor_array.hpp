#ifndef FACTOR_ARRAY_HPP
#define FACTOR_ARRAY_HPP

#include "preallocated_array.hpp"

template <typename T>
class FactorArray : public PreallocatedArray<T>
{
  public:
    FactorArray() : PreallocatedArray<T>(1), factor_(2) {}

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
        auto old_ = this->array_;
        switch (mode) {
        case Grow:
            this->array_ = new T[this->capacity_ *= this->factor_];
            break;
        case Shrink:
            this->array_ = new T[this->capacity_ /= this->factor_];
            break;
        default:
            throw "unexpected resize mode";
        }
        copyPointerArray<T>(old_, this->array_, this->size_);
        delete[] old_;
    }

  private:
    const size_t factor_;
};

#endif