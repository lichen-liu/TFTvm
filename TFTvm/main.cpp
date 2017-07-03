#include <iostream>

#include "TURING_MACHINE.h"
#include "Engine.h"


int main(void)
{
    TURING_MACHINE::Engine engine(2, 8, 3, 1024 * 1024);

    for (TURING_MACHINE::byte_t i = 0; i < 100; i++)
    {
        engine.writeByte(i, i);
    }

    std::cout << "MEM[20]=" << (unsigned int)engine.readByte(20) << std::endl;
    std::cout << "MEM[25]=" << (unsigned int)engine.readByte(25) << std::endl;

    return EXIT_SUCCESS;
}
