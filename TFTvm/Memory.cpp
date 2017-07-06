#include "memory.h"
#include "TURING_MACHINE.h"

#include <cassert>
#include <memory>


namespace TURING_MACHINE {

    struct Memory::IMPL {
        std::size_t memorySize;
        std::unique_ptr<byte_t[]> memory; /*0...memorySize-1*/
    };

    Memory::Memory(std::size_t memorySize) :impl_(new IMPL)
    {
        impl_->memorySize = memorySize;
        impl_->memory.reset(new byte_t[memorySize]);
        // memory is not initialized due to its nature
    }

    Memory::~Memory()
    {
    }

    std::size_t Memory::getSize() const
    {
        return impl_->memorySize;
    }

    byte_t Memory::read(size_t byteAddress) const
    {
        assert(byteAddress < impl_->memorySize);
        return impl_->memory[byteAddress];
    }

    void Memory::write(size_t byteAddress, byte_t value)
    {
        assert(byteAddress < impl_->memorySize);
        impl_->memory[byteAddress] = value;
    }

    byte_t & Memory::operator[](std::size_t byteAddress)
    {
        assert(byteAddress < impl_->memorySize);
        return impl_->memory[byteAddress];
    }

    const byte_t & Memory::operator[](std::size_t byteAddress) const
    {
        assert(byteAddress < impl_->memorySize);
        return impl_->memory[byteAddress];
    }
}