#include "TFT_ARCH.h"
#include "TFT_ARCH_instructions_actions.h"

#include <cassert>
#include "TFT_ARCH_instr_engine_requirement.h"
#include "word_t.h"


namespace {
    using namespace TFT_ARCH;

    NOOP_InstructionAction s_noopInstructionAction;
}


namespace TFT_ARCH {

    TFT_ARCH_InstructionAction * TFT_ARCH_InstructionAction::createInstructionAction(const TURING_MACHINE::word_t& instructionWord)
    {
        std::size_t opcode = 0;
        std::size_t rx = 0;
        std::size_t ry = 0;

        if (decodeInstructionWord(instructionWord, opcode, rx, ry) == false) {
            assert(false);
            return nullptr; // invalid instructionWord
        }

        TFT_ARCH_InstructionAction *instructionAction = nullptr;
        switch (opcode) {
        case OPCODE_E::MV:
            instructionAction = new MV_InstructionAction(rx, ry);
            break;
        case OPCODE_E::MVI:
            instructionAction = new MVI_InstructionAction(rx);
            break;
        case OPCODE_E::ADD:
            instructionAction = new ADD_InstructionAction(rx, ry);
            break;
        case OPCODE_E::SUB:
            instructionAction = new SUB_InstructionAction(rx, ry);
            break;
        case OPCODE_E::LD:
            instructionAction = new LD_InstructionAction(rx, ry);
            break;
        case OPCODE_E::ST:
            instructionAction = new ST_InstructionAction(rx, ry);
            break;
        case OPCODE_E::MVNZ:
            instructionAction = new MVNZ_InstructionAction(rx, ry);
            break;
        default:
            assert(false); // invalid operand
            instructionAction = nullptr;
            break;
        }

        return instructionAction;
    }

    bool TFT_ARCH_InstructionAction::decodeInstructionWord(const TURING_MACHINE::word_t & instructionWord, std::size_t & iii, std::size_t & xxx, std::size_t & yyy)
    {
        std::size_t instruction = instructionWord.template getValue<std::size_t>();
        instruction >>= 7;

        yyy = instruction & 7; // 0b0 0000 0111
        xxx = (instruction & 56) >> 3; // 0b0 0011 1000
        iii = (instruction & 448) >> 6; // 0b1 1100 0000

        return true;
    }

    TFT_ARCH_InstructionAction & TFT_ARCH_InstructionAction::getNOOPInstructionAction()
    {
        return s_noopInstructionAction;
    }


    MV_InstructionAction::MV_InstructionAction(std::size_t rX, std::size_t rY) :
        TFT_ARCH_InstructionAction(rX, rY)
    {
    }

    MV_InstructionAction::~MV_InstructionAction()
    {
    }

    /*
     * MV: cycle3
     * rX<-[rY]
     */
    bool MV_InstructionAction::cycle3(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(1);

        engine.setPublicRegisterContent(rx, (engine.getPublicRegisterContent(ry)));

        return true;
    }


    MVI_InstructionAction::MVI_InstructionAction(std::size_t rX) :
        TFT_ARCH_InstructionAction(rX, PUBLIC_REG_E::NUM)
    {
    }

    MVI_InstructionAction::~MVI_InstructionAction()
    {
    }

    /*
     * MVI: cycle3
     * ADDR<-[PC]
     * [PC]++
     */
    bool MVI_InstructionAction::cycle3(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(1);

        engine.privateRegisterContent(PRIVATE_REG_E::ADDR) = engine.publicRegisterContent(PUBLIC_REG_E::PC);
        ++(engine.publicRegisterContent(PUBLIC_REG_E::PC));

        return true;
    }

    /*
     * MVI: cycle4
     * This stage is for memory access.
     */
    bool MVI_InstructionAction::cycle4(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(MEMORY_DELAY_IN_CYCLE + 1);

        return true;
    }

    /*
     * MVI: cycle5
     * rX<-MEM[[ADDR]]
     */
    bool MVI_InstructionAction::cycle5(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(1);

        std::size_t addr = (engine.privateRegisterContent(PRIVATE_REG_E::ADDR)).template getValue<std::size_t>();
        engine.publicRegisterContent(rx) = engine.readWord(addr, ADDRESSABLE, ENDIAN);

        return true;
    }


    ADD_InstructionAction::ADD_InstructionAction(std::size_t rX, std::size_t rY) :
        TFT_ARCH_InstructionAction(rX, rY)
    {
    }

    ADD_InstructionAction::~ADD_InstructionAction()
    {
    }

    /*
     * ADD: cycle3
     * A<-[rX]
     */
    bool ADD_InstructionAction::cycle3(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(1);

        engine.privateRegisterContent(PRIVATE_REG_E::A) = engine.publicRegisterContent(rx);

        return true;
    }

    /*
     * ADD: cycle4
     * G<-[A]+[rY]
     */
    bool ADD_InstructionAction::cycle4(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(1);

        engine.privateRegisterContent(PRIVATE_REG_E::G) =
            engine.privateRegisterContent(PRIVATE_REG_E::A) + engine.publicRegisterContent(ry);

        return true;
    }

