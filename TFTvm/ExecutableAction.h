#pragma once
#include "Action.h"


/*
 * This abstract class is the interface for all actions that are executable on
 * the Virtual Machine (not implemented yet).
 * This interface is a placeholder for now.
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