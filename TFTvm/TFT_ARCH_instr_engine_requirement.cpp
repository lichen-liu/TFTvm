#include "TFT_ARCH_instr_engine_requirement.h"


namespace TFT_ARCH {
    std::size_t InstrEngineRequirement::getCycleCount() const
    {
        return cycleCount_;
    }

    std::size_t InstrEngineRequirement::incrementCycleCount(std::size_t amount)
    {
        cycleCount_ += amount;
        return cycleCount_;
    }

    void InstrEngineRequirement::resetCycleCount()
    {
        cycleCount_ = 0;
    }
}
