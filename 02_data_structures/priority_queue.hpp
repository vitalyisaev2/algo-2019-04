#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <cstddef>

template <typename T>
class PriorityQueue
{
  public:
    virtual void enqueue(int priority, T value) = 0;
    virtual T    dequeue()                      = 0;
    virtual bool empty()                        = 0;
    virtual ~PriorityQueue(){};
};

#endif