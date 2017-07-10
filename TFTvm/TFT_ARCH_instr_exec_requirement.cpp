#include "TFT_ARCH.h"
#include "TFT_ARCH_instr_exec_requirement.h"

#include "TFT_ARCH_instr_engine_requirement.h"
#include "TFT_ARCH_instr_stage_requirement.h"


/*
 * The implementation of cycles are for Engine only.
 * The implementation of hardware requirements are for InstructionAction only.
 */
namespace TFT_ARCH {

    /*
     * cycle0 is the same for all instructions.
     * ADDR<-[PC]
     */
    bool InstrExecRequirement::cycle0(InstrStageRequirement<InstrEngineRequirement> & instruction)
    {
        instruction;/*Unused Reference*/
        incrementCycleCount(1);

        setPrivateRegisterContent(PRIVATE_REG_E::ADDR, publicRegisterContent(PUBLIC_REG_E::PC));

        return true;
    }

    /*
     * cycle1 is the same for all instructions.
     * This stage is for memory access.
     */
    bool InstrExecRequirement::cycle1(InstrStageRequirement<InstrEngineRequirement> & instruction)
    {
        instruction;/*Unused Reference*/
        incrementCycleCount(MEMORY_DELAY_IN_CYCLE + 1);

        return true;
    }

    /*
     * cycle2 is the same for all instructions.
     * [PC]++
     * IR<-MEM[[ADDR]]
     */
    bool InstrExecRequirement::cycle2(InstrStageRequirement<InstrEngineRequirement> & instruction)
    {
        instruction;/*Unused Reference*/
        incrementCycleCount(1);

        ++publicRegisterContent(PUBLIC_REG_E::PC);
        std::size_t addr = getPrivateRegisterContent(PRIVATE_REG_E::ADDR).template getValue<std::size_t>();

        if ((addr*getWordSizeInBytes()) >= getMemorySizeInBytes()) { // PC holds address greater than the memory size
            return false;
        }

        setPrivateRegisterContent(PRIVATE_REG_E::IR, readWord(addr, ADDRESSABLE, ENDIAN));

        return true;
    }

    /*
     * cycle3 is instruction-dependent.
     */
    bool InstrExecRequirement::cycle3(InstrStageRequirement<InstrEngineRequirement> & instruction)
    {
        return instruction.cycle3(*this); // pass this engine instance to instruction
    }

    /*
     * cycle4 is instruction-dependent.
     */
    bool InstrExecRequirement::cycle4(InstrStageRequirement<InstrEngineRequirement> & instruction)
    {
        return instruction.cycle4(*this); // pass this engine instance to instruction
    }

    /*
     * cycle5 is instruction-dependent.
     */
    bool InstrExecRequirement::cycle5(InstrStageRequirement<InstrEngineRequirement> & instruction)
    {
        return instruction.cycle5(*this); // pass this engine instance to instruction
    }

    /*
     * cycle6 is instruction-dependent.
     */
    bool InstrExecRequirement::cycle6(InstrStageRequirement<InstrEngineRequirement> & instruction)
    {
        return instruction.cycle6(*this); // pass this engine instance to instruction
    }
}
