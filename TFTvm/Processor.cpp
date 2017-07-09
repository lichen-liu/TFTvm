#include "processor.h"

#include <algorithm>
#include <cassert>
#include <vector>


namespace TURING_MACHINE {
    using RegisterFile = std::vector<Processor::Register>;

    struct Processor::IMPL {
        std::size_t wordSizeInBytes;
        std::size_t numPublicRegisters;
        std::size_t numPrivateRegisters;

        RegisterFile publicRF; /*0...numPublicRegisters-1*/
        RegisterFile privateRF; /*0...numPrivateRegisters-1*/
    };

    Processor::Processor(std::size_t wordSizeInBytes, std::size_t numPublicRegisters, std::size_t numPrivateRegisters) :
        impl_(new IMPL)
    {
        assert((wordSizeInBytes >= 1) && ((wordSizeInBytes & (wordSizeInBytes - 1)) == 0));

        impl_->wordSizeInBytes = wordSizeInBytes;
        impl_->numPublicRegisters = numPublicRegisters;
        impl_->numPrivateRegisters = numPrivateRegisters;

        // Initialize the RFs
        impl_->publicRF.resize(numPublicRegisters, Register(impl_->wordSizeInBytes));
        impl_->privateRF.resize(numPrivateRegisters, Register(impl_->wordSizeInBytes));
    }

    Processor::~Processor()
    {
    }

    std::size_t Processor::getWordSizeInBytes() const
    {
        return impl_->wordSizeInBytes;
    }

    std::size_t Processor::getNumPublicRegisters() const
    {
        return impl_->numPublicRegisters;
    }

    std::size_t Processor::getNumPrivateRegisters() const
    {
        return impl_->numPrivateRegisters;
    }

    Processor::Register & Processor::publicRegister(std::size_t pos)
    {
        assert(pos < impl_->numPublicRegisters);
        return impl_->publicRF[pos];
    }

    const Processor::Register & Processor::publicRegister(std::size_t pos) const
    {
        assert(pos < impl_->numPublicRegisters);
        return impl_->publicRF[pos];
    }

    Processor::Register & Processor::privateRegister(std::size_t pos)
    {
        assert(pos < impl_->numPrivateRegisters);
        return impl_->privateRF[pos];
    }

    const Processor::Register & Processor::privateRegister(std::size_t pos) const
    {
        assert(pos < impl_->numPrivateRegisters);
        return impl_->privateRF[pos];
    }

    const Processor::Register & Processor::getPublicRegister(std::size_t pos) const
    {
        assert(pos < impl_->numPublicRegisters);
        return impl_->publicRF[pos];
    }

    const Processor::Register & Processor::getPrivateRegister(std::size_t pos) const
    {
        assert(pos < impl_->numPrivateRegisters);
        return impl_->privateRF[pos];
    }

    void Processor::setPublicRegister(std::size_t pos, const Processor::Register & reg)
    {
        assert(pos < impl_->numPublicRegisters);
        assert(reg.size() == impl_->wordSizeInBytes);
        impl_->publicRF[pos] = reg;
    }

    void Processor::setPrivateRegister(std::size_t pos, const Processor::Register & reg)
    {
        assert(pos < impl_->numPrivateRegisters);
        assert(reg.size() == impl_->wordSizeInBytes);
        impl_->privateRF[pos] = reg;
    }

    void Processor::resetPublicRegisters()
    {
        std::for_each(impl_->publicRF.begin(), impl_->publicRF.end(), [](Register& reg) {reg.clear(); });
    }

    void Processor::resetPrivateRegisters()
    {
        std::for_each(impl_->privateRF.begin(), impl_->privateRF.end(), [](Register& reg) {reg.clear(); });
    }

    void Processor::resetRegisters()
    {
        resetPublicRegisters();
        resetPrivateRegisters();
    }
}