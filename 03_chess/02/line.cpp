#include "fen.hpp"
#include <cctype>
#include <iostream>
#include <sstream>

namespace fen
{
    Line::Line(const std::string& input) : cells({})
    {
        size_t i = 0;
        for (const char& c : input) {
            if (std::isdigit(c)) {
                // char конвертируется в цифру
                int emptyNodes = c - '0';
                // std::cout << "is_digit" << c << " " << emptyNodes << std::endl;
                while (emptyNodes--) {
                    this->cells[i] = Cell();
                    i++;
                }
            } else {
                this->cells[i] = Cell(c);
            i++;
            }
        }
    }

    std::string Line::ToString() const
    {
        std::stringstream ss;
        int               emptySequence = 0;

        for (const auto& cell : cells) {
            // std::cout << cell.ToChar() << " " << int(cell.GetFigure()) << " " << int(cell.GetSide()) << std::endl;
            switch (cell.GetFigure()) {
            case EMPTY:
                emptySequence++;
                break;
            default:
                if (emptySequence) {
                    ss << emptySequence;
                    emptySequence = 0;
                }
                ss << cell.ToChar();
                break;
            }
        }
        if (emptySequence) {
            ss << emptySequence;
        }
        return std::move(ss.str());
    }
} // namespace fen