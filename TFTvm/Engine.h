#pragma once
#include <memory>

#include "Processor.h"


/*
 * This class provides the basic atomic behaviours of the virtual machine system.
 * Since this Engine needs to be generic enough to be able to adapt to a variety of architectures,
 * it is deigned to only supports a minimal sets of architecture-independent atomic operations.
 */
namespace MACHINE {
    class Engine
    {
    public:
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
        std::size_t getWordSizeInBytes()const;


        // Register Operations
        std::size_t getNumPublicRegisters()const;
        std::size_t getNumPrivateRegisters()const;

        const Processor::Register& getPublicRegister(std::size_t idx)const;
        const Processor::Register& getPrivateRegister(std::size_t idx)const;

        void setPublicRegister(std::size_t idx, const Processor::Register& reg);
        void setPrivateRegister(std::size_t idx, const Processor::Register& reg);

    private:

        struct IMPL;
        std::unique_ptr<IMPL> m_impl;
    };
}
