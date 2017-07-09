#pragma once
#include "executable_action.h"


/*
 * This abstract class is the interface for action performed by instructions on
 * the Actionable~TuringMachinePrototype.
 *
 * template<typename StageRequirement> is an interface that defines the
 * instruction executation requirement according to a spcific architecture.
 *
 *  Action = 0
 *  |
 *  ExecutableAction = 0                                <StageRequirement>
 *  |                                                   |
 *  InstructionAction<typename StageRequirement> = 0 ----
 *
 */
namespace ACTION {
    template<typename StageRequirement>
    class InstructionAction :
        public ExecutableAction, public StageRequirement
    {
    public:
        virtual ~InstructionAction() {}

        /*
         * Architecture-specific instruction executation requirement
         * declared in template<typename StageRequirement>
         */

    protected:
        InstructionAction() {}
    };
}