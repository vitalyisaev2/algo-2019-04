#include "fen.hpp"

namespace fen {
    Record::Record(const std::string& src) {

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
    } 
}