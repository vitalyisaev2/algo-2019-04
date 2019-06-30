#include "unbalanced_binary_tree.hpp"
#include <catch2/catch.hpp>

TEMPLATE_TEST_CASE("BinaryTree", "[BinaryTree][template]", (algo::UnbalancedBinaryTree<int, char>))
{
    SECTION("Basic CRUD operations")
    {
        auto tree = new TestType();
        tree->Insert(65, 'A');
        tree->Insert(66, 'B');
        tree->Insert(67, 'C');
        REQUIRE(tree->Contains(65));
        REQUIRE(tree->Contains(66));
        REQUIRE(tree->Contains(67));
        // REQUIRE(tree->Get(65) == 'A');
        // REQUIRE(tree->Get(66) == 'B');
        // REQUIRE(tree->Get(67) == 'C');
        delete tree;
    }
}