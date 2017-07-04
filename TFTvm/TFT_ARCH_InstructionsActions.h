#pragma once
#include "InstructionAction.h"
#include "TFT_ARCH_InstrExecRequirement.h"


/*
* These sets of InstructionAction model the executation behaviour of instructions on
* the TFT Architecture.
*
* ACTION::InstructionAction<InstrExecRequirement> = 0
* |
* xxx_InstructionAction
*
*/
namespace TFT_ARCH {
    using TFT_ARCH_InstructionAction = ACTION::InstructionAction<InstrExecRequirement>;


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
