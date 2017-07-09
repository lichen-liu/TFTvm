#pragma once
#include "TURING_MACHINE.h"

#include <memory>

#include "memory.h"
#include "processor.h"
#include "word_t.h"


/*
 * This class provides the basic atomic behaviours of the machine.
 * Since this Engine needs to be generic enough to be able to adapt to a variety of architectures,
 * it is deigned to only supports a minimal sets of architecture-independent atomic operations.
 *
 * template <typename EngineRequirement> is the interface that defines the required methods
 * provided by this engine.
 *
 * <EngineRequirement>
 * |
 * Engine<typename EngineRequirement>
 *
 * DONE
 */
namespace TURING_MACHINE {

    template <typename EngineRequirement>
    class Engine : public EngineRequirement
    {
    public:
        /*
         * TODO: pass the args to the base contructor
         */
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

        virtual word_t& publicRegisterContent(std::size_t pos);
        virtual const word_t& publicRegisterContent(std::size_t pos)const;
        virtual word_t& privateRegisterContent(std::size_t pos);
        virtual const word_t& privateRegisterContent(std::size_t pos)const;

        virtual const word_t& getPublicRegisterContent(std::size_t pos)const;
        virtual const word_t& getPrivateRegisterContent(std::size_t pos)const;

        virtual void setPublicRegisterContent(std::size_t pos, const word_t& regContent);
        virtual void setPrivateRegisterContent(std::size_t pos, const word_t& regContent);

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
        std::unique_ptr<IMPL> impl_;
    };
}

// Class Template requires both declaration and definition to be in the header file.
#include "engine.tpp"
