#ifndef TRIE_HPP
#define TRIE_HPP

#include <iterator>
#include <map>

namespace algo
{
    template <class Iterator, class T = typename std::iterator_traits<Iterator>::value_type>
    class Trie
    {
      public:
        void Insert(Iterator begin, Iterator end)
        {
            if (begin == end) {
                return;
            }
            T value = *begin;
            if (!children.contains(value)) {
                children[value] = std::make_unique<Trie>();
            }
            children[value]->Insert(++begin, end);
        }

        bool Exists(const Iterator begin, const Iterator end) const
        {
            if (begin == end) {
                return true;
            }
            T value = *begin;
            if (!children.contains(value)) {
                return false;
            }
            return children[value]->Exists(++begin, end);
        }

        // void Remove(Iterator begin, Iterator end) {}

      private:
        std::map<T, std::unique_ptr<Trie>> children;
    };

} // namespace algo

#endif