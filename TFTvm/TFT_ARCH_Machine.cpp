#include "TFT_ARCH.h"
#include "TFT_ARCH_machine.h"

#include "TFT_ARCH_instr_exec_requirement.h"
#include "turing_machine_prototype.h"


namespace TFT_ARCH {

    Machine::Machine(std::size_t memorySizeInBytes) :
        TURING_MACHINE::TuringMachinePrototype<InstrExecRequirement>
        (WORD_SIZE, PUBLIC_REG_E::NUM, PRIVATE_REG_E::NUM, memorySizeInBytes)
    {
    }

    Machine::~Machine()
    {
    }

    void Machine::runImplementation(TURING_MACHINE::Engine<InstrExecRequirement> & engine, std::size_t startingByteAddress)
    {
        engine;
        startingByteAddress;
    }
}