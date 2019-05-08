#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

template <typename T>
class DynamicArray
{
  public:
    // добавляет элемент в конец массива
    virtual void   add(T item) = 0;
    // вставляет элемент по индексу со сдвигом хвоста массива вправо
    virtual void   add(T item, int index) = 0;
    // извлекает элемент массива по индексу
    virtual T      get(int index) const = 0;
    // удаляет элемент массива со сдвигом хвоста массива влево 
    virtual T      remove(int index) = 0;
    // возвращает актуальный размер массива 
    virtual size_t size() const = 0;
};

#endif