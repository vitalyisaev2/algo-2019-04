#include <catch2/catch.hpp>
#include <vector>
#include "trie.hpp"

TEST_CASE("Trie") {
    SECTION("Basic operations") {
        algo::Trie<std::vector<int>>::iterator> t;
        std::vector<int> v({1,2,3,4,5});
        t.Insert(v.begin(), v.end());
    }
};