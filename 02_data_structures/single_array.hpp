#ifndef SINGLE_ARRAY
#define SINGLE_ARRAY

#include "dynamic_array.hpp"
#include <algorithm>
#include <iterator>

template <typename T> copyPointerArray(T* from, T** to, size_t num);

template <typename T>
class SingleArray : public DynamicArray<T>
{
  public:
    SingleArray() : array_(new T[0]), size_(0){};

    ~SingleArray() {
        if (array_ != nullptr) {
            delete array_;
        }
    }

    void add(T item) override
    {
        resizeWithShiftRight(size_);
        array_[size_ - 1] = item;
    };

   void add(T item, size_t index) override
    {
        if (index > size_)
            {
                throw "index value to big when trying to add value to single array";
            }
        resizeWithShiftRight(index);
        array_[index] = item;
    };

    virtual T get(size_t index) const override
    {
        return array_[index];
    };

    virtual T remove(size_t index) override
    {
        if (index > size_)
            {
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
        auto old = array_;
        array_   = new T[size_ + 1];
        // копируются голова массива
        {
            auto old_begin = std::begin(old);
            auto old_end   = std::advance(std::begin(old), from);
            auto new_begin = std::begin(array_);
            std::copy(old_begin, old_end, new_begin);
        }
        // при необходимости копируется хвост массива
        if (from < size_)
            {
                auto old_begin = std::advance(std::begin(old), from + 1);
                auto old_end   = std::end(old);
                auto new_begin = std::advance(std::begin(array_), from);
                std::copy(old_begin, old_end, new_begin);
            }
        delete[] old;
        size_++;
    };

    // resizeWithShiftLeft создаёт новый массив меньшей длины
    // и копирует старый массив в новый, после чего удаляет старый;
    // from указывает на индекс свободной ячейки, начиная с которой
    // новые величины будут сдвинуты влево
    void resizeWithShiftLeft(size_t from)
    {
        if (size == 0)
            {
                throw "trying to reduce size of empty array_";
            }

        if (from > size)
            {
                throw "shift point must not be greater than size";
            }

        // если в массиве ничего не осталось, зануляем указатель
        if (size == 1) {
            delete[] array_;
            array_ = nullptr;
            size = 0;
            return;
        }
        

        auto old = array_;
        array_   = new T[size - 1];
        // при необходимости копируется голова массива
        if (from != 0)
            {
                auto old_begin = std::begin(old);
                auto old_end   = std::advance(std::begin(old), from - 1);
                auto new_begin = std::begin(array_);
                std::copy(old_begin, old_end, new_begin);
            }
        // копируется хвост массива
        {
            auto old_begin = std::advance(std::begin(old), from);
            auto old_end   = std::end(old);
            auto new_begin = std::advance(std::begin(array_), from);
            std::copy(old_begin, old_end, new_begin);
        }
        delete[] old;
        size_--;
    };

    T*     array;
    size_t size_;
};

#endif