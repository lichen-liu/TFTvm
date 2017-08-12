#include "PARSER.h"

#include <cassert>
#include <string>


namespace PARSER {
    radix_e& operator << (radix_e& rad, const std::string &str)
    {
        if (str == "BIN") {
            rad = radix_e::BIN;
        }
        else if (str == "HEX") {
            rad = radix_e::HEX;
        }
        else if (str == "OCT") {
            rad = radix_e::OCT;
        }
        else if (str == "DEC") {
            rad = radix_e::DEC;
        }
        else if (str == "UNS") {
            rad = radix_e::UNS;
        }
        else {
            rad = radix_e::INVALID;
        }
        return rad;
    }


    radix_e& operator >> (radix_e& rad, std::string &str)
    {
        switch (rad) {
        case radix_e::BIN:
            str = "BIN";
            break;
        case radix_e::HEX:
            str = "HEX";
            break;
        case radix_e::OCT:
            str = "OCT";
            break;
        case radix_e::DEC:
            str = "DEC";
            break;
        case radix_e::UNS:
            str = "UNS";
            break;
        case radix_e::INVALID:
            str = "INVALID";
            break;
        default:
            assert(false);
            break;
        }

        return rad;
    }
}