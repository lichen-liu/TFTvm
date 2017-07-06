#pragma once
#include "action.h"


/*
 * This abstract class is the interface for all actions that are executable on
 * the Actionable~TuringMachinePrototype.
 * This interface is a placeholder for now.
 *
 *  Action = 0
 *  |
 *  ExecutableAction = 0
 *
 */
namespace ACTION {
    class ExecutableAction :
        public Action
    {
    public:
        ExecutableAction() {}
        virtual ~ExecutableAction() {}
    };
}