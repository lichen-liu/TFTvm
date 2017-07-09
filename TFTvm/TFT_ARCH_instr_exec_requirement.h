#pragma once
#include "TFT_ARCH_instr_engine_requirement.h"
#include "TFT_ARCH_instr_stage_requirement.h"
#include "TURING_MACHINE.h"
#include "word_t.h"


/*
 * This abstract class defines the interface of architecture-specific
 * instruction executation requirement.
 * This interface is for Engine only.
 *
 * InstrEngineRequirement = 0      InstrStageRequirement<InstrStageRequirement<InstrExecRequirement>> = 0
 * |                               |
 * InstrExecRequirement = 0 --------
 *
 */
namespace TFT_ARCH {

    class InstrExecRequirement :
        public InstrEngineRequirement, public InstrStageRequirement<InstrStageRequirement<InstrExecRequirement>>
    {
    public:
        // Instruction executation stages
        virtual bool cycle0(InstrStageRequirement<InstrExecRequirement>& instruction) override;
        virtual bool cycle1(InstrStageRequirement<InstrExecRequirement>& instruction) override;
        virtual bool cycle2(InstrStageRequirement<InstrExecRequirement>& instruction) override;
        virtual bool cycle3(InstrStageRequirement<InstrExecRequirement>& instruction) override;
        virtual bool cycle4(InstrStageRequirement<InstrExecRequirement>& instruction) override;
        virtual bool cycle5(InstrStageRequirement<InstrExecRequirement>& instruction) override;
        virtual bool cycle6(InstrStageRequirement<InstrExecRequirement>& instruction) override;

        // Count the cycle
        std::size_t getCycleCount()const;
        std::size_t incrementCycleCount(std::size_t amount = 1);
        void resetCycleCount();


        virtual ~InstrExecRequirement() {}

    protected:
        // This class can not be instantiated by itself
        InstrExecRequirement() :cycleCount_(0) {}

    private:
        std::size_t cycleCount_; // use size_t for now
    };
}
