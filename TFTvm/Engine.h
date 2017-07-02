#pragma once
#include <memory>

#include "MACHINE.h"


/*
 * This class provides the basic atomic behaviours of the machine.
 * Since this Engine needs to be generic enough to be able to adapt to a variety of architectures,
 * it is deigned to only supports a minimal sets of architecture-independent atomic operations.
 */
namespace MACHINE {

    enum class endian_e {
        little,
        big
    };

    enum class addressable_e {
        byte,
        word
    };

    class Engine
    {
    public:
        Engine(
            // Architecture-Related Settings
            std::size_t wordSizeInBytes = 2,
            // Processor-Related
            std::size_t numPublicRegisters = 8,
            std::size_t numPrivateRegisters = 3,
            // Memory-Related
            std::size_t memorySizeInBytes = 0);

        virtual ~Engine();


        // Architecture-Related
        std::size_t getWordSizeInBytes()const;


        // Register Operations
        std::size_t getNumPublicRegisters()const;
        std::size_t getNumPrivateRegisters()const;

        const word_t& getPublicRegisterContent(std::size_t idx)const;
        const word_t& getPrivateRegisterContent(std::size_t idx)const;

        void setPublicRegisterContent(std::size_t idx, const word_t& regContent);
        void setPrivateRegisterContent(std::size_t idx, const word_t& regContent);


        // Memory Operations
        std::size_t getMemorySizeInBytes()const;

        // Byte access, use when BYTE_ADDRESSABLE=TRUE
        byte_t readByte(std::size_t byteAddress)const;
        void writeByte(std::size_t byteAddress, byte_t value);

        // Word access
        word_t readWord(std::size_t address,
            addressable_e addressable = addressable_e::word,
            endian_e endian = endian_e::little)const;
        void writeWord(std::size_t address, const word_t& value,
            addressable_e addressable = addressable_e::word,
            endian_e endian = endian_e::little);

    private:

        struct IMPL;
        std::unique_ptr<IMPL> m_impl;
    };
}
