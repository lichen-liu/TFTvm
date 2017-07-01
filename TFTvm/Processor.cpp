#include "Processor.h"

#include <cassert>
#include <vector>


namespace MACHINE {
    using RegisterFile = std::vector<Processor::Register>;

    struct Processor::IMPL {
        std::size_t wordSizeInBytes;
        std::size_t numPublicRegisters;
        std::size_t numPrivateRegisters;

        RegisterFile publicRF;
        RegisterFile privateRF;
    };

    Processor::Processor(std::size_t wordSizeInBits, std::size_t numPublicRegisters, std::size_t numPrivateRegisters) :
        m_impl(new IMPL)
    {
        assert(wordSizeInBits >= 8 && (wordSizeInBits & (wordSizeInBits - 1)));

        m_impl->wordSizeInBytes = wordSizeInBits / BYTE_SIZE;
        m_impl->numPublicRegisters = numPublicRegisters;
        m_impl->numPrivateRegisters = numPrivateRegisters;

        // Initialize the RFs
        m_impl->publicRF.resize(numPublicRegisters, Register(m_impl->wordSizeInBytes));
        m_impl->privateRF.resize(numPrivateRegisters, Register(m_impl->wordSizeInBytes));
    }
}