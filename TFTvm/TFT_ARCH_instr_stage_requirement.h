#pragma once


/*
 * This abstract class is the interface for Instruction Stage Requirement.
 * The template <typename Target> is the interface that is either an Action or Actionable.
 *
 * InstrStageRequirement<typename Target> = 0
 *
 */
namespace TFT_ARCH {

    template <typename Target>
    class InstrStageRequirement
    {
    public:
        virtual ~InstrStageRequirement() {}

        virtual bool cycle0(Target&) = 0;
        virtual bool cycle1(Target&) = 0;
        virtual bool cycle2(Target&) = 0;
        virtual bool cycle3(Target&) = 0;
        virtual bool cycle4(Target&) = 0;
        virtual bool cycle5(Target&) = 0;
        virtual bool cycle6(Target&) = 0;
    };
}