    /*
     * ADD: cycle5
     * rX<-[G]
     */
    bool ADD_InstructionAction::cycle5(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(1);

        engine.publicRegisterContent(rx) = engine.privateRegisterContent(PRIVATE_REG_E::G);

        return true;
    }


    SUB_InstructionAction::SUB_InstructionAction(std::size_t rX, std::size_t rY) :
        TFT_ARCH_InstructionAction(rX, rY)
    {
    }

    SUB_InstructionAction::~SUB_InstructionAction()
    {
    }

    /*
     * SUB: cycle3
     * A<-[rX]
     */
    bool SUB_InstructionAction::cycle3(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(1);

        engine.privateRegisterContent(PRIVATE_REG_E::A) = engine.publicRegisterContent(rx);

        return true;
    }

    /*
     * SUB: cycle4
     * G<-[A]-[rY]
     */
    bool SUB_InstructionAction::cycle4(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(1);

        engine.privateRegisterContent(PRIVATE_REG_E::G) =
            engine.privateRegisterContent(PRIVATE_REG_E::A) - engine.publicRegisterContent(ry);

        return true;
    }

    /*
     * SUB: cycle5
     * rX<-[G]
     */
    bool SUB_InstructionAction::cycle5(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(1);

        engine.publicRegisterContent(rx) = engine.privateRegisterContent(PRIVATE_REG_E::G);

        return true;
    }


    LD_InstructionAction::LD_InstructionAction(std::size_t rX, std::size_t rY) :
        TFT_ARCH_InstructionAction(rX, rY)
    {
    }

    LD_InstructionAction::~LD_InstructionAction()
    {
    }

    /*
     * LD: cycle3
     * ADDR<-[rY]
     */
    bool LD_InstructionAction::cycle3(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(1);

        engine.privateRegisterContent(PRIVATE_REG_E::ADDR) = engine.publicRegisterContent(ry);

        return true;
    }

    /*
     * LD: cycle4
     * This stage is for memory access.
     */
    bool LD_InstructionAction::cycle4(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(MEMORY_DELAY_IN_CYCLE + 1);

        return true;
    }

    /*
     * LD: cycle5
     * rX<-MEM[[ADDR]]
     */
    bool LD_InstructionAction::cycle5(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(1);

        std::size_t addr = engine.privateRegisterContent(PRIVATE_REG_E::ADDR).template getValue<std::size_t>();
        engine.publicRegisterContent(rx) = engine.readWord(addr, ADDRESSABLE, ENDIAN);

        return true;
    }


    ST_InstructionAction::ST_InstructionAction(std::size_t rX, std::size_t rY) :
        TFT_ARCH_InstructionAction(rX, rY)
    {
    }

    ST_InstructionAction::~ST_InstructionAction()
    {
    }

    /*
     * ST: cycle3
     * ADDR<-[rY]
     */
    bool ST_InstructionAction::cycle3(InstrEngineRequirement &engine)
    {
        engine.incrementCycleCount(1);

        engine.privateRegisterContent(PRIVATE_REG_E::ADDR) = engine.publicRegisterContent(ry);

        return true;
    }

    /*
     * ST: cycle4
     * DOUT<-[rX]
     */
    bool ST_InstructionAction::cycle4(InstrEngineRequirement &engine)
    {
        engine.incrementCycleCount(1);

        engine.privateRegisterContent(PRIVATE_REG_E::DOUT) = engine.publicRegisterContent(rx);

        return true;
    }

    /*
     * ST: cycle5
     * This stage is for memory access.
     */
    bool ST_InstructionAction::cycle5(InstrEngineRequirement &engine)
    {
        engine.incrementCycleCount(MEMORY_DELAY_IN_CYCLE + 1);

        return true;
    }

    /*
     * ST: cycle6
     * MEM[[ADDR]]<-[DOUT]
     */
    bool ST_InstructionAction::cycle6(InstrEngineRequirement &engine)
    {
        engine.incrementCycleCount(1);

        std::size_t addr = engine.privateRegisterContent(PRIVATE_REG_E::ADDR).template getValue<std::size_t>();
        engine.writeWord(addr, engine.privateRegisterContent(PRIVATE_REG_E::DOUT), ADDRESSABLE, ENDIAN);

        return true;
    }


    MVNZ_InstructionAction::MVNZ_InstructionAction(std::size_t rX, std::size_t rY) :
        TFT_ARCH_InstructionAction(rX, rY)
    {
    }

    MVNZ_InstructionAction::~MVNZ_InstructionAction()
    {
    }

    /*
     * MVNZ: cycle3
     * if(G!=0)
     *     rX<-[rY]
     */
    bool MVNZ_InstructionAction::cycle3(InstrEngineRequirement & engine)
    {
        engine.incrementCycleCount(1);

        if (!(engine.privateRegisterContent(PRIVATE_REG_E::G).equalsZero())) {
            engine.publicRegisterContent(rx) = engine.publicRegisterContent(ry);
        }

        return true;
    }


    NOOP_InstructionAction::NOOP_InstructionAction() :
        TFT_ARCH_InstructionAction(0, 0)
    {
    }

    NOOP_InstructionAction::~NOOP_InstructionAction()
    {
    }
}