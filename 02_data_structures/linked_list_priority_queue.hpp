#ifndef LINKED_LIST_PRIORITY_QUEUE_HPP
#define LINKED_LIST_PRIORITY_QUEUE_HPP

#include "priority_queue.hpp"

template <typename T>
class LinkedListPriorityQueue : public PriorityQueue<T>
{
  public:
    LinkedListPriorityQueue() : head_(nullptr) {}

    ~LinkedListPriorityQueue()
    {
        if (head_ != nullptr) {
            delete head_;
        }
    };

    void enqueue(int priority, T value) override
    {
        // небольшое упрощение
        if (priority < 0) {
            throw "invalid priority";
        }

        // при необходимости аллоцируем первый элемент
        if (head_ == nullptr) {
            head_ = new List();
        }

        // выбираем уровень, соответствующий данному приоритету
        auto curr = head_;
        while (priority--) {
            if (curr->next_ == nullptr) {
                curr->next_ = new List();
            };
            curr = curr->next_;
        }

        curr->pushBack(value);
    };

    T dequeue() override
    {
        if (empty()) {
            throw "can't perofm dequeue on empty queue";
        }

        auto curr = head_;
        while (curr->empty()) {
            auto removed = curr;
            curr         = curr->next_;
            delete removed;
        }

        auto ret = curr->popFront();

        while (curr != nullptr && curr->empty()) {
            auto removed = curr;
            curr         = curr->next_;
            delete removed;
        }

        // наиболее приоритетный список сохраняем в head_
        head_ = curr;

        return ret;
    }

    bool empty() override
    {
        return head_ == nullptr;
    }

  private:
    struct List {

        struct Node {
            Node(T v) : value(v), next(nullptr){};
            T     value;
            Node* next;
        };

        List() : head_(nullptr), next_(nullptr){};

        ~List()
        {
            auto curr = head_;
            while (curr != nullptr) {
                auto next = curr->next;
                delete curr;
                curr = next;
            }
        };

        // O(N)
        void pushBack(T value)
        {
            if (head_ == nullptr) {
                head_ = new Node(value);
                return;
            }
            auto curr = head_;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = new Node(value);
        }

        // O(1)
        T popFront()
        {
            if (head_ == nullptr) {
                throw "nothing to pop from list";
            }

            auto removed = head_;
            auto ret     = removed->value;
            head_        = head_->next;
            delete removed;
            return ret;
        }

        bool empty()
        {
            return head_ == nullptr;
        };

        Node* head_;
        List* next_;
    };

    List* head_;
};

#endif