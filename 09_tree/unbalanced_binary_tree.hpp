#ifndef UNBALANCED_BINARY_TREE
#define UNBALANCED_BINARY_TREE

#include "binary_tree.hpp"

namespace algo
{
    // простой вариант бинарного дерева, написал просто для тренировки
    template <typename Key, typename Value>
    class UnbalancedBinaryTree : public BinaryTree<Key, Value>
    {
      public:
        UnbalancedBinaryTree() : _root(nullptr), _size(0) {}

        ~UnbalancedBinaryTree()
        {
            if (_root != nullptr) {
                delete _root;
            }
        }

        void Insert(const Key& key, const Value& value) override
        {
            if (_root == nullptr) {
                _root = new Node(key, value);
                _size++;
                return;
            }

            if (_root->Insert(key, value)) {
                _size++;
            };
            return;
        }

        bool Contains(const Key& key) const override
        {
            if (_root == nullptr) {
                return false;
            }
            return _root->Contains(key);
        }

        size_t Size() const override
        {
            return _size;
        }

      private:
        class Node
        {
          public:
            Node(const Key& key, const Value& value) : _key(key), _value(value), _left(nullptr), _right(nullptr){};

            ~Node()
            {
                if (_left != nullptr) {
                    delete _left;
                }
                if (_right != nullptr) {
                    delete _right;
                }
            }

            void SetLeft(Node* node)
            {
                _left = node;
            }

            void SetRight(Node* node)
            {
                _right = node;
            }

            // Возвращаемое значение указывает на то, был ли создан новый узел дерева
            bool Insert(const Key& key, const Value& value)
            {
                if (key == _key) {
                    _value = value;
                    return false;
                }

                if (key > _key) {
                    if (_right == nullptr) {
                        _right = new Node(key, value);
                        return true;
                    }
                    return _right->Insert(key, value);
                }

                if (_left == nullptr) {
                    _left = new Node(key, value);
                    return true;
                }
                return _left->Insert(key, value);
            }

            bool Contains(const Key& key) const
            {
                if (_key == key) {
                    return true;
                }

                if (key > _key && _right != nullptr) {
                    return _right->Contains(key);
                }

                if (key < _key && _left != nullptr) {
                    return _left->Contains(key);
                }

                return false;
            }

          private:
            Key   _key;
            Value _value;
            Node* _left;
            Node* _right;
        };

        Node*  _root;
        size_t _size;
    };
} // namespace algo

#endif