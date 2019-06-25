#ifndef BINARY_TREE
#define BINARY_TREE

namespace algo
{

    template <typename Key, typename Value>
    class BinaryTree
    {
      public:
        virtual void   Insert(const Key& key, const Value& value) = delete;
        virtual void   Remove(const Key& key)                     = delete;
        virtual bool   Contains(const Key& key) const               = delete;
        virtual Value& Get(const Key& key) const                  = delete;
        virtual ~BinaryTree();
    };

} // namespace algo

#endif BINARY_TREE