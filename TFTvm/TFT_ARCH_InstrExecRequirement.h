#pragma once


/*
 * This abstract class defines the interface of architecture-specific instruction executation requirement
 * for TFT Architecture.
 *
 * InstrExecRequirement
 *
 */
namespace TFT_ARCH {
    class InstrExecRequirement
    {
    public:
        virtual bool cycle0(InstrExecRequirement& engine) { engine; return true; }
        virtual bool cycle1(InstrExecRequirement& engine) { engine; return true; }
        virtual bool cycle2(InstrExecRequirement& engine) { engine; return true; }
        virtual bool cycle3(InstrExecRequirement& engine) { engine; return true; }
        virtual bool cycle4(InstrExecRequirement& engine) { engine; return true; }
        virtual bool cycle5(InstrExecRequirement& engine) { engine; return true; }
        virtual bool cycle6(InstrExecRequirement& engine) { engine; return true; }
    };
}
