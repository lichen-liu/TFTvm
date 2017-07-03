#include "Engine.h"

#include <cassert>

#include "MACHINE.h"
#include "Processor.h"
#include "Memory.h"


namespace MACHINE {

    struct Engine::IMPL {
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

    Engine::Engine(
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

    Engine::~Engine()
    {
    }

    std::size_t Engine::getWordSizeInBytes() const
    {
        return m_impl->wordSizeInBytes;
    }

    std::size_t Engine::getNumPublicRegisters() const
    {
        return m_impl->processor.getNumPublicRegisters();
    }

    std::size_t Engine::getNumPrivateRegisters() const
    {
        return m_impl->processor.getNumPrivateRegisters();
    }

    const word_t & Engine::getPublicRegisterContent(std::size_t idx) const
    {
        // implicit cast register to register content
        return m_impl->processor.getPublicRegister(idx);
    }

    const word_t & Engine::getPrivateRegisterContent(std::size_t idx) const
    {
        // implicit cast register to register content
        return m_impl->processor.getPrivateRegister(idx);
    }

    void Engine::setPublicRegisterContent(std::size_t idx, const word_t & regContent)
    {
        // implicit cast register content to register
        m_impl->processor.setPublicRegister(idx, regContent);
    }

    void Engine::setPrivateRegisterContent(std::size_t idx, const word_t & regContent)
    {
        // implicit cast register content to register
        m_impl->processor.setPrivateRegister(idx, regContent);
    }

    std::size_t Engine::getMemorySizeInBytes() const
    {
        return m_impl->memory.getSize();
    }

    byte_t Engine::readByte(std::size_t byteAddress) const
    {
        return m_impl->memory.read(byteAddress);
    }

    void Engine::writeByte(std::size_t byteAddress, byte_t value)
    {
        m_impl->memory.write(byteAddress, value);
    }

    word_t Engine::readWord(std::size_t address, addressable_e addressable, endian_e endian) const
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

    void Engine::writeWord(std::size_t address, const word_t & value, addressable_e addressable, endian_e endian)
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