#pragma once
#include <cstdint>
#include <vector>

namespace MACHINE {
    using byte_t = uint8_t;

    /* Register Layout
     * BYTE#
     *   3  2  1  0
     * |xx|xx|xx|xx|
     *
     * xx = 1 Byte
     * BYTE#0 is the LSB
     * BYTE#3 is the MSB
     */
    using word_t = std::vector<byte_t>;
    // TODO: wrap the word_t to make it complete
}