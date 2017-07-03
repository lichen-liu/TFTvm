#pragma once
#include "Engine.h"


/*
 * This abstract class defines the interface of architecture-specific instruction executation stages
 * for TFT Architecture.
 *
 * InstructionExecutationStages = 0
 *
 */
namespace TFT_ARCH {
    class InstructionExecutationStages
    {
    public:
        virtual bool cycle0(TURING_MACHINE::Engine& engine) const = 0;
        virtual bool cycle1(TURING_MACHINE::Engine& engine) const = 0;
        virtual bool cycle2(TURING_MACHINE::Engine& engine) const = 0;
        virtual bool cycle3(TURING_MACHINE::Engine& engine) const = 0;
        virtual bool cycle4(TURING_MACHINE::Engine& engine) const = 0;
        virtual bool cycle5(TURING_MACHINE::Engine& engine) const = 0;
        virtual bool cycle6(TURING_MACHINE::Engine& engine) const = 0;
    };
}
