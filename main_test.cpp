#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_NOSTDOUT
#include <catch2/catch.hpp>

namespace Catch {
    std::ostream& cout() {
        return std::cout;
    }
    std::ostream& clog() {
        return std::clog;
    }
    std::ostream& cerr() {
        return std::cerr;
    }
}
