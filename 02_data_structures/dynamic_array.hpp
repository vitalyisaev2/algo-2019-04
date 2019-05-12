#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <ostream>

// интерфейс динамического массива
template <typename T>
class DynamicArray
{
  public:
    // добавляет элемент в конец массива
    virtual void add(T item) = 0;

    // вставляет элемент по индексу со сдвигом хвоста массива вправо
    virtual void add(T item, size_t index) = 0;

    // извлекает элемент массива по индексу
    virtual T get(size_t index) const = 0;

    // удаляет элемент массива со сдвигом хвоста массива влево
    virtual T remove(size_t index) = 0;

    // возвращает актуальный размер массива
    virtual size_t size() const = 0;

    // оператор сравнения важен в юнит-тестах
    bool operator==(const DynamicArray& other) const
    {
        if (this->size() != other.size()) {
            return false;
        }
        for (size_t i = 0; i < other.size(); i++) {
            if (this->get(i) != other.get(i)) {
                return false;
            }
        }
        return true;
    }

    virtual ~DynamicArray(){};
};

// распечатка массива в поток
template <typename T>
std::ostream& operator<<(std::ostream& out, const DynamicArray<T>& array)
{
    for (size_t i = 0; i < array.size(); i++) {
        out << array.get(i);
        if (i != array.size() - 1) {
            out << " ";
        }
    }
    return out;
}

#endif