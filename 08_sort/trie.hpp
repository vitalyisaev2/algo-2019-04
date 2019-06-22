#ifndef TRIE_HPP
#define TRIE_HPP

#include <iterator>
#include <map>
#include <memory>

namespace algo
{
    // Префиксное дерево, которое работает с последовательностями значений какого-то типа,
    // которые передаются через итераторы
    template <typename Iterator, typename T = Iterator::value_type>
    class Trie
    {
      public:
        Trie() : terminated(false){};

        void Insert(Iterator begin, Iterator end)
        {
            if (begin == end) {
                if (terminated) {
                    throw "Sequence already exists";
                }
                terminated = true;
                return;
            }
            auto value = *begin;
            if (!children.contains(value)) {
                children[value] = std::make_unique<Trie>();
            }
            children[value]->Insert(++begin, end);
        }

        bool Exists(Iterator begin, Iterator end)
        {
            if (begin == end) {
                return terminated;
            }
            auto value = *begin;
            if (!children.contains(value)) {
                return false;
            }
            return children[value]->Exists(++begin, end);
        }

        void Remove(Iterator begin, Iterator end)
        {
            if (begin == end) {
                if (!terminated) {
                    throw "Sequence does not exist";
                }
                terminated = false;
                return;
            }

            // если дочернего узла не существует, значит, такой последовательности нет
            auto value = *begin;
            if (!children.contains(value)) {
                throw "Sequence does not exist";
            }

            // если у дочернего узла нет своих детей, значит, узел удаляется
            if (std::distance(begin, end) == 1 && children[value]->children.size() == 0) {
                children.erase(value);
                return;
            }

            children[value]->Remove(++begin, end);
        }

      private:
        std::map<T, std::unique_ptr<Trie>> children;
        bool                               terminated;
    };

} // namespace algo

#endif