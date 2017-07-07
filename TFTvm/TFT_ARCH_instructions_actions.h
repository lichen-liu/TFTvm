#pragma once
#include "TFT_ARCH.h"

#include "instruction_action.h"
#include "TFT_ARCH_instr_exec_requirement.h"


/*
* These sets of InstructionAction model the executation behaviour of instructions on
* the TFT Architecture.
*
* ACTION::InstructionAction<InstrExecRequirement> = 0
* |
* TFT_ARCH_InstructionAction = 0
* |
* xx_InstructionAction
*
*/
namespace TFT_ARCH {
    /* This abstract class is the base for all InstructionAction used on TFT Architecture. */
    class TFT_ARCH_InstructionAction :
        public ACTION::InstructionAction<InstrExecRequirement>
    {
    public:
        TFT_ARCH_InstructionAction() :TFT_ARCH_InstructionAction(0, 0) {}
        TFT_ARCH_InstructionAction(std::size_t rX, std::size_t rY) :rx(rX), ry(rY) {}
        virtual ~TFT_ARCH_InstructionAction() {}

    protected:
        std::size_t rx;
        std::size_t ry;
    };


    class MV_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        MV_InstructionAction();
        virtual ~MV_InstructionAction();
    };


    class MVI_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        MVI_InstructionAction();
        virtual ~MVI_InstructionAction();
    };


    class ADD_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        ADD_InstructionAction();
        virtual ~ADD_InstructionAction();
    };


    class SUB_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        SUB_InstructionAction();
        virtual ~SUB_InstructionAction();
    };


    class LD_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        LD_InstructionAction();
        virtual ~LD_InstructionAction();
    };


    class ST_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        ST_InstructionAction();
        virtual ~ST_InstructionAction();
    };


    class MVNZ_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        MVNZ_InstructionAction();
        virtual ~MVNZ_InstructionAction();
    };
}
