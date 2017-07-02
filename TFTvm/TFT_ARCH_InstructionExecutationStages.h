#pragma once
#include "Engine.h"


/*
 * This abstract class defines the interface of architecture-specific instruction executation stages
 * for TFT Architecture.
 */
namespace TFT_ARCH {
    class InstructionExecutationStages
    {
    public:
        InstructionExecutationStages() {}
        virtual ~InstructionExecutationStages() {}

        virtual bool cycle0(MACHINE::Engine& engine) const = 0;
        virtual bool cycle1(MACHINE::Engine& engine) const = 0;
        virtual bool cycle2(MACHINE::Engine& engine) const = 0;
        virtual bool cycle3(MACHINE::Engine& engine) const = 0;
        virtual bool cycle4(MACHINE::Engine& engine) const = 0;
        virtual bool cycle5(MACHINE::Engine& engine) const = 0;
        virtual bool cycle6(MACHINE::Engine& engine) const = 0;
    };
}
