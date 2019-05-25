#include "fen.hpp"
#include <cctype>

namespace fen
{

    Cell::Cell() : side(UNMARKED), figure(EMPTY) {}

    Cell::Cell(const char& input)
    {
        if (std::isupper(input)) {
            this->side = WHITE;
        } else {
            this->side = BLACK;
        }

        switch (std::tolower(input)) {
        case 'p':
            this->figure = PAWN;
            break;
        case 'b':
            this->figure = BISHOP;
            break;
        case 'n':
            this->figure = KNIGHT;
            break;
        case 'r':
            this->figure = ROOK;
            break;
        case 'q':
            this->figure = QUEEN;
            break;
        case 'k':
            this->figure = KING;
            break;
        default:
            throw "ivalid figure code";
        }
    }

    FIGURE Cell::GetFigure() const
    {
        return this->figure;
    }

    COLOR Cell::GetColor() const
    {
        return this->side;
    }

    char Cell::ToChar() const
    {
        char result = 0;
        switch (this->figure) {
        case EMPTY:
            break;
        case PAWN:
            result = 'p';
            break;
        case BISHOP:
            result = 'b';
            break;
        case KNIGHT:
            result = 'n';
            break;
        case ROOK:
            result = 'r';
            break;
        case QUEEN:
            result = 'q';
            break;
        case KING:
            result = 'k';
            break;
        default:
            throw "unknown figure";
        }

        if (this->side == WHITE) {
            result = std::toupper(result);
        }
        return result;
    }
} // namespace fen