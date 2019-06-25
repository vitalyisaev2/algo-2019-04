#ifndef UNBALANCED_BINARY_TREE
#define UNBALANCED_BINARY_TREE

#include "binary_tree.hpp"

namespace algo
{
    // простой вариант бинарного дерева, пишу просто для тренировки
    template <typename Key, typename Value>
    class UnbalancedBinaryTree : public BinaryTree<Key, Value>
    {
      public:
        UnbalancedBinaryTree() : root(nullptr) {}

        ~UnbalancedBinaryTree()
        {
            if (root != nullptr) {
                delete root;
            }
        }

        void Insert(const Key& key, const Value& value) override
        {
            if (root == nullptr) {
                root = new Node(key, value);
                return;
            }

            root->Insert(key, value);
            return;
        }

      private:
        class Node
        {
          public:
            Node(const Key& key, const Value& value) : _key(key), _value(value), _left(nullptr), _right(nullptr) : {};

            ~Node()
            {
                if (left != nullptr) {
                    delete left;
                }
                if (right != nullptr) {
                    delete right;
                }
            }

            SetLeft(Node* node)
            {
                left = node;
            }

            SetRight(Node* node)
            {
                right = node;
            }

            Insert(const Key& key, const Value& value)
            {
                if (key == _key) {
                    _value = value;
                    return;
                }

                if (key > _key) {
                    if (_right == nullptr) {
                        _right = new Node(key, value);
                        return;
                    }
                    _right->Insert(key, value);
                    return;
                }

                if (_left == nullptr) {
                    _left = new Node(key, value);
                    return;
                }
                _left->Insert(key, value);
                return;
            }

          private:
            Key   _key;
            Value _value;
            Node* _left;
            Node* _right;
        }

        Node* root;
    };
} // namespace algo

#endif