#include "fen.hpp"
#include <sstream>
#include <iostream>

namespace fen
{
    const std::string delimiter = "/";

    Board::Board(const std::string& s)
    {
        size_t last = 0;
        size_t next = 0;
        size_t i    = 0;

        // строка разбивается по символу "/"
        while ((next = s.find(delimiter, last)) != std::string::npos) {
            this->lines[i] = new Line(s.substr(last, next - last));
            last = next + 1;
            i++;
        }
        this->lines[i] = new Line(s.substr(last));
    }

    std::string Board::ToString() const
    {
        std::stringstream ss;
        for (size_t i = 0; i < this->lines.size(); i++) {
            ss << this->lines[i]->ToString();
            if (i != this->lines.size() - 1) {
                ss << delimiter;
            }
        }
        return std::move(ss.str());
    }

    Board::~Board()
    {
        for (auto line : this->lines) {
            delete line;
        }
    }
} // namespace fen