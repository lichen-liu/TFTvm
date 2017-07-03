#pragma once
#include "TFT_ARCH_InstructionExecutationStages.h"
#include "TuringMachine.h"


/*
*
* TURING_MACHINE::TuringMachine<InstructionExecutationStages> = 0
* |
* Machine
*
*/
namespace TFT_ARCH {
    class Machine : public TURING_MACHINE::TuringMachine<InstructionExecutationStages>
    {
    public:
        Machine();
        virtual ~Machine();
    };
}
