#ifndef FEN_HPP
#define FEN_HPP

#include <array>

namespace fen
{
    // FIGURE - тип фигуры, которая может быть размещена в ячейке
    enum FIGURE {
        EMPTY  = 0,
        PAWN   = 1,
        BISHOP = 2,
        KNIGHT = 3,
        ROOK   = 4,
        QUEEN  = 5,
        KING   = 6,
    };

    // SIDE - цветовая принадлежность фигуры
    enum SIDE {
        UNMARKED = 0,
        BLACK    = 1,
        WHITE    = 2,
    };

    // Cell - структура, описывающая текущее состоянии клетки шахматной доски
    class Cell
    {
      public:
        // конструктор пустой ячейки
        Cell();
        // конструктор ячейки, занятой какой-то фигурой
        Cell(const char& input);
        FIGURE GetFigure() const;
        SIDE   GetSide() const;
        char   ToChar() const;

      private:
        SIDE   side;
        FIGURE figure;
    };

    std::ostream& operator<<(std::ostream& out, const Cell& figure);

    class Line
    {
      public:
        Line(const std::string& src);
        std::string ToString() const;

      private:
        std::array<Cell, 8> cells;
    };

    std::ostream& operator<<(std::ostream& out, const Line& figure);

    class Board
    {
      private:
        std::array<Line*, 8> lines;
    };

    std::ostream& operator<<(std::ostream& out, const Board& figure);

} // namespace fen

#endif