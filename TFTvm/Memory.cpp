#include "Memory.h"

#include <memory>
#include <cassert>
#include "MACHINE.h"


namespace MACHINE {

    struct Memory::IMPL {
        std::size_t memorySize;
        std::unique_ptr<byte_t[]> memory;
    };

    Memory::Memory(std::size_t memorySize) :m_impl(new IMPL)
    {
        m_impl->memorySize = memorySize;
        m_impl->memory.reset(new byte_t[memorySize]);
    }

    Memory::~Memory()
    {
    }

    std::size_t Memory::getSize() const
    {
        return m_impl->memorySize;
    }

    byte_t Memory::read(size_t byteAddress) const
    {
        assert(byteAddress < m_impl->memorySize);
        return m_impl->memory[byteAddress];
    }

    void Memory::write(size_t byteAddress, byte_t value)
    {
        assert(byteAddress < m_impl->memorySize);
        m_impl->memory[byteAddress] = value;
    }

    byte_t & Memory::operator[](std::size_t byteAddress)
    {
        assert(byteAddress < m_impl->memorySize);
        return m_impl->memory[byteAddress];
    }

    const byte_t & Memory::operator[](std::size_t byteAddress) const
    {
        assert(byteAddress < m_impl->memorySize);
        return m_impl->memory[byteAddress];
    }
}