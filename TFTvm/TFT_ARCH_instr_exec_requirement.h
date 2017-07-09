#pragma once
#include "TURING_MACHINE.h"
#include "word_t.h"


/*
 * This non-abstract class defines the interface of architecture-specific
 * instruction executation requirement.
 * The default definition in this class is for compatibility only.
 * Both Engine and InstructionAction instances should implement their own definitions.
 *
 * InstrExecRequirement
 *
 */
namespace TFT_ARCH {
    class InstrExecRequirement
    {
    public:
        // Instruction executation stages
        virtual bool cycle0(InstrExecRequirement&);
        virtual bool cycle1(InstrExecRequirement&);
        virtual bool cycle2(InstrExecRequirement&);
        virtual bool cycle3(InstrExecRequirement&);
        virtual bool cycle4(InstrExecRequirement&);
        virtual bool cycle5(InstrExecRequirement&);
        virtual bool cycle6(InstrExecRequirement&);

        // Instruction hardware requirement
        virtual TURING_MACHINE::word_t& publicRegisterContent(std::size_t pos);
        virtual const TURING_MACHINE::word_t& publicRegisterContent(std::size_t pos)const;
        virtual TURING_MACHINE::word_t& privateRegisterContent(std::size_t pos);
        virtual const TURING_MACHINE::word_t& privateRegisterContent(std::size_t pos)const;
        virtual const TURING_MACHINE::word_t& getPublicRegisterContent(std::size_t pos)const;
        virtual const TURING_MACHINE::word_t& getPrivateRegisterContent(std::size_t pos)const;
        virtual void setPublicRegisterContent(std::size_t pos, const TURING_MACHINE::word_t& regContent);
        virtual void setPrivateRegisterContent(std::size_t pos, const TURING_MACHINE::word_t& regContent);
        virtual std::size_t getMemorySizeInBytes()const;
        virtual TURING_MACHINE::word_t readWord(std::size_t address,
            TURING_MACHINE::addressable_e addressable,
            TURING_MACHINE::endian_e endian)const;
        virtual void writeWord(std::size_t address, const TURING_MACHINE::word_t& value,
            TURING_MACHINE::addressable_e addressable,
            TURING_MACHINE::endian_e endian);

        // Count the cycle
        std::size_t getCycleCount()const;
        std::size_t incrementCycleCount(std::size_t amount = 1);
        void resetCycleCount();


        virtual ~InstrExecRequirement() {}

    protected:
        // This class can not be instantiated by itself
        InstrExecRequirement() :cycleCount_(0) {}

    private:
        std::size_t cycleCount_; // use size_t for now
    };
}
