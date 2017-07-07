#pragma once
#include <cstdint>


namespace TURING_MACHINE {
    using byte_t = uint8_t;

    enum class endian_e {
        little,
        big
    };

    enum class addressable_e {
        byte,
        word
    };
}