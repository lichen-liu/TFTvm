#include "TFT_ARCH_Machine.h"

#include "TFT_ARCH.h"
#include "TuringMachine.h"


namespace TFT_ARCH {

    Machine::Machine(std::size_t memorySizeInBytes) :
        TURING_MACHINE::TuringMachine<InstrExecRequirement>
        (WORD_SIZE, NUM_PUBLIC_REGISTERS, NUM_PRIVATE_REGISTERS, memorySizeInBytes)
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