#ifndef SINGLE_ARRAY_HPP
#define SINGLE_ARRAY_HPP

#include "copy.hpp"
#include "dynamic_array.hpp"
#include <iostream>

template <typename T>
class SingleArray : public DynamicArray<T>
{
  public:
    SingleArray() : array_(nullptr), size_(0){};

    ~SingleArray()
    {
        if (array_ != nullptr) {
            delete[] array_;
        }
    }

    void add(T item) override
    {
        resizeWithShiftRight(size_);
        array_[size_ - 1] = item;
    };

    void add(T item, size_t index) override
    {
        if (index > size_) {
            throw "index value to big when trying to add value to single array";
        }
        resizeWithShiftRight(index);
        array_[index] = item;
    };

    virtual T get(size_t index) const override
    {
        if (index > size_) {
            throw "index value to big when trying to get value frome single array";
        }
        return array_[index];
    };

    virtual T remove(size_t index) override
    {
        if (index > size_) {
            throw "index value to big when trying to remove value from single array";
        }
        auto value = array_[index];
        resizeWithShiftLeft(index);
        return value;
    };

    virtual size_t size() const
    {
        return size_;
    };

  private:

    // resizeWithShiftRight создаёт новый массив большей длины
    // и копирует старый массив в новый, после чего удаляет старый;
    // from указывает на индекс свободной ячейки, начиная с которой
    // новые величины будут сдвинуты вправо
    void resizeWithShiftRight(size_t from)
    {
        auto old_ = array_;
        array_    = new T[size_ + 1];

        // копируется голова массива
        copyPointerArray<T>(old_, array_, from);

        // при необходимости копируется хвост массива
        if (from < size_) {
            copyPointerArray<T>(old_ + from, array_ + from + 1, size_ - from);
        }

        // память из-под старого массива освобождается
        delete[] old_;
        size_++;
    };

    // resizeWithShiftLeft создаёт новый массив меньшей длины
    // и копирует старый массив в новый, после чего удаляет старый;
    // from указывает на индекс свободной ячейки, начиная с которой
    // новые величины будут сдвинуты влево
    void resizeWithShiftLeft(size_t from)
    {
        if (size_ == 0) {
            throw "trying to reduce size of empty array_";
        }

        if (from > size_) {
            throw "shift point must not be greater than size";
        }

        // если в массиве ничего не осталось, зануляем указатель
        if (size_ == 1) {
            delete[] array_;
            array_ = nullptr;
            size_  = 0;
            return;
        }

        auto old_ = array_;
        array_    = new T[size_ - 1];
        // при необходимости копируется голова массива
        if (from != 0) {
            copyPointerArray<T>(old_, array_, from);
        }

        // копируется хвост массива
        copyPointerArray<T>(old_ + from + 1, array_ + from, size_ - from - 1);

        // память из-под старого массива освобождается
        delete[] old_;
        size_--;
    };

    T*     array_;
    size_t size_;
};

#endif