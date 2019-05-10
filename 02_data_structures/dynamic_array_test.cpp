#include "dynamic_array.hpp"
#include "single_array.hpp"
#include <catch2/catch.hpp>

TEST_CASE("DynamicArray")
{
    SECTION("simple CRUD operations")
    {
        DynamicArray<int>* array = new SingleArray<int>();

        // у пустого массива размер равен 0
        REQUIRE(array->size() == 0);

        // записываем элемент в конец
        array->add(0);
        REQUIRE(array->size() == 1);
        REQUIRE(array->get(0) == 0);

        // удаляем единственный элемент
        REQUIRE(array->remove(0) == 0);
        REQUIRE(array->size() == 0);

        delete array;
    }

    SECTION("add to front")
    {
        DynamicArray<int>* array = new SingleArray<int>();
        array->add(0);
        array->add(1);
        array->add(2);
        array->add(3, 0);

        DynamicArray<int>* expected = new SingleArray<int>();
        expected->add(3);
        expected->add(0);
        expected->add(1);
        expected->add(2);

        REQUIRE(*array == *expected);

        delete array;
        delete expected;
    }

    SECTION("add to middle")
    {
        DynamicArray<int>* array = new SingleArray<int>();
        array->add(0);
        array->add(1);
        array->add(2);
        array->add(3, 2);

        DynamicArray<int>* expected = new SingleArray<int>();
        expected->add(0);
        expected->add(1);
        expected->add(3);
        expected->add(2);

        REQUIRE(*array == *expected);

        delete array;
        delete expected;
    }

    SECTION("add to back")
    {
        DynamicArray<int>* array = new SingleArray<int>();
        array->add(0);
        array->add(1);
        array->add(2);
        array->add(3, 3);

        DynamicArray<int>* expected = new SingleArray<int>();
        expected->add(0);
        expected->add(1);
        expected->add(2);
        expected->add(3);

        REQUIRE(*array == *expected);

        delete array;
        delete expected;
    }

    SECTION("remove from front")
    {
        DynamicArray<int>* array = new SingleArray<int>();
        array->add(0);
        array->add(1);
        array->add(2);
        array->add(3);
        REQUIRE(array->remove(0) == 0);

        DynamicArray<int>* expected = new SingleArray<int>();
        expected->add(1);
        expected->add(2);
        expected->add(3);

        REQUIRE(*array == *expected);

        delete array;
        delete expected;
    }

    SECTION("remove from middle")
    {
        DynamicArray<int>* array = new SingleArray<int>();
        array->add(0);
        array->add(1);
        array->add(2);
        array->add(3);
        REQUIRE(array->remove(2) == 2);

        DynamicArray<int>* expected = new SingleArray<int>();
        expected->add(0);
        expected->add(1);
        expected->add(3);

        REQUIRE(*array == *expected);

        delete array;
        delete expected;
    }

    SECTION("remove from back")
    {
        DynamicArray<int>* array = new SingleArray<int>();
        array->add(0);
        array->add(1);
        array->add(2);
        array->add(3);
        REQUIRE(array->remove(3) == 3);

        DynamicArray<int>* expected = new SingleArray<int>();
        expected->add(0);
        expected->add(1);
        expected->add(2);

        REQUIRE(*array == *expected);

        delete array;
        delete expected;
    }
}