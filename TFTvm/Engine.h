#pragma once


/*
 * This class provides the basic atomic behaviours of the virtual machine system.
 * Since this Engine needs to be generic enough to be able to adapt to a variety of architectures,
 * it is deigned to only supports a minimal sets of architecture-independent atomic operations.
 */
namespace MACHINE {
    class Engine
    {
    public:
        Engine() {}

        virtual ~Engine() {}
    };
}
