#pragma once
#include "TURING_MACHINE.h"

#include <cassert>
#include <memory>
#include <vector>

#include "Engine.h"


/*
 *
 * template <typename EngineRequirement> is the interface that defines the required methods
 * provided by the engine used by this machine.
 *
 * TuringMachine<typename EngineRequirement> = 0
 *
 * DONE
 */
namespace TURING_MACHINE {

    template<typename  EngineRequirement>
    class TuringMachinePrototype
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

        virtual bool load(const std::vector<word_t>& program, std::size_t startingAddress = 0, addressable_e addressable = addressable_e::word,
            endian_e endian = endian_e::little)final {
            return loadImplementation(*m_engine, program, startingAddress, addressable, endian);
        }

        /* This function is the entry to run this Turing Machine.
         * startingAddress is a hint to the program counter.
         * runImplementation() must be implemented by derived class.
         */
        virtual bool run(std::size_t startingAddress = 0) final
        {
            return runImplementation(*m_engine, startingAddress);
        }

    protected:
        TuringMachinePrototype(
            std::size_t wordSizeInBytes = 2,
            std::size_t numPublicRegisters = 8,
            std::size_t numPrivateRegisters = 3,
            std::size_t memorySizeInBytes = 0) :
            m_engine(new Engine<EngineRequirement>(wordSizeInBytes, numPublicRegisters, numPrivateRegisters, memorySizeInBytes)) {}

        // The argument engine must be dynamically allocated, its ownership is then transferred to this object
        TuringMachinePrototype(Engine<EngineRequirement>* engine) :
            m_engine(engine) {}

        /*
         * This class cannot be used as referenced type or pointer type.
         */
        virtual ~TuringMachinePrototype() {}

    private:
        std::unique_ptr<Engine<EngineRequirement>> m_engine;

        // Implmentations of the finalized interface, overridable
        virtual void resetImplementation(Engine<EngineRequirement>& engine)
        {
            engine.resetRegisters();
        }

        virtual bool loadImplementation(Engine<EngineRequirement>& engine, const std::vector<byte_t>& program, std::size_t startingByteAddress)
        {
            std::size_t memorySize = engine.getMemorySizeInBytes();
            // startingByteAddress should not exceed the memory size
            assert(startingByteAddress < memorySize);

            for (std::size_t i = 0; i < program.size(); i++)
            {
                if ((i + startingByteAddress) >= memorySize)
                    break;
                engine.writeByte(i + startingByteAddress, program[i]);
            }

            // Return true if the program is loaded into memory successfully
            // Return false if the program cannot be fully loaded into the memory
            return (memorySize >= (program.size() + startingByteAddress));
        }

        virtual bool loadImplementation(Engine<EngineRequirement>& engine, const std::vector<word_t>& program, std::size_t startingAddress,
            addressable_e addressable, endian_e endian) {

            // convert to startingByteAddress
            std::size_t memorySize = engine.getMemorySizeInBytes();
            std::size_t startingByteAddress = 0;
            std::size_t wordSize = engine.getWordSizeInBytes();
            switch (addressable) {
            case addressable_e::byte:
                startingByteAddress = startingAddress;
                break;
            case addressable_e::word:
                startingByteAddress = startingAddress*wordSize;
                break;
            default:
                assert(false);
                break;
            }
            // startingByteAddress should not exceed the memory size
            assert(startingByteAddress < memorySize);

            for (std::size_t i = 0; i < program.size(); i++) {
                if ((i*wordSize + startingByteAddress) >= memorySize)
                    break;
                engine.writeWord(startingByteAddress + i*wordSize, program[i], addressable_e::byte, endian);
            }

            // Return true if the program is loaded into memory successfully
            // Return false if the program cannot be fully loaded into the memory
            return (memorySize >= (program.size()*wordSize + startingByteAddress));
        }

        /* This function is the implementation of run(), and must be implemented by the derived class.
         * startingAddress is a hint to the program counter.
         * It is up to the implementor to decide how to deal with this parameter.
         */
        virtual bool runImplementation(Engine<EngineRequirement>& engine, std::size_t startingAddress) = 0;
    };
}
