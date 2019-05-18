#ifndef SPACE_ARRAY_HPP
#define SPACE_ARRAY_HPP

#include "dynamic_array.hpp"
#include "factor_array.hpp"
#include <tuple>

template <typename T>
class SpaceArray : public DynamicArray<T>
{
  public:
    SpaceArray(size_t row_size) : array_(new FactorArray<DynamicArray*>()), row_size_(row_size), size_(0){};

    ~SpaceArray() :
    {
        delete array_;
    }

    // добавляет элемент в конец массива
    void add(T item) override
    {
        if (array_->size() == 0) {
            array_->add(new FactorArray<T>());
        }
        // достигнут предел размера для последнего ряда,
        // необходимо создать новый ряд
        if (array_->get(array_->size() - 1)->size() == row_size_) {
            array_->add(new FactorArray<T>());
        }
        array_->get(array_->size() - 1)->add(item);
    };

    // вставляет элемент по индексу со сдвигом хвоста массива вправо
    void add(T item, size_t index)
    {

        if (array_->size() == 0) {
            array_->add(new FactorArray<T>());
        }

        auto position = getIndexPosition(index);
        auto rowID    = std::get<0> position;
        auto cellID   = std::get<1> position;

        // если целевой массив достиг предельного размера,
        // надо добавить новый массив
        if (array_->get(rowID)->size() == row_size_) {
            switch (cellID) {
                // новый ряд предшествует текущему
            case 0:
                auto newRow =  new FactorArray<T>();
                array_->add(newRow, rowID);
                newRow->add(item);
                break;
            case row_size_ - 1:
                auto newRow =  new FactorArray<T>();
                array_->add(new FactorArray<T>(), rowID+1);
                break; 
            default:
                break;
            }
        }
    };

    // извлекает элемент массива по индексу
    T get(size_t index) const = 0;

    // удаляет элемент массива со сдвигом хвоста массива влево
    T remove(size_t index) = 0;

    // возвращает актуальный размер массива
    size_t size() const = 0;

  private:
    // возвращает идентификатор ряда и идентифкатор ячейки в ряду для указанного индекса
    std::tuple<size_t, size_t> getIndexPosition(size_t index)
    {
        size_t cumSize = 0;
        size_t rowID   = 0;
        for (; rowID < array_->size(); rowID++) {
            cumSize += array_->get(i)->size();
            if (index < cumSize) {
                break;
            }
        }

        if (index >= cumSize) {
            throw "index value too big";
        }

        size_t cellID = index % (cumSize - array_->get(rowID)->size());
        return std::make_tuple(rowID, cellID);
    }
    DynamicArray<DynamicArray<T>*>* array_;
    size_t                          row_size_;
}

#endif