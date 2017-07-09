#include "TFT_ARCH.h"
#include "TFT_ARCH_instr_exec_requirement.h"


/*
 * The implementation of cycles are for Engine only.
 * The implementation of hardware requirements are for InstructionAction only.
 */
namespace TFT_ARCH {

    /*
     * cycle0 is the same for all instructions.
     * This cycle is for storing PC into arbitrary ADDR(not modeled).
     */
    bool InstrExecRequirement::cycle0(InstrExecRequirement & instruction)
    {
        instruction;
        cycleCount_++;

        return true;
    }

    /*
     * cycle1 is the same for all instructions.
     * This cycle is for memory access (read instruction)
     */
    bool InstrExecRequirement::cycle1(InstrExecRequirement & instruction)
    {
        instruction;
        cycleCount_ += MEMORY_DELAY_IN_CYCLE;

        std::size_t addr = getPublicRegisterContent(PUBLIC_REG_E::PC).template getValue<std::size_t>();
        setPrivateRegisterContent(PRIVATE_REG_E::IR, readWord(addr, ADDRESSABLE, ENDIAN));

        return true;
    }

    /*
     * cycle2 is the same for all instructions.
     */
    bool InstrExecRequirement::cycle2(InstrExecRequirement & instruction)
    {
        cycleCount_++;
        return instruction.cycle2(*this); // pass this engine instance to instruction
    }

    bool InstrExecRequirement::cycle3(InstrExecRequirement & instruction)
    {
        cycleCount_++;
        return instruction.cycle3(*this); // pass this engine instance to instruction
    }

    bool InstrExecRequirement::cycle4(InstrExecRequirement & instruction)
    {
        cycleCount_++;
        return instruction.cycle4(*this); // pass this engine instance to instruction
    }

    bool InstrExecRequirement::cycle5(InstrExecRequirement & instruction)
    {
        cycleCount_++;
        return instruction.cycle5(*this); // pass this engine instance to instruction
    }

    bool InstrExecRequirement::cycle6(InstrExecRequirement & instruction)
    {
        cycleCount_++;
        return instruction.cycle6(*this); // pass this engine instance to instruction
    }

    TURING_MACHINE::word_t InstrExecRequirement::getPublicRegisterContent(std::size_t pos) const
    {
        pos;
        return TURING_MACHINE::word_t();
    }

    TURING_MACHINE::word_t InstrExecRequirement::getPrivateRegisterContent(std::size_t pos) const
    {
        pos;
        return TURING_MACHINE::word_t();
    }

    void InstrExecRequirement::setPublicRegisterContent(std::size_t pos, const TURING_MACHINE::word_t & regContent)
    {
        pos;
        regContent;
    }

    void InstrExecRequirement::setPrivateRegisterContent(std::size_t pos, const TURING_MACHINE::word_t & regContent)
    {
        pos;
        regContent;
    }

    std::size_t InstrExecRequirement::getMemorySizeInBytes() const
    {
        return std::size_t();
    }

    TURING_MACHINE::word_t InstrExecRequirement::readWord(std::size_t address, TURING_MACHINE::addressable_e addressable, TURING_MACHINE::endian_e endian) const
    {
        address;
        addressable;
        endian;
        return TURING_MACHINE::word_t();
    }

    void InstrExecRequirement::writeWord(std::size_t address, const TURING_MACHINE::word_t & value, TURING_MACHINE::addressable_e addressable, TURING_MACHINE::endian_e endian)
    {
        address;
        value;
        addressable;
        endian;
    }

    std::size_t InstrExecRequirement::getCycleCount() const
    {
        return cycleCount_;
    }

    std::size_t InstrExecRequirement::incrementCycleCount()
    {
        cycleCount_++;
        return cycleCount_;
    }

    void InstrExecRequirement::resetCycleCount()
    {
        cycleCount_ = 0;
    }
}
