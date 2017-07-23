#pragma once
#include <string>
#include <vector>

#include "PARSER.h"


namespace PARSER {
    class MIFParser
    {
    public:
        MIFParser();
        virtual ~MIFParser();

        bool load(const std::vector<std::string>& mifRaw);
        bool load(const std::string& mifFile);


        struct  MIFProperty {
            std::size_t depth;
            std::size_t width;
            radix_e address_radix;
            radix_e data_radix;
        };


        static std::vector<std::string> processComment(const std::vector<std::string>& in);
        static std::vector<std::string> processFormat(const std::vector<std::string>& in);
        static MIFProperty parseProperty(const std::vector<std::string>& in);
    };
}
