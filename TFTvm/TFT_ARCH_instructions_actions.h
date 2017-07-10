#pragma once
#include "instruction_action.h"
#include "TFT_ARCH_instr_stage_requirement.h"
#include "word_t.h"


/*
* These sets of InstructionAction model the executation behaviour of instructions on
* the TFT Architecture.
*
* ACTION::InstructionAction<InstrStageRequirement<InstrEngineRequirement>> = 0
* |
* TFT_ARCH_InstructionAction = 0
* |
* xx_InstructionAction
*
*/
namespace TFT_ARCH {
    class InstrEngineRequirement; // forward declaration

    /* This abstract class is the base for all InstructionAction used on TFT Architecture. */
    class TFT_ARCH_InstructionAction :
        public ACTION::InstructionAction<InstrStageRequirement<InstrEngineRequirement>>
    {
    public:
        /*
         * Factory method to create the xxx_instructionAction instance.
         * The argument word_t is the instruction word.
         * This method dynamically create the corresponding InstructionAction object on heap(operator new) and returns
         * the pointer to it.
         * Return nullptr if the instruction is not valid.
         */
        static TFT_ARCH_InstructionAction* createInstructionAction(const TURING_MACHINE::word_t& instructionWord);

        /*
         * Decode the instructionWord.
         * Return false if the instructionWord is not valid.
         */
        static bool decodeInstructionWord(const TURING_MACHINE::word_t& instructionWord, std::size_t& iii, std::size_t& xxx, std::size_t& yyy);

        /*
         * Returns a NOOP_InstructionAction that performs nothing.
         */
        static TFT_ARCH_InstructionAction& getNOOPInstructionAction();


        virtual ~TFT_ARCH_InstructionAction() {}


        /*
         * Defines the default behaviour of the InstrStageRequirement interface.
         */
        virtual bool cycle0(InstrEngineRequirement& engine) override {
            engine;/*Unused Reference*/
            return true;
        }
        virtual bool cycle1(InstrEngineRequirement& engine) override {
            engine;/*Unused Reference*/
            return true;
        }
        virtual bool cycle2(InstrEngineRequirement& engine) override {
            engine;/*Unused Reference*/
            return true;
        }
        virtual bool cycle3(InstrEngineRequirement& engine) override {
            engine;/*Unused Reference*/
            return true;
        }
        virtual bool cycle4(InstrEngineRequirement& engine) override {
            engine;/*Unused Reference*/
            return true;
        }
        virtual bool cycle5(InstrEngineRequirement& engine) override {
            engine;/*Unused Reference*/
            return true;
        }
        virtual bool cycle6(InstrEngineRequirement& engine) override {
            engine;/*Unused Reference*/
            return true;
        }

    protected:
        /*
         * This base abstract class cannot be instantiated.
         */
        TFT_ARCH_InstructionAction() :TFT_ARCH_InstructionAction(0, 0) {}
        TFT_ARCH_InstructionAction(std::size_t rX, std::size_t rY) :rx(rX), ry(rY) {}

        std::size_t rx;
        std::size_t ry;
    };


    class MV_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        MV_InstructionAction(std::size_t rX, std::size_t rY);
        virtual ~MV_InstructionAction();

        virtual bool cycle3(InstrEngineRequirement& engine)override;
    };


    class MVI_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        MVI_InstructionAction(std::size_t rX);
        virtual ~MVI_InstructionAction();

        virtual bool cycle3(InstrEngineRequirement& engine)override;
        virtual bool cycle4(InstrEngineRequirement& engine)override;
        virtual bool cycle5(InstrEngineRequirement& engine)override;
    };


    class ADD_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        ADD_InstructionAction(std::size_t rX, std::size_t rY);
        virtual ~ADD_InstructionAction();

        virtual bool cycle3(InstrEngineRequirement& engine)override;
        virtual bool cycle4(InstrEngineRequirement& engine)override;
        virtual bool cycle5(InstrEngineRequirement& engine)override;
    };


    class SUB_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        SUB_InstructionAction(std::size_t rX, std::size_t rY);
        virtual ~SUB_InstructionAction();

        virtual bool cycle3(InstrEngineRequirement& engine)override;
        virtual bool cycle4(InstrEngineRequirement& engine)override;
        virtual bool cycle5(InstrEngineRequirement& engine)override;
    };


    class LD_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        LD_InstructionAction(std::size_t rX, std::size_t rY);
        virtual ~LD_InstructionAction();

        virtual bool cycle3(InstrEngineRequirement& engine)override;
        virtual bool cycle4(InstrEngineRequirement& engine)override;
        virtual bool cycle5(InstrEngineRequirement& engine)override;
    };


    class ST_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        ST_InstructionAction(std::size_t rX, std::size_t rY);
        virtual ~ST_InstructionAction();

        virtual bool cycle3(InstrEngineRequirement& engine)override;
        virtual bool cycle4(InstrEngineRequirement& engine)override;
        virtual bool cycle5(InstrEngineRequirement& engine)override;
        virtual bool cycle6(InstrEngineRequirement& engine)override;
    };


    class MVNZ_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        MVNZ_InstructionAction(std::size_t rX, std::size_t rY);
        virtual ~MVNZ_InstructionAction();

        virtual bool cycle3(InstrEngineRequirement& engine)override;
    };


    class NOOP_InstructionAction :
        public TFT_ARCH_InstructionAction
    {
    public:
        NOOP_InstructionAction();
        virtual ~NOOP_InstructionAction();
    };
}
