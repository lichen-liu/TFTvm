#pragma once
#include <cassert>
#include <string>


namespace PARSER {
    enum class radix_e {
        BIN, // binary
        HEX, // hexdacimal
        OCT, // octal
        DEC, // signed decimal
        UNS, // unsigned decimal
        INVALID
    };

    radix_e& operator << (radix_e& rad, const std::string &str);
    radix_e& operator >> (radix_e& rad, std::string &str);
}
