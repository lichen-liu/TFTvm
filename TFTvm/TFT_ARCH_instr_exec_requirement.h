#pragma once
#include "TFT_ARCH_instr_engine_requirement.h"
#include "TFT_ARCH_instr_stage_requirement.h"
#include "TURING_MACHINE.h"
#include "word_t.h"


/*
 * This abstract class defines the interface of architecture-specific
 * instruction execution requirement.
 * This interface is for by TuringMachinePrototype~Engine only.
 *
 * InstrEngineRequirement = 0      InstrStageRequirement<InstrStageRequirement<InstrEngineRequirement>> = 0
 * |                               |
 * InstrExecRequirement = 0 --------
 *
 */
namespace TFT_ARCH {

    class InstrExecRequirement :
        public InstrEngineRequirement, public InstrStageRequirement<InstrStageRequirement<InstrEngineRequirement>>
    {
    public:
        // Instruction execution stages
        virtual bool cycle0(InstrStageRequirement<InstrEngineRequirement>& instruction) override;
        virtual bool cycle1(InstrStageRequirement<InstrEngineRequirement>& instruction) override;
        virtual bool cycle2(InstrStageRequirement<InstrEngineRequirement>& instruction) override;
        // IR<-instructionWord after cycle2
        virtual bool cycle3(InstrStageRequirement<InstrEngineRequirement>& instruction) override;
        virtual bool cycle4(InstrStageRequirement<InstrEngineRequirement>& instruction) override;
        virtual bool cycle5(InstrStageRequirement<InstrEngineRequirement>& instruction) override;
        virtual bool cycle6(InstrStageRequirement<InstrEngineRequirement>& instruction) override;

        virtual ~InstrExecRequirement() {}
    };
}
