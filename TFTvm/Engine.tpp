#include "engine.h"
#include "TURING_MACHINE.h"

#include <cassert>

#include "memory.h"
#include "processor.h"
#include "word_t.h"


/*
 * Class Template definition.
 * Do not compile this file.
 */
namespace TURING_MACHINE {
    template <typename EngineRequirement>
    struct Engine<EngineRequirement>::IMPL {
        // Physical Components
        Processor processor;
        Memory memory;

        // Architecture-Related Settings
        std::size_t wordSizeInBytes;


        // Constructor
        IMPL(std::size_t wordSizeInBytes,
            std::size_t numPublicRegisters,
            std::size_t numPrivateRegisters,
            std::size_t memorySizeInBytes) :
            processor(wordSizeInBytes, numPublicRegisters, numPrivateRegisters),
            memory(memorySizeInBytes)
        {
            this->wordSizeInBytes = wordSizeInBytes;
        }

        IMPL() = delete;
    };

    template <typename EngineRequirement>
    Engine<EngineRequirement>::Engine(
        // Architecture-Related Settings
        std::size_t wordSizeInBytes,
        // Processor-Related
        std::size_t numPublicRegisters,
        std::size_t numPrivateRegisters,
        // Memory-Related
        std::size_t memorySizeInBytes) :
        impl_(new IMPL(wordSizeInBytes, numPublicRegisters, numPrivateRegisters, memorySizeInBytes))
    {

    }

    template <typename EngineRequirement>
    Engine<EngineRequirement>::~Engine()
    {
    }

    template <typename EngineRequirement>
    std::size_t Engine<EngineRequirement>::getWordSizeInBytes() const
    {
        return impl_->wordSizeInBytes;
    }

    template <typename EngineRequirement>
    std::size_t Engine<EngineRequirement>::getNumPublicRegisters() const
    {
        return impl_->processor.getNumPublicRegisters();
    }

    template <typename EngineRequirement>
    std::size_t Engine<EngineRequirement>::getNumPrivateRegisters() const
    {
        return impl_->processor.getNumPrivateRegisters();
    }

    template <typename EngineRequirement>
    word_t Engine<EngineRequirement>::getPublicRegisterContent(std::size_t pos) const
    {
        // implicitly cast register to register content
        return impl_->processor.getPublicRegister(pos);
    }

    template <typename EngineRequirement>
    word_t Engine<EngineRequirement>::getPrivateRegisterContent(std::size_t pos) const
    {
        // implicitly cast register to register content
        return impl_->processor.getPrivateRegister(pos);
    }

    template <typename EngineRequirement>
    void Engine<EngineRequirement>::setPublicRegisterContent(std::size_t pos, const word_t & regContent)
    {
        // implicitly cast register content to register
        impl_->processor.setPublicRegister(pos, regContent);
    }

    template <typename EngineRequirement>
    void Engine<EngineRequirement>::setPrivateRegisterContent(std::size_t pos, const word_t & regContent)
    {
        // implicitly cast register content to register
        impl_->processor.setPrivateRegister(pos, regContent);
    }

    template <typename EngineRequirement>
    void Engine<EngineRequirement>::resetPublicRegisters()
    {
        impl_->processor.resetPublicRegisters();
    }

    template <typename EngineRequirement>
    void Engine<EngineRequirement>::resetPrivateRegisters()
    {
        impl_->processor.resetPrivateRegisters();
    }

    template <typename EngineRequirement>
    void Engine<EngineRequirement>::resetRegisters()
    {
        impl_->processor.resetRegisters();
    }

    template <typename EngineRequirement>
    std::size_t Engine<EngineRequirement>::getMemorySizeInBytes() const
    {
        return impl_->memory.getSize();
    }

    template <typename EngineRequirement>
    byte_t Engine<EngineRequirement>::readByte(std::size_t byteAddress) const
    {
        return impl_->memory.read(byteAddress);
    }

    template <typename EngineRequirement>
    void Engine<EngineRequirement>::writeByte(std::size_t byteAddress, byte_t value)
    {
        impl_->memory.write(byteAddress, value);
    }

    template <typename EngineRequirement>
    word_t Engine<EngineRequirement>::readWord(std::size_t address, addressable_e addressable, endian_e endian) const
    {
        std::size_t byteAddress = 0;

        switch (addressable)
        {
        case addressable_e::byte:
            // The argument address is already the byteAddress (index of byte array)
            // Check alignment
            // The byteAddress must be a multiple of the word size in bytes
            assert(address % (impl_->wordSizeInBytes) == 0);
            byteAddress = address;
            break;

        case addressable_e::word:
            // The argument address is a wordAddress (index of word array)
            // Convert the wordAddress to byteAddress
            byteAddress = address * (impl_->wordSizeInBytes);
            break;

        default:
            assert(false);
        }

        word_t word(impl_->wordSizeInBytes);

        for (std::size_t iByte = 0; iByte < impl_->wordSizeInBytes; iByte++)
        {
            switch (endian)
            {
            case endian_e::little: // word.LSB = mem.LOW
                word[iByte] = impl_->memory[byteAddress + iByte];
                break;

            case endian_e::big: // word.MSB = mem.LOW
                word[iByte] = impl_->memory[byteAddress + impl_->wordSizeInBytes - 1 - iByte];
                break;

            default:
                assert(false);
            }
        }

        return word;
    }

    template <typename EngineRequirement>
    void Engine<EngineRequirement>::writeWord(std::size_t address, const word_t & value, addressable_e addressable, endian_e endian)
    {
        assert(value.size() == impl_->wordSizeInBytes);

        std::size_t byteAddress = 0;

        switch (addressable)
        {
        case addressable_e::byte:
            // The argument address is already the byteAddress (index of byte array)
            // Check alignment
            // The byteAddress must be a multiple of the word size in bytes
            assert(address % (impl_->wordSizeInBytes) == 0);
            byteAddress = address;
            break;

        case addressable_e::word:
            // The argument address is a wordAddress (index of word array)
            // Convert the wordAddress to byteAddress
            byteAddress = address * (impl_->wordSizeInBytes);
            break;

        default:
            assert(false);
        }

        for (std::size_t iByte = 0; iByte < impl_->wordSizeInBytes; iByte++)
        {
            switch (endian)
            {
            case endian_e::little: // word.LSB = mem.LOW
                impl_->memory[byteAddress + iByte] = value[iByte];
                break;

            case endian_e::big: // word.MSB = mem.LOW
                impl_->memory[byteAddress + impl_->wordSizeInBytes - 1 - iByte] = value[iByte];
                break;

            default:
                assert(false);
            }
        }
    }
}