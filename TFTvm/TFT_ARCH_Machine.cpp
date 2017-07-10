#include "TFT_ARCH.h"
#include "TFT_ARCH_machine.h"

#include <cassert>
#include <memory>

#include "TFT_ARCH_instructions_actions.h"
#include "TFT_ARCH_instr_exec_requirement.h"
#include "turing_machine_prototype.h"
#include "word_t.h"


namespace TFT_ARCH {

    Machine::Machine(std::size_t memorySizeInBytes) :
        TURING_MACHINE::TuringMachinePrototype<InstrExecRequirement>
        (WORD_SIZE, PUBLIC_REG_E::NUM, PRIVATE_REG_E::NUM, memorySizeInBytes)
    {
    }

    Machine::~Machine()
    {
    }

    bool Machine::runImplementation(TURING_MACHINE::Engine<InstrExecRequirement> & engine, std::size_t startingAddress)
    {
        // startingByteAddress should not exceed the memory byte size
        assert((startingAddress*WORD_SIZE) < engine.getMemorySizeInBytes());

        // set initial program counter
        TURING_MACHINE::word_t programCounter(WORD_SIZE);
        programCounter.setValue(startingAddress);
        engine.setPublicRegisterContent(PUBLIC_REG_E::PC, programCounter);

        bool executationSuccessful = true;
        // Executation Loop
        while (executationSuccessful) {
            if (executationSuccessful)
                executationSuccessful &= engine.cycle0(TFT_ARCH_InstructionAction::getNOOPInstructionAction());
            if (executationSuccessful)
                executationSuccessful &= engine.cycle1(TFT_ARCH_InstructionAction::getNOOPInstructionAction());
            if (executationSuccessful)
                executationSuccessful &= engine.cycle2(TFT_ARCH_InstructionAction::getNOOPInstructionAction());

            std::unique_ptr<TFT_ARCH_InstructionAction> instructionAction_ptr;
            if (executationSuccessful) {
                instructionAction_ptr.reset(TFT_ARCH_InstructionAction::createInstructionAction(engine.privateRegisterContent(PRIVATE_REG_E::IR)));
                executationSuccessful &= static_cast<bool>(instructionAction_ptr);
            }

            if (executationSuccessful)
                executationSuccessful &= engine.cycle3(*instructionAction_ptr);
            if (executationSuccessful)
                executationSuccessful &= engine.cycle4(*instructionAction_ptr);
            if (executationSuccessful)
                executationSuccessful &= engine.cycle5(*instructionAction_ptr);
            if (executationSuccessful)
                executationSuccessful &= engine.cycle6(*instructionAction_ptr);

            /*
             * TODO: Output the content inside registers and memory.
             */
        }

        return executationSuccessful;
    }
}