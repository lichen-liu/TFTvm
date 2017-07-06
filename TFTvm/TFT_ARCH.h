#pragma once
#include <cstddef>

#include "TURING_MACHINE.h"


/*
 * All TFT Architecture dependent parameters are defined here.
 */
namespace TFT_ARCH {
    constexpr std::size_t WORD_SIZE = 2; // 16-bit architecture

    namespace PUBLIC_REG_E {
        enum :std::size_t
        {
            R0 = 0,
            R1 = 1,
            R2 = 2,
            R3 = 3,
            R4 = 4,
            R5 = 5,
            R6 = 6,
            PC = 7,
            NUM
        };
    }

    namespace PRIVATE_REG_E {
        enum :std::size_t
        {
            IR = 0,
            A = 1,
            G = 2,
            NUM
        };
    }

    constexpr TURING_MACHINE::addressable_e ADDRESSABLE = TURING_MACHINE::addressable_e::word;
    constexpr TURING_MACHINE::endian_e ENDIAN = TURING_MACHINE::endian_e::little;
}
