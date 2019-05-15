#include "linked_list_priority_queue.hpp"
#include <catch2/catch.hpp>

TEMPLATE_TEST_CASE("PriorityQueue operations", "[PriorityQueue][template]", LinkedListPriorityQueue<int>)
{
    SECTION("basic operations")
    {
        TestType queue;
        REQUIRE(queue.empty());

        queue.enqueue(0, 0);
        queue.enqueue(1, 1);
        queue.enqueue(1, 2);

        REQUIRE(!queue.empty());

        REQUIRE(queue.dequeue() == 0);
        REQUIRE(queue.dequeue() == 1);
        REQUIRE(queue.dequeue() == 2);
        REQUIRE(queue.empty());
    }

    SECTION("big gaps in between")
    {
        TestType queue;
        queue.enqueue(0, 0);
        queue.enqueue(5, 5);
        queue.enqueue(10, 10);
        REQUIRE(queue.dequeue() == 0);
        REQUIRE(queue.dequeue() == 5);
        REQUIRE(queue.dequeue() == 10);
    }
}