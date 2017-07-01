#pragma once


/*
 * This class provides the basic atomic behaviours of the virtual machine system.
 *
 * template <typename WORD> is the bit of the architecture. Perferably using uintxx_t types.
 */
namespace MACHINE {
    template <typename WORD>
    class Engine
    {
    public:
        Engine() {}

        virtual ~Engine() {}
    };
}
