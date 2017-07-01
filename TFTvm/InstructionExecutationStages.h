#pragma once
#include "Engine.h"
#include "TFT_ARCH.h"


/*
 * This abstract class defines the architecture-specific instruction executation stages
 * for TFT Architecture.
 */
namespace TFT_ARCH {
    class InstructionExecutationStages
    {
    public:
        InstructionExecutationStages() = default;
        virtual ~InstructionExecutationStages() = 0;

        virtual bool cycle0(MACHINE::Engine<word_t>& engine) const = 0;
        virtual bool cycle1(MACHINE::Engine<word_t>& engine) const = 0;
        virtual bool cycle2(MACHINE::Engine<word_t>& engine) const = 0;
        virtual bool cycle3(MACHINE::Engine<word_t>& engine) const = 0;
        virtual bool cycle4(MACHINE::Engine<word_t>& engine) const = 0;
        virtual bool cycle5(MACHINE::Engine<word_t>& engine) const = 0;
        virtual bool cycle6(MACHINE::Engine<word_t>& engine) const = 0;
    };
}
