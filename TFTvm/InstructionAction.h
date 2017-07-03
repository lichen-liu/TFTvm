#pragma once
#include "ExecutableAction.h"

#include "Engine.h"

/*
 * This abstract class is the interface for action performed by instructions on
 * the Actionable~TuringMachine.
 *
 * template<typename InstructionExecutationStages> is an interface that defines the
 * instruction executation stages according to a spcific architecture.
 *
 *  Action = 0
 *  |
 *  ExecutableAction = 0                                   <InstructionExecutationStages> => 0
 *  |                                                      |
 *  InstructionAction<InstructionExecutationStages> = 0 ----
 *
 */
namespace ACTION {
    template<typename InstructionExecutationStages>
    class InstructionAction :
        public ExecutableAction, public InstructionExecutationStages
    {
    public:
        InstructionAction() {}
        virtual ~InstructionAction() {}

        /*
         * Architecture-specific instruction executation stages
         * declared in template<typename InstructionExecutationStages>
         */
    };
}