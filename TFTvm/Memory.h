#pragma once
#include "TURING_MACHINE.h"

#include <memory>


/*
 * This class implements the most minimal interface of a memory.
 * This memory is implemented as a byte array. All operations at word
 * level should be handled at a higher level.
 *
 * 00:|xx|
 * 01:|xx|
 * 02:|xx|
 * 03:|xx|
 * 04:|xx|
 * 05:|xx|
 * 06:|xx|
 * 07:|xx|
 * 08:|xx|
 * 09:|xx|
 * 0A:|xx|
 * 0B:|xx|
 *
 * xx = 1 Byte
 *
 * DONE
 */
namespace TURING_MACHINE {
    class Memory
    {
    public:
        Memory(std::size_t memorySize = 0);
        virtual ~Memory();

        std::size_t getSize()const;

        byte_t read(std::size_t byteAddress)const;
        void write(std::size_t byteAddress, byte_t value);

        byte_t& operator[] (std::size_t byteAddress);
        const byte_t& operator[] (std::size_t byteAddress)const;

    private:

        struct IMPL;
        std::unique_ptr<IMPL> impl_;
    };
}
