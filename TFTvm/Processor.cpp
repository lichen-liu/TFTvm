#include "Processor.h"

#include <cassert>
#include <vector>


namespace TURING_MACHINE {
    using RegisterFile = std::vector<Processor::Register>;

    struct Processor::IMPL {
        std::size_t wordSizeInBytes;
        std::size_t numPublicRegisters;
        std::size_t numPrivateRegisters;

        RegisterFile publicRF;
        RegisterFile privateRF;
    };

    Processor::Processor(std::size_t wordSizeInBytes, std::size_t numPublicRegisters, std::size_t numPrivateRegisters) :
        m_impl(new IMPL)
    {
        assert((wordSizeInBytes >= 1) && ((wordSizeInBytes & (wordSizeInBytes - 1)) == 0));

        m_impl->wordSizeInBytes = wordSizeInBytes;
        m_impl->numPublicRegisters = numPublicRegisters;
        m_impl->numPrivateRegisters = numPrivateRegisters;

        // Initialize the RFs
        m_impl->publicRF.resize(numPublicRegisters, Register(m_impl->wordSizeInBytes));
        m_impl->privateRF.resize(numPrivateRegisters, Register(m_impl->wordSizeInBytes));
    }

    Processor::~Processor()
    {
    }

    std::size_t Processor::getWordSizeInBytes() const
    {
        return m_impl->wordSizeInBytes;
    }

    std::size_t Processor::getNumPublicRegisters() const
    {
        return m_impl->numPublicRegisters;
    }

    std::size_t Processor::getNumPrivateRegisters() const
    {
        return m_impl->numPrivateRegisters;
    }

    const Processor::Register & Processor::getPublicRegister(std::size_t idx) const
    {
        assert(idx < m_impl->numPublicRegisters);
        return m_impl->publicRF[idx];
    }

    const Processor::Register & Processor::getPrivateRegister(std::size_t idx) const
    {
        assert(idx < m_impl->numPrivateRegisters);
        return m_impl->privateRF[idx];
    }

    void Processor::setPublicRegister(std::size_t idx, const Processor::Register & reg)
    {
        assert(idx < m_impl->numPublicRegisters);
        assert(reg.size() == m_impl->wordSizeInBytes);
        m_impl->publicRF[idx] = reg;
    }

    void Processor::setPrivateRegister(std::size_t idx, const Processor::Register & reg)
    {
        assert(idx < m_impl->numPrivateRegisters);
        assert(reg.size() == m_impl->wordSizeInBytes);
        m_impl->privateRF[idx] = reg;
    }
}