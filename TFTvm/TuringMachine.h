#pragma once
#include <cassert>
#include <memory>
#include <vector>

#include "TURING_MACHINE.h"
#include "Engine.h"


/*
 *
 * template <typename InstrExecRequirement> is the interface that defines the required methods
 * provided by the engine used by this machine.
 *
 * TuringMachine<InstrExecRequirement> = 0
 *
 * DONE
 */
namespace TURING_MACHINE {

    template<typename  InstrExecRequirement>
    class TuringMachine
    {
    public:
        // Finalized interface to access this Turing Machine
        virtual void reset() final
        {
            resetImplementation(*m_engine);
        }

        virtual bool load(const std::vector<byte_t>& program, std::size_t startingByteAddress = 0) final
        {
            return loadImplementation(*m_engine, program, startingByteAddress);
        }

        /* This function is the entry to run this Turing Machine.
         * startingByteAddress is a hint to the program counter.
         * runImplementation() must be implemented by derived class.
         */
        virtual void run(std::size_t startingByteAddress = 0) final
        {
            runImplementation(*m_engine, startingByteAddress);
        }

    protected:
        TuringMachine(
            std::size_t wordSizeInBytes = 2,
            std::size_t numPublicRegisters = 8,
            std::size_t numPrivateRegisters = 3,
            std::size_t memorySizeInBytes = 0) :
            m_engine(new Engine<InstrExecRequirement>(wordSizeInBytes, numPublicRegisters, numPrivateRegisters, memorySizeInBytes)) {}

        // The argument engine must be dynamically allocated, its ownership is then transferred to this object
        TuringMachine(Engine<InstrExecRequirement>* engine) :
            m_engine(engine) {}

        virtual ~TuringMachine() {}

    private:
        std::unique_ptr<Engine<InstrExecRequirement>> m_engine;

        // Implmentations of the finalized interface, overridable
        virtual void resetImplementation(Engine<InstrExecRequirement>& engine)
        {
            engine.resetRegisters();
        }

        virtual bool loadImplementation(Engine<InstrExecRequirement>& engine, const std::vector<byte_t>& program, std::size_t startingByteAddress)
        {
            std::size_t memorySize = engine.getMemorySizeInBytes();
            // startingByteAddress should not exceed the memory size
            assert(startingByteAddress < memorySize);

            for (std::size_t i = startingByteAddress; i < memorySize; i++)
            {
                engine.writeByte(i, program[i - startingByteAddress]);
            }

            // Return true if the program is loaded into memory successfully
            // Return false if the program cannot be fully loaded into the memory
            return (memorySize >= (program.size() + startingByteAddress));
        }

        /* This function is the implementation of run(), and must be implemented by the derived.
        * startingByteAddress is a hint to the program counter.
        * It is up to the implementor to decide how to deal with this parameter.
        */
        virtual void runImplementation(Engine<InstrExecRequirement>& engine, std::size_t startingByteAddress) = 0;
    };
}
