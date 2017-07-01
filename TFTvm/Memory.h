#pragma once
#include <memory>

#include "MACHINE.h"


/*
 * This class implements the most minimal interface of a memory.
 * This memory is implemented as a byte array. All operations at word
 * level should be handled at a higher level.
 *
 * DONE
 */
namespace MACHINE {
    class Memory
    {
    public:
        Memory(std::size_t memorySize = 0);
        virtual ~Memory() = default;

        std::size_t getSize()const;

        byte_t read(std::size_t byteAddress)const;
        void write(std::size_t byteAddress, byte_t value)const;

    private:

        struct IMPL;
        std::unique_ptr<IMPL> m_impl;
    };
}
