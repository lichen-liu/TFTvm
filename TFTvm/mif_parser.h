#pragma once
#include <string>


namespace DRIVER {
    class MIFParser
    {
    public:
        MIFParser();
        virtual ~MIFParser();

        bool load(const std::string& mifFile);
    };
}
