#include "TFT_ARCH.h"
#include "TFT_ARCH_instr_exec_requirement.h"


/*
 * The implementation of cycles are for Engine only.
 * The implementation of hardware requirements are for InstructionAction only.
 */
namespace TFT_ARCH {

    /*
     * cycle0 is the same for all instructions.
     * ADDR<-[PC]
     */
    bool InstrExecRequirement::cycle0(InstrExecRequirement & instruction)
    {
        instruction;/*Unused Reference*/
        cycleCount_++;

        setPrivateRegisterContent(PRIVATE_REG_E::ADDR, publicRegisterContent(PUBLIC_REG_E::PC));

        return true;
    }

    /*
     * cycle1 is the same for all instructions.
     * This stage is for memory access.
     */
    bool InstrExecRequirement::cycle1(InstrExecRequirement & instruction)
    {
        instruction;/*Unused Reference*/
        cycleCount_ += (MEMORY_DELAY_IN_CYCLE + 1);

        return true;
    }

    /*
     * cycle2 is the same for all instructions.
     * [PC]++
     * IR<-MEM[[ADDR]]
     */
    bool InstrExecRequirement::cycle2(InstrExecRequirement & instruction)
    {
        instruction;/*Unused Reference*/
        cycleCount_++;

        ++publicRegisterContent(PUBLIC_REG_E::PC);
        std::size_t addr = getPrivateRegisterContent(PRIVATE_REG_E::ADDR).template getValue<std::size_t>();
        setPrivateRegisterContent(PRIVATE_REG_E::IR, readWord(addr, ADDRESSABLE, ENDIAN));

        return true;
    }

    /*
     * cycle3 is instruction-dependent.
     */
    bool InstrExecRequirement::cycle3(InstrExecRequirement & instruction)
    {
        return instruction.cycle3(*this); // pass this engine instance to instruction
    }

    /*
     * cycle4 is instruction-dependent.
     */
    bool InstrExecRequirement::cycle4(InstrExecRequirement & instruction)
    {
        return instruction.cycle4(*this); // pass this engine instance to instruction
    }

    /*
     * cycle5 is instruction-dependent.
     */
    bool InstrExecRequirement::cycle5(InstrExecRequirement & instruction)
    {
        return instruction.cycle5(*this); // pass this engine instance to instruction
    }

    /*
     * cycle6 is instruction-dependent.
     */
    bool InstrExecRequirement::cycle6(InstrExecRequirement & instruction)
    {
        return instruction.cycle6(*this); // pass this engine instance to instruction
    }

    TURING_MACHINE::word_t & InstrExecRequirement::publicRegisterContent(std::size_t pos)
    {
        return publicRegisterContent(pos);
    }

    const TURING_MACHINE::word_t & InstrExecRequirement::publicRegisterContent(std::size_t pos) const
    {
        return publicRegisterContent(pos);
    }

    TURING_MACHINE::word_t & InstrExecRequirement::privateRegisterContent(std::size_t pos)
    {
        return privateRegisterContent(pos);
    }

    const TURING_MACHINE::word_t & InstrExecRequirement::privateRegisterContent(std::size_t pos) const
    {
        return privateRegisterContent(pos);
    }

    const TURING_MACHINE::word_t& InstrExecRequirement::getPublicRegisterContent(std::size_t pos) const
    {
        return getPublicRegisterContent(pos);
    }

    const TURING_MACHINE::word_t& InstrExecRequirement::getPrivateRegisterContent(std::size_t pos) const
    {
        return getPrivateRegisterContent(pos);
    }

    void InstrExecRequirement::setPublicRegisterContent(std::size_t pos, const TURING_MACHINE::word_t & regContent)
    {
        pos;/*Unused Reference*/
        regContent;/*Unused Reference*/
    }

    void InstrExecRequirement::setPrivateRegisterContent(std::size_t pos, const TURING_MACHINE::word_t & regContent)
    {
        pos;/*Unused Reference*/
        regContent;/*Unused Reference*/
    }

    std::size_t InstrExecRequirement::getMemorySizeInBytes() const
    {
        return std::size_t();
    }

    TURING_MACHINE::word_t InstrExecRequirement::readWord(std::size_t address, TURING_MACHINE::addressable_e addressable, TURING_MACHINE::endian_e endian) const
    {
        address;/*Unused Reference*/
        addressable;/*Unused Reference*/
        endian;/*Unused Reference*/
        return TURING_MACHINE::word_t();
    }

    void InstrExecRequirement::writeWord(std::size_t address, const TURING_MACHINE::word_t & value, TURING_MACHINE::addressable_e addressable, TURING_MACHINE::endian_e endian)
    {
        address;/*Unused Reference*/
        value;/*Unused Reference*/
        addressable;/*Unused Reference*/
        endian;/*Unused Reference*/
    }

    std::size_t InstrExecRequirement::getCycleCount() const
    {
        return cycleCount_;
    }

    std::size_t InstrExecRequirement::incrementCycleCount(std::size_t amount)
    {
        cycleCount_ += amount;
        return cycleCount_;
    }

    void InstrExecRequirement::resetCycleCount()
    {
        cycleCount_ = 0;
    }
}
