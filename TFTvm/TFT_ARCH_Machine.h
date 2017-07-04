#pragma once
#include "TFT_ARCH_InstrExecRequirement.h"
#include "TuringMachine.h"


/*
*
* TURING_MACHINE::TuringMachine<InstrExecRequirement> = 0
* |
* Machine
*
*/
namespace TFT_ARCH {
    class Machine : public TURING_MACHINE::TuringMachine<InstrExecRequirement>
    {
    public:
        Machine(std::size_t memorySizeInBytes = 0);
        virtual ~Machine();

    private:
        virtual void runImplementation(TURING_MACHINE::Engine<InstrExecRequirement>& engine, std::size_t startingByteAddress) override;
    };
}
