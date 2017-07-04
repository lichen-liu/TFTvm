#pragma once
#include "ExecutableAction.h"

#include "Engine.h"

/*
 * This abstract class is the interface for action performed by instructions on
 * the Actionable~TuringMachine.
 *
 * template<typename InstrExecRequirement> is an interface that defines the
 * instruction executation requirement according to a spcific architecture.
 *
 *  Action = 0
 *  |
 *  ExecutableAction = 0                            <InstrExecRequirement>
 *  |                                               |
 *  InstructionAction<InstrExecRequirement> = 0 ----
 *
 */
namespace ACTION {
    template<typename InstrExecRequirement>
    class InstructionAction :
        public ExecutableAction, public InstrExecRequirement
    {
    public:
        InstructionAction() {}
        virtual ~InstructionAction() {}

        /*
         * Architecture-specific instruction executation requirement
         * declared in template<typename InstrExecRequirement>
         */
    };
}