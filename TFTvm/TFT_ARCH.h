#pragma once
#include <cstddef>


/*
 * All TFT Architecture dependent parameters are defined here.
 */
namespace TFT_ARCH {
    constexpr std::size_t WORD_SIZE = 2; // 16-bit architecture
    constexpr std::size_t NUM_PUBLIC_REGISTERS = 8;
    constexpr std::size_t NUM_PRIVATE_REGISTERS = 3;
}
