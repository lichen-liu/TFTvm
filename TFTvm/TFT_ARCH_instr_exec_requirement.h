#pragma once
#include "TURING_MACHINE.h"
#include "word_t.h"


/*
 * This class defines the non-abstract interface of architecture-specific instruction executation requirement
 * for TFT Architecture.
 *
 * InstrExecRequirement
 *
 */
namespace TFT_ARCH {
    class InstrExecRequirement
    {
    public:
        // Instruction executation stages
        virtual bool cycle0(InstrExecRequirement& engine) { engine; return true; }
        virtual bool cycle1(InstrExecRequirement& engine) { engine; return true; }
        virtual bool cycle2(InstrExecRequirement& engine) { engine; return true; }
        virtual bool cycle3(InstrExecRequirement& engine) { engine; return true; }
        virtual bool cycle4(InstrExecRequirement& engine) { engine; return true; }
        virtual bool cycle5(InstrExecRequirement& engine) { engine; return true; }
        virtual bool cycle6(InstrExecRequirement& engine) { engine; return true; }

        // Instruction hardware requirement
        virtual TURING_MACHINE::word_t getPublicRegisterContent(std::size_t idx)const { idx; return TURING_MACHINE::word_t(); }
        virtual TURING_MACHINE::word_t getPrivateRegisterContent(std::size_t idx)const { idx; return TURING_MACHINE::word_t(); }
        virtual void setPublicRegisterContent(std::size_t idx, const TURING_MACHINE::word_t& regContent) { idx; regContent; }
        virtual void setPrivateRegisterContent(std::size_t idx, const TURING_MACHINE::word_t& regContent) { idx; regContent; }
        virtual std::size_t getMemorySizeInBytes()const { return 0; }
        virtual TURING_MACHINE::word_t readWord(std::size_t address,
            TURING_MACHINE::addressable_e addressable,
            TURING_MACHINE::endian_e endian)const
        {
            address;
            addressable;
            endian;
            return TURING_MACHINE::word_t();
        }
        virtual void writeWord(std::size_t address, const TURING_MACHINE::word_t& value,
            TURING_MACHINE::addressable_e addressable,
            TURING_MACHINE::endian_e endian)
        {
            address;
            value;
            addressable;
            endian;
        }
    };
}
