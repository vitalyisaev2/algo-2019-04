#include "fen.hpp"
#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

TEST_CASE("FEN")
{
    SECTION("line")
    {
        // проверка на корректное конструирование / сериализацию горизонтали
        std::vector<std::string> inputs = {
            "rnbqkbnr", "pppppppp", "8", "PPPPPPPP", "RNBQKBNR", "4P3", "3p4", "PPPP1PPP", "ppp1pppp",
        };
        for (const auto& input : inputs) {
            REQUIRE(fen::Line(input).ToString() == input);
        }
    }

    SECTION("board")
    {
        // проверка на корректное конструирование / сериализацию последовательности горизонталей
        std::vector<std::string> inputs = {
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR",
        };
        for (const auto& input: inputs) {
            REQUIRE(fen::Board(input).ToString() == input);
        }
    }
}