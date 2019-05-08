#ifndef SINGLE_ARRAY
#define SINGLE_ARRAY

#include "dynamic__array.hpp"
#include <algorithm>
#include <iterator>

template <typename T>
class SingleArray : public DynamicArray
{
  public:
    SingleArray() : _array(new T[0]), size(0){};

    virtual void add(T item) override
    {
        resizeWithShiftRight(size);
        _array[size - 1] = T;
    };

    virtual void add(T item, int index) override
    {
        resizeWithShiftRight(index);
        _array[index] = T;
    };

    virtual T get(int index) const override
    {
        return _array[index];
    };

    virtual T remove(int index) override{

    };
    virtual size_t size() const {return _size};

  private:
    // resizeWithShiftRight создаёт новый массив увеличенной длины
    // и копирует старый массив в новый, после чего удаляет старый;
    // from указывает на индекс свободной ячейки, начиная с которой
    // новые величины будут сдвинуты вправо
    void resizeWithShiftRight(size_t from)
    {
        auto old = _array;
        _array   = new T[_size + 1];
        // копируются голова массива
        {
            auto old_begin = std::begin(old);
            auto old_end   = std::advance(std::begin(old), from);
            auto new_begin = std::begin(_array) std::copy(old_begin, old_end, new_begin);
        }
        // при необходимости копируется хвост массива
        if (from < _size)
            {
                auto old_begin = std::advance(std::begin(old), from + 1);
                auto old_end   = std::end(old);
                auto new_begin = std::advance(std::begin(_array), from);
                std::copy(old_begin, old_end, new_begin);
            }
        delete[] old;
        _size++;
    };

    // resizeWithShiftLeft создаёт новый массив уменьшенной длины
    // и копирует старый массив в новый, после чего удаляет старый;
    // from указывает на индекс свободной ячейки, начиная с которой
    // новые величины будут сдвинуты вправо
    void resizeWithShiftLeft(size_t from)
    {
        if (size == 0)
            {
                throw "trying to reduce size of empty _array";
            }

        if (from > size)
            {
                throw "shift point must not be greater than size";
            }

        auto old = _array;
        _array   = new T[size - 1];
        // при необходимости копируется голова массива
        if (from != 0)
            {
                auto old_begin = std::begin(old);
                auto old_end   = std::advance(std::begin(old), from - 1);
                auto new_begin = std::begin(_array);
                std::copy(old_begin, old_end, new_begin);
            }
        // копируется хвост массива
        {
            auto old_begin = std::advance(std::begin(old), from);
            auto old_end   = std::end(old);
            auto new_begin = std::advance(std::begin(_array), from);
            std::copy(old_begin, old_end, new_begin);
        }
        delete[] old;
        _size++;
    };

    [] T   _array;
    size_t _size;
};

#endif