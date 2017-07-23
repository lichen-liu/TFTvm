#pragma once
#include <string>
#include <vector>


namespace PARSER {
    class MIFParser
    {
    public:
        MIFParser();
        virtual ~MIFParser();

        bool load(const std::vector<std::string>& mifRaw);
        bool load(const std::string& mifFile);


        static void processComment(const std::vector<std::string>& in, std::vector<std::string>& out);
    };
}
