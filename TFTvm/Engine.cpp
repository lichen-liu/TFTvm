#include "Engine.h"

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

    const Processor::Register & Engine::getPublicRegister(std::size_t idx) const
    {
        return m_impl->processor.getPublicRegister(idx);
    }

    const Processor::Register & Engine::getPrivateRegister(std::size_t idx) const
    {
        return m_impl->processor.getPrivateRegister(idx);
    }

    void Engine::setPublicRegister(std::size_t idx, const Processor::Register & reg)
    {
        m_impl->processor.setPublicRegister(idx, reg);
    }

    void Engine::setPrivateRegister(std::size_t idx, const Processor::Register & reg)
    {
        m_impl->processor.setPrivateRegister(idx, reg);
    }
}