#include "TFT_ARCH.h"
#include "TFT_ARCH_machine.h"

#include <cassert>
#include <memory>

#include "TFT_ARCH_instructions_actions.h"
#include "TFT_ARCH_instr_exec_requirement.h"
#include "turing_machine_prototype.h"
#include "word_t.h"


/* For Debugging Purposes */
// ===================================================================================================================
#include <algorithm>
#include <conio.h>
#include <iomanip>
#include <ostream>
#include <limits>
#include <sstream>
#include "TURING_MACHINE.h"

namespace {
    bool l_dump_engine(const TURING_MACHINE::Engine<TFT_ARCH::InstrExecRequirement> & engine, std::ostream& os) {
        std::stringstream out;

        constexpr int MAXWIDTH = 80;
        constexpr int SMALLFIELDWIDTH = 8;
        constexpr int FIELDWIDTH = 25;

        out << std::endl;
        out << std::setfill('#') << std::setw(MAXWIDTH) << "" << std::setfill(static_cast<char>(0)) << "" << std::endl;
        out << "ENGINE STATUS" << std::endl << std::endl;
        out << std::left << std::setw(FIELDWIDTH) << "Clock Cycle:"
            << std::right << std::setw(SMALLFIELDWIDTH) << engine.getCycleCount() << std::endl;

        out << std::left << std::setw(FIELDWIDTH) << "Word Size:"
            << std::right << std::setw(SMALLFIELDWIDTH) << (engine.getWordSizeInBytes()*std::numeric_limits<TURING_MACHINE::byte_t>::digits)
            << std::left << std::setw(FIELDWIDTH) << "  Bit"
            << std::right << std::setw(SMALLFIELDWIDTH) << engine.getWordSizeInBytes()
            << std::left << std::setw(FIELDWIDTH) << "  Byte" << std::endl;

        out << std::left << std::setw(FIELDWIDTH) << "Memory Size:"
            << std::right << std::setw(SMALLFIELDWIDTH) << engine.getMemorySizeInBytes()
            << std::left << std::setw(FIELDWIDTH) << "  Byte"
            << std::right << std::setw(SMALLFIELDWIDTH) << (engine.getMemorySizeInBytes() / engine.getWordSizeInBytes())
            << std::left << std::setw(FIELDWIDTH) << "  Word" << std::endl;

        out << std::left << std::setw(FIELDWIDTH) << "Num Registers:"
            << std::right << std::setw(SMALLFIELDWIDTH) << engine.getNumPublicRegisters()
            << std::left << std::setw(FIELDWIDTH) << "  Public"
            << std::right << std::setw(SMALLFIELDWIDTH) << engine.getNumPrivateRegisters()
            << std::left << std::setw(FIELDWIDTH) << "  Private" << std::endl;

        out << std::endl;
        out << std::left << std::setw(FIELDWIDTH + SMALLFIELDWIDTH) << "Public Register"
            << std::left << std::setw(FIELDWIDTH + SMALLFIELDWIDTH) << "  Private Register" << std::endl;
        std::size_t numRow = std::max(engine.getNumPublicRegisters(), engine.getNumPrivateRegisters());
        for (std::size_t i = 0; i < numRow; i++) {

            if (i < engine.getNumPublicRegisters()) {
                out << std::left << std::setw(0) << "[" << i << "]  "
                    << std::left << std::setw(FIELDWIDTH - 2) << engine.getPublicRegisterContent(i);
            }
            else {
                out << std::left << std::setw(FIELDWIDTH + 3) << "";
            }

            if (i < engine.getNumPrivateRegisters()) {
                out << std::right << std::setw(SMALLFIELDWIDTH) << "[" << i << "]  "
                    << std::left << std::setw(FIELDWIDTH) << engine.getPrivateRegisterContent(i);
            }
            else {
                out << std::left << std::setw(FIELDWIDTH + 3) << "";
            }

            out << std::endl;
        }

        out << std::setfill('#') << std::setw(MAXWIDTH) << "" << std::setfill(static_cast<char>(0)) << "" << std::endl;
        os << out.str();

        // Pause the console
        os << "Press <q> to Exit or <c> to Continue...";
        char result = static_cast<char>(_getch());
        os << std::endl << std::endl;

        return (result == 'c');
    }
}
// ===================================================================================================================


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
        assert((startingAddress*engine.getWordSizeInBytes()) < engine.getMemorySizeInBytes());

        // set initial program counter
        TURING_MACHINE::word_t programCounter(engine.getWordSizeInBytes());
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
             * For Debug Purpose
             */
            if (!executationSuccessful) {
                std::cout << std::endl;
                std::cout << "------------[HALTED] TFT_ARCH_MACHINE EXECUTION STOPPED ABNORMALLY!------------" << std::endl;
                std::cout << std::endl;
            }

            executationSuccessful &= l_dump_engine(engine, std::cout);
        }

        return executationSuccessful;
    }
}