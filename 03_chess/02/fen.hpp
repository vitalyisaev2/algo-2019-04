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

    // COLOR - цветовая принадлежность фигуры
    enum COLOR {
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
        COLOR  GetColor() const;
        char   ToChar() const;

      private:
        COLOR  side;
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
      public:
        Board() = delete;
        Board(const std::string& src);
        std::string ToString() const;
        ~Board();

      private:
        std::array<Line*, 8> lines;
    };

    std::ostream& operator<<(std::ostream& out, const Board& figure);

    enum CastlingDirection {
        NOWHERE   = 0,
        KINGSIDE  = 1,
        QUEENSIDE = 2,
    };

    struct Castling {
        std::string       ToString() const;
        CastlingDirection white;
        CastlingDirection black;
    };

    class Record
    {
      public:
        Record() = delete;
        Record(const std::string& src);
        std::string ToString() const;

      private:
        Board       board;
        COLOR       activeColor;
        Castling    castling;
        Cell*       enPassant;
        std::size_t halfMoves;
        std::size_t fullMoves;
    };

} // namespace fen

#endif