#include "dynamic_array.hpp"
#include "factor_array.hpp"
#include "matrix_array.hpp"
#include "single_array.hpp"
#include "space_array.hpp"
#include "std_vector_array.hpp"
#include "vector_array.hpp"
#include <catch2/catch.hpp>

TEMPLATE_TEST_CASE("DynamicArray operations", "[DynamicArray][template]", SingleArray<int>, VectorArray<int>, FactorArray<int>,
                    MatrixArray<int>, StdVectorArray<int>, SpaceArray<int>)
{
    SECTION("simple CRUD operations")
    {
        TestType array;

        // у пустого массива размер равен 0
        REQUIRE(array.size() == 0);

        // записываем элемент в конец
        array.add(0);
        REQUIRE(array.size() == 1);
        REQUIRE(array.get(0) == 0);

        // удаляем единственный элемент
        REQUIRE(array.remove(0) == 0);
        REQUIRE(array.size() == 0);
    }

    SECTION("add to front")
    {
        TestType array;
        array.add(0);
        array.add(1);
        array.add(2);
        array.add(3);
        array.add(4);
        array.add(5, 0);

        TestType expected;
        expected.add(5);
        expected.add(0);
        expected.add(1);
        expected.add(2);
        expected.add(3);
        expected.add(4);

        REQUIRE(array == expected);
    }

    SECTION("add to middle")
    {
        TestType array;
        array.add(0);
        array.add(1);
        array.add(2);
        array.add(3);
        array.add(4);
        array.add(5, 2);

        TestType expected;
        expected.add(0);
        expected.add(1);
        expected.add(5);
        expected.add(2);
        expected.add(3);
        expected.add(4);

        REQUIRE(array == expected);
    }

    SECTION("add to back")
    {
        TestType array;
        array.add(0);
        array.add(1);
        array.add(2);
        array.add(3);
        array.add(4);
        array.add(5, 5);

        TestType expected;
        expected.add(0);
        expected.add(1);
        expected.add(2);
        expected.add(3);
        expected.add(4);
        expected.add(5);

        REQUIRE(array == expected);
    }

    SECTION("remove from front")
    {
        TestType array;
        array.add(0);
        array.add(1);
        array.add(2);
        array.add(3);
        array.add(4);
        array.add(5);
        REQUIRE(array.remove(0) == 0);

        TestType expected;
        expected.add(1);
        expected.add(2);
        expected.add(3);
        expected.add(4);
        expected.add(5);

        REQUIRE(array == expected);
    }

    SECTION("remove from middle")
    {
        TestType array;
        array.add(0);
        array.add(1);
        array.add(2);
        array.add(3);
        array.add(4);
        array.add(5);
        REQUIRE(array.remove(2) == 2);

        TestType expected;
        expected.add(0);
        expected.add(1);
        expected.add(3);
        expected.add(4);
        expected.add(5);

        REQUIRE(array == expected);
    }

    SECTION("remove from back")
    {
        TestType array;
        array.add(0);
        array.add(1);
        array.add(2);
        array.add(3);
        array.add(4);
        array.add(5);
        REQUIRE(array.remove(5) == 5);

        TestType expected;
        expected.add(0);
        expected.add(1);
        expected.add(2);
        expected.add(3);
        expected.add(4);

        REQUIRE(array == expected);
    }
}
