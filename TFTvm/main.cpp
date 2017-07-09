#include <iostream>
#include <limits>

#include "engine.h"
#include "TFT_ARCH_instr_exec_requirement.h"
#include "TURING_MACHINE.h"
#include "word_t.h"


int main(void)
{
    //constexpr std::size_t MEMORY_SIZE = 1024 * 1024 * 128; // 128 MiB
    //TURING_MACHINE::Engine<TFT_ARCH::InstrExecRequirement> engine(2, 8, 3, MEMORY_SIZE);

    //for (TURING_MACHINE::byte_t i = 0; i < 100; i++)
    //{
    //    engine.writeByte(i, i);
    //}

    //std::cout << "MEM[20]=" << (unsigned int)engine.readByte(20) << std::endl;
    //std::cout << "MEM[25]=" << (unsigned int)engine.readByte(25) << std::endl;
    //TURING_MACHINE::word_t word(sizeof(unsigned int));

    //std::cout << "0x123456789abcu=" << word.setValue(0x123456789abcu) << std::endl;
    //std::cout << "12345u=" << word.setValue(12345u) << std::endl;
    //std::cout << word.template getValue<unsigned int>() << std::endl;
    //TURING_MACHINE::word_t word(sizeof(int));
    //std::cout << "-12345=0x" << std::hex << -12345 << std::dec << std::endl;
    //std::cout << "word=" << word.setValue(-12345) << std::endl;
    //std::cout << word.template getValue<int>() << std::endl;

    TURING_MACHINE::word_t word(sizeof(unsigned int));
    word.setValue(0x00000000u);
    std::cout << "word=0x" << std::hex << word.template getValue<unsigned int>() << std::dec << std::endl;
    std::cout << "word=0d" << word.template getValue<unsigned int>() << std::endl;
    std::cout << word << std::endl;
    std::cout << std::endl;
    --word;
    std::cout << std::endl;
    std::cout << "word=0x" << std::hex << word.template getValue<unsigned int>() << std::dec << std::endl;
    std::cout << "word=0d" << word.template getValue<unsigned int>() << std::endl;
    std::cout << word << std::endl;



    /*std::cout << "-1=0x" << std::hex << -1 << std::dec << std::endl;
    std::cout << "-1u=0x" << std::hex << unsigned(-1) << std::dec << std::endl;*/

    // Pause the console
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return EXIT_SUCCESS;
}
