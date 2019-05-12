#ifndef STD_VECTOR_ARRAY_HPP
#define STD_VECTOR_ARRAY_HPP

#include <cstddef>
#include <iterator>
#include <vector>

// интерфейс динамического массива
template <typename T>
class StdVectorArray : public DynamicArray<T>
{
  public:
    // добавляет элемент в конец массива
    void add(T item) override
    {
        array_.push_back(item);
    }

    // вставляет элемент по индексу со сдвигом хвоста массива вправо
    void add(T item, size_t index) override
    {
        auto ix = array_.begin();
        std::advance(ix, index);
        array_.insert(ix, item);
    };

    // извлекает элемент массива по индексу
    T get(size_t index) const override
    {
        if (index >= array_.size()) {
            throw invalidIndexNumber(array_.size(), index);
        }
        return array_[index];
    }

    // удаляет элемент массива со сдвигом хвоста массива влево
    T remove(size_t index) override
    {
        if (index >= array_.size()) {
            throw invalidIndexNumber(array_.size(), index);
        }
        T value = array_[index];
        auto start = array_.begin();
        std::advance(start, index);
        auto end = array_.begin();
        std::advance(end, index + 1);
        array_.erase(start, end);
        return value;
    };

    // возвращает актуальный размер массива
    size_t size() const override
    {
        return array_.size();
    }

  private:
    std::vector<T> array_;
};

#endif