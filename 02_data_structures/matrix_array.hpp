#ifndef MATRIX_ARRAY_HPP
#define MATRIX_ARRAY_HPP

#include "dynamic_array.hpp"
#include "factor_array.hpp"
#include "single_array.hpp"
#include "utils.hpp"

template <typename T>
class MatrixArray : public DynamicArray<T>
{
  public:
    MatrixArray() : MatrixArray(2){};
    MatrixArray(size_t row_size) : array_(new SingleArray<DynamicArray<T>*>()), size_(0), row_size_(row_size){};
    ~MatrixArray()
    {
        delete array_;
        array_ = nullptr;
    }

    // добавляет элемент в конец массива
    void add(T item) override
    {
        if (mustGrow()) {
            grow();
        }
        array_->get(size_ / row_size_)->add(item);
        size_++;
    };

    // вставляет элемент по индексу со сдвигом хвоста массива вправо
    void add(T item, size_t index) override
    {
        if (mustGrow()) {
            grow();
        }
        shiftRight(index);
        array_->get(size_ / row_size_)->add(item);
        size_++;
    };

    // извлекает элемент массива по индексу
    T get(size_t index) const override
    {
        if (index >= size_) {
            throw invalidIndexNumber(size_, index);
        }
        return array_->get(index / row_size_)->get(index % row_size_);
    }

    // удаляет элемент массива со сдвигом хвоста массива влево
    T remove(size_t index) override
    {
        T result = get(index);
        shiftLeft(index);
        size_--;
        if (mustShrink()) {
            shrink();
        }
        return result;
    };

    // возвращает актуальный размер массива
    size_t size() const override
    {
        return size_;
    };

  private:
    bool mustGrow()
    {
        return size_ == array_->size() * row_size_;
    }

    bool mustShrink()
    {
        // можно освободить целый ряд
        return size_ == (array_->size() - 1) * row_size_;
    }

    void grow()
    {
        array_->add(new FactorArray<T>());
    }

    void shrink()
    {
        auto removed = array_->get(array_->size() - 1);
        array_->remove(array_->size() - 1);
        delete removed;
    }

    void shiftRight(size_t from)
    {
        auto lastAffectedRow = from / row_size_;

        // последний элемент предыдущего массива становится
        // первым элементом следующего;
        for (auto i = array_->size(); i >= lastAffectedRow + 1; --i) {
            auto next = array_->get(i);
            auto prev = array_->get(i - 1);
            std::cout << "i: " << i << "next: " << *next << " prev: " << *prev << std::endl;
            next->add(prev->remove(prev->size() - 1), 0);
        }
    }

    void shiftLeft(size_t from)
    {
        // удаляется нужный элемент из целевого массива
        auto firstAffectedRow = from / row_size_;
        array_->get(firstAffectedRow)->remove(from % row_size_);

        // первый элемент следующего массива становится
        // последним элементом предыдущего
        for (auto i = firstAffectedRow; i < array_->size() - 1; i++) {
            auto prev = array_->get(i);
            auto next = array_->get(i + 1);
            prev->add(next->remove(0));
        }
    }

    DynamicArray<DynamicArray<T>*>* array_;
    size_t                          size_;
    const size_t                    row_size_;
};

#endif