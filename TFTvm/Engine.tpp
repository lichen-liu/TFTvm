#include "Engine.h"

#include <cassert>

#include "TURING_MACHINE.h"
#include "Processor.h"
#include "Memory.h"


/*
 * Class Template definition.
 * Do not compile this file.
 */
namespace TURING_MACHINE {
    template <typename InstrExecRequirement>
    struct Engine<InstrExecRequirement>::IMPL {
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

    template <typename InstrExecRequirement>
    Engine<InstrExecRequirement>::Engine(
        // Architecture-Related Settings
        std::size_t wordSizeInBytes,
        // Processor-Related
        std::size_t numPublicRegisters,
        std::size_t numPrivateRegisters,
        // Memory-Related
        std::size_t memorySizeInBytes) :
        m_impl(new IMPL(wordSizeInBytes, numPublicRegisters, numPrivateRegisters, memorySizeInBytes))
    {

    }

    template <typename InstrExecRequirement>
    Engine<InstrExecRequirement>::~Engine()
    {
    }

    template <typename InstrExecRequirement>
    std::size_t Engine<InstrExecRequirement>::getWordSizeInBytes() const
    {
        return m_impl->wordSizeInBytes;
    }

    template <typename InstrExecRequirement>
    std::size_t Engine<InstrExecRequirement>::getNumPublicRegisters() const
    {
        return m_impl->processor.getNumPublicRegisters();
    }

    template <typename InstrExecRequirement>
    std::size_t Engine<InstrExecRequirement>::getNumPrivateRegisters() const
    {
        return m_impl->processor.getNumPrivateRegisters();
    }

    template <typename InstrExecRequirement>
    const word_t & Engine<InstrExecRequirement>::getPublicRegisterContent(std::size_t idx) const
    {
        // implicitly cast register to register content
        return m_impl->processor.getPublicRegister(idx);
    }

    template <typename InstrExecRequirement>
    const word_t & Engine<InstrExecRequirement>::getPrivateRegisterContent(std::size_t idx) const
    {
        // implicitly cast register to register content
        return m_impl->processor.getPrivateRegister(idx);
    }

    template <typename InstrExecRequirement>
    void Engine<InstrExecRequirement>::setPublicRegisterContent(std::size_t idx, const word_t & regContent)
    {
        // implicitly cast register content to register
        m_impl->processor.setPublicRegister(idx, regContent);
    }

    template <typename InstrExecRequirement>
    void Engine<InstrExecRequirement>::setPrivateRegisterContent(std::size_t idx, const word_t & regContent)
    {
        // implicitly cast register content to register
        m_impl->processor.setPrivateRegister(idx, regContent);
    }

    template <typename InstrExecRequirement>
    void Engine<InstrExecRequirement>::resetPublicRegisters()
    {
        m_impl->processor.resetPublicRegisters();
    }

    template <typename InstrExecRequirement>
    void Engine<InstrExecRequirement>::resetPrivateRegisters()
    {
        m_impl->processor.resetPrivateRegisters();
    }

    template <typename InstrExecRequirement>
    void Engine<InstrExecRequirement>::resetRegisters()
    {
        m_impl->processor.resetRegisters();
    }

    template <typename InstrExecRequirement>
    std::size_t Engine<InstrExecRequirement>::getMemorySizeInBytes() const
    {
        return m_impl->memory.getSize();
    }

    template <typename InstrExecRequirement>
    byte_t Engine<InstrExecRequirement>::readByte(std::size_t byteAddress) const
    {
        return m_impl->memory.read(byteAddress);
    }

    template <typename InstrExecRequirement>
    void Engine<InstrExecRequirement>::writeByte(std::size_t byteAddress, byte_t value)
    {
        m_impl->memory.write(byteAddress, value);
    }

    template <typename InstrExecRequirement>
    word_t Engine<InstrExecRequirement>::readWord(std::size_t address, addressable_e addressable, endian_e endian) const
    {
        std::size_t byteAddress = 0;

        switch (addressable)
        {
        case addressable_e::byte:
            // The argument address is already the byteAddress (index of byte array)
            // Check alignment
            // The byteAddress must be a multiple of the word size in bytes
            assert(address % (m_impl->wordSizeInBytes) == 0);
            byteAddress = address;
            break;

        case addressable_e::word:
            // The argument address is a wordAddress (index of word array)
            // Convert the wordAddress to byteAddress
            byteAddress = address * (m_impl->wordSizeInBytes);
            break;

        default:
            assert(false);
        }

        word_t word(m_impl->wordSizeInBytes);

        for (std::size_t iByte = 0; iByte < m_impl->wordSizeInBytes; iByte++)
        {
            switch (endian)
            {
            case endian_e::little: // word.LSB = mem.LOW
                word[iByte] = m_impl->memory[byteAddress + iByte];
                break;

            case endian_e::big: // word.MSB = mem.LOW
                word[iByte] = m_impl->memory[byteAddress + m_impl->wordSizeInBytes - 1 - iByte];
                break;

            default:
                assert(false);
            }
        }

        return word;
    }

    template <typename InstrExecRequirement>
    void Engine<InstrExecRequirement>::writeWord(std::size_t address, const word_t & value, addressable_e addressable, endian_e endian)
    {
        assert(value.size() == m_impl->wordSizeInBytes);

        std::size_t byteAddress = 0;

        switch (addressable)
        {
        case addressable_e::byte:
            // The argument address is already the byteAddress (index of byte array)
            // Check alignment
            // The byteAddress must be a multiple of the word size in bytes
            assert(address % (m_impl->wordSizeInBytes) == 0);
            byteAddress = address;
            break;

        case addressable_e::word:
            // The argument address is a wordAddress (index of word array)
            // Convert the wordAddress to byteAddress
            byteAddress = address * (m_impl->wordSizeInBytes);
            break;

        default:
            assert(false);
        }

        for (std::size_t iByte = 0; iByte < m_impl->wordSizeInBytes; iByte++)
        {
            switch (endian)
            {
            case endian_e::little: // word.LSB = mem.LOW
                m_impl->memory[byteAddress + iByte] = value[iByte];
                break;

            case endian_e::big: // word.MSB = mem.LOW
                m_impl->memory[byteAddress + m_impl->wordSizeInBytes - 1 - iByte] = value[iByte];
                break;

            default:
                assert(false);
            }
        }
    }
}