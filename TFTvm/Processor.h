#pragma once
#include <memory>
#include <vector>

#include "MACHINE.h"


/*
 * Processor is modelled as a simple RISC for now.
 * Memory controller, multi-core, caching are not supported.
 * Intercepts, exceptions are not supported for now.
 * Bitwidth must of a power of 2 and greater-equal than 8 (for alignment purposes).
 */
namespace MACHINE {
    class Processor
    {
    public:
        using Register = std::vector<byte_t>;

        Processor(std::size_t wordSizeInBits = 16, std::size_t numPublicRegisters = 8, std::size_t numPrivateRegisters = 3);
        virtual ~Processor() = default;

    private:

        struct IMPL;
        std::unique_ptr<IMPL> m_impl;
    };
}
