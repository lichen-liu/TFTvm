#pragma once
#include "TFT_ARCH_instr_exec_requirement.h"
#include "turing_machine_prototype.h"


/*
*
* TURING_MACHINE::TuringMachinePrototype<InstrExecRequirement> = 0
* |
* Machine
*
*/
namespace TFT_ARCH {
    class Machine : public TURING_MACHINE::TuringMachinePrototype<InstrExecRequirement>
    {
    public:
        Machine(std::size_t memorySizeInBytes = 0);
        virtual ~Machine();

    private:
        virtual void runImplementation(TURING_MACHINE::Engine<InstrExecRequirement>& engine, std::size_t startingByteAddress) override;
    };
}
