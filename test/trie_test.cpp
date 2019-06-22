#include "trie.hpp"
#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("Trie")
{
    SECTION("Insert")
    {
        algo::Trie<std::vector<int>::iterator> trie;

        // вставляем пару последовтельностей
        std::vector<int> v1({1, 2, 3, 4, 5});
        trie.Insert(v1.begin(), v1.end());
        std::vector<int> v2({1, 2, 3, 5, 4});
        trie.Insert(v2.begin(), v2.end());

        // проверяем, что они имеются в дереве
        REQUIRE(trie.Exists(v1.begin(), v1.end()));
        REQUIRE(trie.Exists(v2.begin(), v2.end()));
    }

    SECTION("Insert the same sequence twice")
    {
        algo::Trie<std::vector<int>::iterator> trie;

        // повторная вставка одной и той же последовательности вызывает исключение
        std::vector<int> v1({1, 2, 3, 4, 5});
        trie.Insert(v1.begin(), v1.end());
        REQUIRE_THROWS(trie.Insert(v1.begin(), v1.end()));
    }

    SECTION("Check nonexisting sequence")
    {
        algo::Trie<std::vector<int>::iterator> trie;

        // любой произвольной последовательности не имеется
        std::vector<int> v3({0, 0, 0, 0, 0});
        REQUIRE(!trie.Exists(v3.begin(), v3.end()));
    }

    SECTION("Remove sequence")
    {
        algo::Trie<std::vector<int>::iterator> trie;

        // вставляем и удаляем последовательность
        std::vector<int> v1({1, 2, 3, 4, 5});
        trie.Insert(v1.begin(), v1.end());
        REQUIRE(trie.Exists(v1.begin(), v1.end()));
        trie.Remove(v1.begin(), v1.end());
        REQUIRE(!trie.Exists(v1.begin(), v1.end()));

        // повторное удаление вызывает исключение
        REQUIRE_THROWS(trie.Remove(v1.begin(), v1.end()));
    }

    SECTION("Remove nonexisting sequence")
    {
        algo::Trie<std::vector<int>::iterator> trie;

        // любой произвольной последовательности не имеется
        std::vector<int> v3({0, 0, 0, 0, 0});
        REQUIRE_THROWS(trie.Remove(v3.begin(), v3.end()));
    }
}