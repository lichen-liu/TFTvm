#pragma once
#include <memory>
#include <vector>

#include "TURING_MACHINE.h"


/*
 * Processor is modelled as a simple RISC for now.
 * It provides the abstraction of its internal physical registers.
 * Memory controller, multi-core, caching, intercepts, exceptions are not supported.
 *
 * RF BYTE#
 * RF#  3  2  1  0
 * 00:|xx|xx|xx|xx|
 * 01:|xx|xx|xx|xx|
 * 02:|xx|xx|xx|xx|
 * 03:|xx|xx|xx|xx|
 * 04:|xx|xx|xx|xx|
 * 05:|xx|xx|xx|xx|
 * 06:|xx|xx|xx|xx|
 * 07:|xx|xx|xx|xx|
 * 08:|xx|xx|xx|xx|
 * 09:|xx|xx|xx|xx|
 * 0A:|xx|xx|xx|xx|
 * 0B:|xx|xx|xx|xx|
 *
 * xx = 1 Byte
 * BYTE#0 is the LSB
 * BYTE#3 is the MSB
 *
 * DONE
 */
namespace TURING_MACHINE {
    class Processor
    {
    public:
        // Register is a container of word_t
        using Register = word_t;

        // Bitwidth must of a power of 2 and greater-equal than 8 (for alignment purposes).
        Processor(std::size_t wordSizeInBytes = 2, std::size_t numPublicRegisters = 8, std::size_t numPrivateRegisters = 3);
        virtual ~Processor();

        std::size_t getWordSizeInBytes()const;
        std::size_t getNumPublicRegisters()const;
        std::size_t getNumPrivateRegisters()const;

        const Register& getPublicRegister(std::size_t idx)const;
        const Register& getPrivateRegister(std::size_t idx)const;

        void setPublicRegister(std::size_t idx, const Register& reg);
        void setPrivateRegister(std::size_t idx, const Register& reg);
    private:

        struct IMPL;
        std::unique_ptr<IMPL> m_impl;
    };
}
