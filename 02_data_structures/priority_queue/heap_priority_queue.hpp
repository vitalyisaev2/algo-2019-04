#ifndef HEAP_PRIORITY_QUEUE
#define HEAP_PRIORITY_QUEUE

#include "heap.hpp"

namespace algo
{

    template <typename T>
    class HeapPriorityQueue : public PriorityQueue<T>
    {
      public:
        HeapPriorityQueue(){};

        void enqueue(int priority, T value) override{

        };

        T dequeue() override{
            return HeapRemoveMax(array);
        };

        bool empty() const override{
            return array.size() == 0;
        };

        ~HeapPriorityQueue(){};

      private:
        std::vector<T> array;
    }

} // namespace algo

#endif