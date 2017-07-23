#include "mif_parser.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>


namespace PARSER {
    MIFParser::MIFParser()
    {
    }


    MIFParser::~MIFParser()
    {
    }

    bool MIFParser::load(const std::vector<std::string>& mifRaw)
    {
        std::vector<std::string> mifWithoutComment = processComment(mifRaw);
        mifWithoutComment = processComment(mifWithoutComment);

        for (const std::string& line : mifWithoutComment)
        {
            std::cout << line << std::endl;
        }

        return false;
    }

    bool MIFParser::load(const std::string & mifFile)
    {
        std::ifstream fin;
        fin.open(mifFile);

        if (fin.is_open()) {
            // Copy the content of the file stream
            std::string line;
            std::vector<std::string> mifRaw;
            while (std::getline(fin, line)) {
                mifRaw.push_back(std::move(line));
            }
            fin.close();

            return load(mifRaw);
        }

        return false;
    }


    /*
     * This function removes all comments in the mif file
     */
    std::vector<std::string> MIFParser::processComment(const std::vector<std::string>& in)
    {
        /* Comments format:
         * 1) (Multi-line) comment enclosed by percent "%" character
         * 2) Single comment with double dash "--" characters.
         */
        std::vector<std::string> out;

        bool inMultiLineComment = false;
        for (const std::string& line : in) {
            // Check the line one char at a time
            std::string newLine;

            char prev = '\n';
            for (char c : line) {
                if (c == '%') {
                    // Multi-line comment sign
                    // Flip the state
                    inMultiLineComment = !inMultiLineComment;
                }
                else if (c == '-' && prev == '-') {
                    // Single-line comment sign
                    if (!inMultiLineComment) {
                        // We skip the entire line if we see a single-line comment sign, also pop the previous '-' sign in newLine
                        assert(newLine.back() == '-');
                        newLine.pop_back();
                        break;
                    }
                }
                else {
                    // Regular characters
                    if (!inMultiLineComment) {
                        // Not in comment
                        // We append this character into newLine
                        newLine += c;
                        prev = c;
                    }
                }
            }
            out.push_back(std::move(newLine));
        }

        return out;
    }


    /*
     * This function removes empty lines in the mif file, and converts all characters to upper case.
     */
    std::vector<std::string> MIFParser::processFormat(const std::vector<std::string>& in)
    {
        std::vector<std::string> out;
        for (std::string line : in) {
            if (!line.empty()) {
                std::transform(line.begin(), line.end(), line.begin(),
                    [](char c) -> char {
                    return static_cast<char>(::toupper(static_cast<int>(c)));
                });
                out.push_back(line);
            }
        }
        return out;
    }


    /*
     * This function parses the MIF property info from the mif file, and
     * returns the data via struct MIFProperty.
     */
    MIFParser::MIFProperty MIFParser::parseProperty(const std::vector<std::string>& in)
    {
        std::size_t depth = 0;
        std::size_t width = 0;
        radix_e addressRadix = radix_e::INVALID;
        radix_e dataRadix = radix_e::INVALID;
        MIFProperty property = { depth,width,addressRadix,dataRadix };

        //std::regex depthExp();
        //std::regex widthExp();
        //std::regex addressRadixExp();
        //std::regex dataRadixExp();

        bool depthFound = false;
        bool widthFound = false;
        bool addressRadixFound = false;
        bool dataRadixFound = false;

        for (const std::string & line : in) {


            if (depthFound && widthFound && addressRadixFound && dataRadixFound) {
                break;
            }
            if (line.find("CONTENT") != std::string::npos) {
                break;
            }
        }

        return property;
    }
}
