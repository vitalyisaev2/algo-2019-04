#ifndef VECTOR_ARRAY_HPP
#define VECTOR_ARRAY_HPP

#include "dynamic_array.hpp"
#include "utils.hpp"

template <typename T>
class VectorArray : public DynamicArray<T>
{
  public:
    VectorArray() : VectorArray(2){};

    VectorArray(size_t step) : array_(nullptr), size_(0), capacity_(0), step_(step){};

    ~VectorArray() {
        if (array_ != nullptr) {
            delete[] array_;
            array_ = nullptr;
        }
    }

    // добавляет элемент в конец массива
    void add(T item) override
    {
        if (size_ == capacity_) {
            resize(Grow);
        }
        array_[size_] = item;
        size_++;
    };

    // вставляет элемент по индексу со сдвигом хвоста массива вправо
    void add(T item, size_t index) override
    {
        if (size_ == capacity_) {
            resize(Grow);
        }
        shiftPointerArrayRight<T>(array_ + index, size_ - index);
        array_[index] = item;
        size_++;
    }

    // извлекает элемент массива по индексу
    T get(size_t index) const override
    {
        return array_[index];
    }

    // удаляет элемент массива со сдвигом хвоста массива влево
    T remove(size_t index) override
    {
        T item = array_[index];
        shiftPointerArrayLeft<T>(array_ + index, size_ - index - 1);
        size_--;

        // если данных осталось слишком мало, освобождаем память
        if (size_ == capacity_ - step_) {
            resize(Shrink);
        }

        return item;
    };

    // возвращает актуальный размер массива
    size_t size() const override
    {
        return size_;
    };

  private:
    enum ResizeMode {
        Grow,
        Shrink,
    };

    // resize увеличивает или снижает размер внутреннего массива на постоянное число (step_) элементов
    void resize(ResizeMode mode)
    {
        auto old_ = array_;
        switch (mode) {
        case Grow:
            array_ = new T[capacity_ += step_];
            break;
        case Shrink:
            array_ = new T[capacity_ -= step_];
            break;
        default:
            throw "unexpected resize mode";
        }
        copyPointerArray<T>(old_, array_, size_);
        delete[] old_;
    }

    T*           array_;
    size_t       size_;
    size_t       capacity_;
    const size_t step_;
};

#endif