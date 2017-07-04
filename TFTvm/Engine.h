#pragma once
#include <memory>

#include "TURING_MACHINE.h"
#include "Memory.h"
#include "Processor.h"


/*
 * This class provides the basic atomic behaviours of the machine.
 * Since this Engine needs to be generic enough to be able to adapt to a variety of architectures,
 * it is deigned to only supports a minimal sets of architecture-independent atomic operations.
 *
 * template <typename InstrExecRequirement> is the interface that defines the required methods
 * provided by this engine.
 *
 * <InstrExecRequirement>
 * |
 * Engine<InstrExecRequirement>
 *
 * DONE
 */
namespace TURING_MACHINE {

    enum class endian_e {
        little,
        big
    };

    enum class addressable_e {
        byte,
        word
    };


    template <typename InstrExecRequirement>
    class Engine : public InstrExecRequirement
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
        virtual std::size_t getWordSizeInBytes()const;


        // Register Operations
        virtual std::size_t getNumPublicRegisters()const;
        virtual std::size_t getNumPrivateRegisters()const;

        virtual const word_t& getPublicRegisterContent(std::size_t idx)const;
        virtual const word_t& getPrivateRegisterContent(std::size_t idx)const;

        virtual void setPublicRegisterContent(std::size_t idx, const word_t& regContent);
        virtual void setPrivateRegisterContent(std::size_t idx, const word_t& regContent);

        virtual void resetPublicRegisters();
        virtual void resetPrivateRegisters();
        virtual void resetRegisters();


        // Memory Operations
        virtual std::size_t getMemorySizeInBytes()const;

        // Byte access, use when BYTE_ADDRESSABLE=TRUE
        virtual byte_t readByte(std::size_t byteAddress)const;
        virtual void writeByte(std::size_t byteAddress, byte_t value);

        // Word access
        virtual word_t readWord(std::size_t address,
            addressable_e addressable = addressable_e::word,
            endian_e endian = endian_e::little)const;
        virtual void writeWord(std::size_t address, const word_t& value,
            addressable_e addressable = addressable_e::word,
            endian_e endian = endian_e::little);

    private:

        struct IMPL;
        std::unique_ptr<IMPL> m_impl;
    };
}

// Class Template requires both declaration and definition to be in the header file.
#include "Engine.tpp"
