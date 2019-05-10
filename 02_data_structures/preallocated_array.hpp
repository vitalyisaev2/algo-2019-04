#ifndef PREALLOCATED_ARRAY_HPP
#define PREALLOCATED_ARRAY_HPP

#include "dynamic_array.hpp"
#include "utils.hpp"

// абстрактный класс динамического массива, который оптимизирует количество аллокаций
template <typename T>
class PreallocatedArray : public DynamicArray<T>
{
  public:
    PreallocatedArray() : array_(nullptr), size_(0), capacity_(0){};

    PreallocatedArray(size_t capacity) : array_(new T[capacity]), size_(0), capacity_(capacity){};

    ~PreallocatedArray()
    {
        if (array_ != nullptr) {
            delete[] array_;
            array_ = nullptr;
        }
    }

    // добавляет элемент в конец массива
    void add(T item) override
    {
        if (mustGrow()) {
            resize(Grow);
        }
        array_[size_] = item;
        size_++;
    };

    // вставляет элемент по индексу со сдвигом хвоста массива вправо
    void add(T item, size_t index) override
    {
        if (mustGrow()) {
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
        if (mustShrink()) {
            resize(Shrink);
        }

        return item;
    };

    // возвращает актуальный размер массива
    size_t size() const override
    {
        return size_;
    };

  protected:
    // mustGrow проверяет, необходимо ли аллоцировать дополнительную память
    virtual bool mustGrow() const = 0;

    // mustShrink провереят, необходимо ли выполнить освобождение незанятой памяти
    virtual bool mustShrink() const = 0;

    // resize увеличивает или снижает размер внутреннего массива в соответcтвии со стратегией,
    // которая зависит от имплементации класса
    virtual void resize(ResizeMode mode) = 0;

    T*     array_;
    size_t size_;
    size_t capacity_;
};

#endif