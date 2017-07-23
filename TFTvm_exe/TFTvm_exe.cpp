// TFTvm_exe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif


#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "engine.h"
#include "mif_parser.h"
#include "TFT_ARCH.h"
#include "TFT_ARCH_instr_exec_requirement.h"
#include "TFT_ARCH_machine.h"
#include "TURING_MACHINE.h"
#include "word_t.h"


namespace {
    void l_runTFTMachine();
    void l_testMIfParser();
}


int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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

    //TURING_MACHINE::word_t word(sizeof(unsigned int));
    //word.setValue(0x00000000u);
    //std::cout << "word=0x" << std::hex << word.template getValue<unsigned int>() << std::dec << std::endl;
    //std::cout << "word=0d" << word.template getValue<unsigned int>() << std::endl;
    //std::cout << word << std::endl;
    //std::cout << std::endl;
    //--word;
    //std::cout << std::endl;
    //std::cout << "word=0x" << std::hex << word.template getValue<unsigned int>() << std::dec << std::endl;
    //std::cout << "word=0d" << word.template getValue<unsigned int>() << std::endl;
    //std::cout << word << std::endl;


    //std::cout << "-1=0x" << std::hex << -1 << std::dec << std::endl;
    //std::cout << "-1u=0x" << std::hex << unsigned(-1) << std::dec << std::endl;

    l_testMIfParser();
    //l_runTFTMachine();


    // Pause the console
    std::cout << std::endl << std::endl;
    std::cout << "*****************************" << std::endl;
    std::cout << "*...Press <ENTER> to Exit...*" << std::endl;
    std::cout << "*****************************" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    return EXIT_SUCCESS;
}


namespace {
    void l_runTFTMachine()
    {
        constexpr std::size_t PROGRAM_SIZE = 3;

        TFT_ARCH::Machine machine(PROGRAM_SIZE * TFT_ARCH::WORD_SIZE);
        std::vector<TURING_MACHINE::word_t> program(PROGRAM_SIZE, TURING_MACHINE::word_t(TFT_ARCH::WORD_SIZE));
        program[0].setValue(0x2800u); // mvi r2, 0xdead
        program[1].setValue(0xdeadu);
        program[2].setValue(0x4500u); // add r1, r2
        machine.load(program, 0, TFT_ARCH::ADDRESSABLE, TFT_ARCH::ENDIAN);
        machine.run(0);
    }

    void l_testMIfParser()
    {
        std::vector<std::string> mif;
        std::string line;

        std::cout << "Enter the MIF content, enter <EXIT> to complete." << std::endl;
        while (true) {
            std::getline(std::cin, line);
            if (line == "EXIT") {
                break;
            }
            mif.push_back(std::move(line));
        }

        PARSER::MIFParser mifp;
        mifp.load(mif);
    }
}