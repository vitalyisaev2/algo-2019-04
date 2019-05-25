#include "fen.hpp"
#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

TEST_CASE("fen")
{
    SECTION("line")
    {
        std::vector<std::string> lines = {
            "rnbqkbnr", "pppppppp", "8", "PPPPPPPP", "RNBQKBNR", "4P3", "3p4", "PPPP1PPP", "ppp1pppp",
        };
        for (const auto& line : lines) {
            REQUIRE(fen::Line(line).ToString() == line);
        }
    }
}