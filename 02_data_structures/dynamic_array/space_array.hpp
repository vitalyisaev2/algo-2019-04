#ifndef SPACE_ARRAY_HPP
#define SPACE_ARRAY_HPP

#include "dynamic_array.hpp"
#include "factor_array.hpp"
#include <tuple>

template <typename T>
class SpaceArray : public DynamicArray<T>
{
  public:
    SpaceArray() : SpaceArray(2){};
    SpaceArray(size_t row_size) : array_(new FactorArray<DynamicArray<T>*>()), row_size_(row_size){};

    ~SpaceArray()
    {
        for (size_t i = 0; i < array_->size(); i++) {
            delete array_->get(i);
        }
        delete array_;
    }

    // добавляет элемент в конец массива
    void add(T item) override
    {
        if (array_->size() == 0) {
            // если массив пуст, выделяем память
            array_->add(new FactorArray<T>());
        } else if (rowIsFull(array_->size() - 1)) {
            // достигнут предел размера для последнего ряда,
            // необходимо создать новый ряд
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
        auto rowID = std::get<0>(position);
        auto cellID = std::get<1>(position);

        // если в целевом массиве есть место, записываем данные сюда
        auto thisRow = array_->get(rowID);
        if (!rowIsFull(rowID)) {
            thisRow->add(item, cellID);
            return;
        }

        // если целевой массив достиг предельного размера,
        // надо записывать в предыдущий или последующий массив,
        // возможно, предварительно создав его
        if (cellID == 0) {
            // при добавлении в начало массива пытаемся перенести новую запись в предыдущий
            if (rowID > 0 && !rowIsFull(rowID - 1)) {
                array_->get(rowID - 1)->add(item);
            } else {
                auto newRow = new FactorArray<T>();
                array_->add(newRow, rowID);
                newRow->add(item);
            }
        } else if (cellID == row_size_ - 1) {

            // при добавлении в конец массива пытаемся перенести новую запись в следующий
            if (rowID < array_->size() - 1 && !rowIsFull(rowID + 1)) {
                array_->get(rowID - 1)->add(item);
            } else {
                auto newRow = new FactorArray<T>();
                array_->add(new FactorArray<T>(), rowID + 1);
                newRow->add(item);
            }
        } else {
            // при добавлении данных в середину заполненного массива его хвост перемещается в новый массив
            auto newRow = new FactorArray<T>();
            array_->add(new FactorArray<T>(), rowID + 1);
            // записываем хвост в новый массив
            for (auto i = cellID + 1; i < thisRow->size(); i++) {
                newRow->add(thisRow->get(i));
            };
            // удаляем данные из старого массива
            for (auto i = thisRow->size() - cellID; i != 0; i--) {
                thisRow->remove(thisRow->size() - 1);
            }
            //
            thisRow->add(item, cellID);
        }
    };

    // извлекает элемент массива по индексу
    T get(size_t index) const
    {
        auto position = getIndexPosition(index);
        auto rowID    = std::get<0>(position);
        auto cellID   = std::get<1>(position);
        return array_->get(rowID)->get(cellID);
    };

    // удаляет элемент массива со сдвигом хвоста массива влево
    T remove(size_t index)
    {
        auto position = getIndexPosition(index);
        auto rowID    = std::get<0>(position);
        auto cellID   = std::get<1>(position);

        T value = array_->get(rowID)->remove(cellID);
        if (array_->get(rowID)->size() == 0) {
            auto row = array_->remove(rowID);
            delete row;
        }
        return value;
    };

    // возвращает актуальный размер массива
    size_t size() const
    {
        size_t cumulativeSize = 0;
        for (size_t rowID = 0; rowID < array_->size(); rowID++) {
            cumulativeSize += array_->get(rowID)->size();
        }
        return cumulativeSize;
    }

  private:
    bool rowIsFull(size_t rowID) const
    {
        if (rowID >= array_->size()) {
            throw "invalid row id";
        }
        return array_->get(rowID)->size() == row_size_;
    }

    // возвращает идентификатор ряда и идентифкатор ячейки в ряду для указанного индекса
    std::tuple<size_t, size_t> getIndexPosition(size_t index) const
    {
        size_t cumulativeSizeBefore = 0;
        size_t cumulativeSizeAfter  = 0;
        size_t rowID                = 0;
        for (; rowID < array_->size(); rowID++) {
            cumulativeSizeBefore = cumulativeSizeAfter;
            cumulativeSizeAfter += array_->get(rowID)->size();
            if (cumulativeSizeBefore <= index && index < cumulativeSizeAfter) {
                break;
            }
        }

        if (index == cumulativeSizeAfter) {
            rowID--;
        }

        if (index > cumulativeSizeAfter) {
            throw "index value too big";
        }

        // определяется номер ячейки в целевом массиве
        size_t cellID = index - cumulativeSizeBefore;

        return std::make_tuple(rowID, cellID);
    }

    DynamicArray<DynamicArray<T>*>* array_;
    size_t                          row_size_;
};

#endif