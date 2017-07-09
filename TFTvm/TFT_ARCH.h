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
            R0,
            R1,
            R2,
            R3,
            R4,
            R5,
            R6,
            PC, // R7
            NUM
        };
    }

    namespace PRIVATE_REG_E {
        enum :std::size_t
        {
            IR,
            A,
            G,
            ADDR,
            DOUT,
            NUM
        };
    }

    namespace OPCODE_E {
        enum : std::size_t {
            MV = 0,
            MVI,
            ADD,
            SUB,
            LD,
            ST,
            MVNZ,
            NUM
        };
    }

    constexpr TURING_MACHINE::addressable_e ADDRESSABLE = TURING_MACHINE::addressable_e::word;
    constexpr TURING_MACHINE::endian_e ENDIAN = TURING_MACHINE::endian_e::little;

    constexpr std::size_t MEMORY_DELAY_IN_CYCLE = 50;
}
