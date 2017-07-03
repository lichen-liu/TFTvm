#pragma once
#include <memory>

#include "Engine.h"


/*
 *
 * <InstructionExecutationStages> => 0
 * |
 * TuringMachine<InstructionExecutationStages> = 0
 *
 */
namespace TURING_MACHINE {

    template<typename  InstructionExecutationStages>
    class TuringMachine :
        public InstructionExecutationStages
    {
    public:
        TuringMachine(
            std::size_t wordSizeInBytes = 2,
            std::size_t numPublicRegisters = 8,
            std::size_t numPrivateRegisters = 3,
            std::size_t memorySizeInBytes = 0) :
            engine(new Engine(wordSizeInBytes, numPublicRegisters, numPrivateRegisters, memorySizeInBytes)) {}

        virtual ~TuringMachine() {}


        // Define the interface that an actual TuringMachine should have
        virtual void run() = 0;

    protected:
        std::unique_ptr<Engine> engine;
    };
}
