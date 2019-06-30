#ifndef BINARY_TREE
#define BINARY_TREE

#include <stddef.h>

namespace algo
{

    template <typename Key, typename Value>
    class BinaryTree
    {
      public:
        virtual void Insert(const Key& key, const Value& value) = 0;
        virtual bool Contains(const Key& key) const             = 0;
        // virtual Value& Get(const Key& key) const                  = 0;
        // virtual void   Remove(const Key& key)                     = 0;
        virtual size_t Size() const = 0;
        virtual ~BinaryTree() {};
    };

} // namespace algo

#endif