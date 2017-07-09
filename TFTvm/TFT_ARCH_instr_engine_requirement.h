#pragma once
#include "TURING_MACHINE.h"
#include "word_t.h"


/*
 * This abstract class is the interface for Instruction Engine Requirement.
 *
 * InstrEngineRequirement = 0
 *
 */
namespace TFT_ARCH {
    class InstrEngineRequirement
    {
    public:
        virtual ~InstrEngineRequirement() {}

        virtual TURING_MACHINE::word_t& publicRegisterContent(std::size_t pos) = 0;
        virtual const TURING_MACHINE::word_t& publicRegisterContent(std::size_t pos)const = 0;
        virtual TURING_MACHINE::word_t& privateRegisterContent(std::size_t pos) = 0;
        virtual const TURING_MACHINE::word_t& privateRegisterContent(std::size_t pos)const = 0;
        virtual const TURING_MACHINE::word_t& getPublicRegisterContent(std::size_t pos)const = 0;
        virtual const TURING_MACHINE::word_t& getPrivateRegisterContent(std::size_t pos)const = 0;
        virtual void setPublicRegisterContent(std::size_t pos, const TURING_MACHINE::word_t& regContent) = 0;
        virtual void setPrivateRegisterContent(std::size_t pos, const TURING_MACHINE::word_t& regContent) = 0;
        virtual std::size_t getMemorySizeInBytes()const = 0;
        virtual TURING_MACHINE::word_t readWord(std::size_t address,
            TURING_MACHINE::addressable_e addressable,
            TURING_MACHINE::endian_e endian)const = 0;
        virtual void writeWord(std::size_t address, const TURING_MACHINE::word_t& value,
            TURING_MACHINE::addressable_e addressable,
            TURING_MACHINE::endian_e endian) = 0;
    };
}
