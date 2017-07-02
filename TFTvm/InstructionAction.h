#pragma once
#include "ExecutableAction.h"

#include "Engine.h"

/*
 * This abstract class is the interface for action performed by instructions on
 * the Virtual Machine (not implemented yet).
 *
 * template<typename InstructionExecutationStages> is an interface that defines the
 * instruction executation stages according to a spcific architecture.
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