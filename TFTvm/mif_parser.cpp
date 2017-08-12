#include "mif_parser.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <sstream>
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
        // Process the comment
        std::vector<std::string> mifWithoutComment = processComment(mifRaw);
        // Process the format
        mifWithoutComment = processFormat(mifWithoutComment);

        std::cout << std::endl;
        std::cout << "===MIF CONTENT AFTER PREPROCESSOR===" << std::endl;
        for (const std::string& line : mifWithoutComment)
        {
            std::cout << line << std::endl;
        }
        std::cout << "***END MIF CONTENT AFTER PREPROCESSOR***" << std::endl;
        std::cout << std::endl;

        // Parse the property
        MIFProperty mifProperty = parseProperty(mifWithoutComment);

        std::string enumString;
        std::cout << std::endl;
        std::cout << "===MIF PROPERTY===" << std::endl;
        std::cout << "DEPTH = <" << mifProperty.depth << ">" << std::endl;
        std::cout << "WIDTH = <" << mifProperty.width << ">" << std::endl;
        mifProperty.address_radix >> enumString;
        std::cout << "ADDRESS_RADIX = <" << enumString << ">" << std::endl;
        mifProperty.data_radix >> enumString;
        std::cout << "DATA_RADIX = <" << enumString << ">" << std::endl;
        std::cout << "***END MIF PROPERTY***" << std::endl;
        std::cout << std::endl;

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
     * This function removes empty lines in the mif file, converts all characters to upper case, and
     * removes any blank characters.
     */
    std::vector<std::string> MIFParser::processFormat(const std::vector<std::string>& in)
    {
        std::vector<std::string> out;
        for (const std::string& line : in) {
            if ([](const std::string &s)-> bool { // Check whether line is completely empty or all blank characters
                return std::any_of(s.begin(), s.end(), [](char c)->bool {return !::isblank(static_cast<int>(c)); });
            }(line)) {
                std::string newLine;
                std::for_each(line.begin(), line.end(),
                    [&newLine](char c) {
                    if (!::isblank(static_cast<int>(c))) {
                        newLine += static_cast<char>(::toupper(static_cast<int>(c)));
                    }
                });
                out.push_back(std::move(newLine));
            }
        }
        return out;
    }


    /*
     * This function parses the MIF property info from the mif file, and
     * returns the data via struct MIFProperty.
     * This function should only be used after
     * 1) processComment()
     * 2) processFormat()
     */
    MIFParser::MIFProperty MIFParser::parseProperty(const std::vector<std::string>& in)
    {
        std::size_t depth = 0;
        std::size_t width = 0;
        radix_e addressRadix = radix_e::INVALID;
        radix_e dataRadix = radix_e::INVALID;

        std::regex depthExp("DEPTH=([0-9]+);", std::regex_constants::icase);
        std::regex widthExp("WIDTH=([0-9]+);", std::regex_constants::icase);
        std::regex addressRadixExp("ADDRESS_RADIX=([[:alpha:]]{3});", std::regex_constants::icase);
        std::regex dataRadixExp("DATA_RADIX=([[:alpha:]]{3});", std::regex_constants::icase);

        bool depthFound = false;
        bool widthFound = false;
        bool addressRadixFound = false;
        bool dataRadixFound = false;

        for (const std::string & line : in) {
            std::smatch m;
            // If find the "CONTENT", break the loop
            if (line.find("CONTENT") != std::string::npos) {
                break;
            }
            else if (std::regex_match(line, m, depthExp)) { // exact match
                // Flip the state
                depthFound = !depthFound;
                if (depthFound == false) {
                    break;
                }
                else {
                    std::stringstream ss;
                    ss << m[1];
                    ss >> depth;
                }
            }
            else if (std::regex_match(line, m, widthExp)) { // exact match
                // Flip the state
                widthFound = !widthFound;
                if (widthFound == false) {
                    break;
                }
                else {
                    std::stringstream ss;
                    ss << m[1];
                    ss >> width;
                }
            }
            else if (std::regex_match(line, m, addressRadixExp)) { // exact match
                // Flip the state
                addressRadixFound = !addressRadixFound;
                if (addressRadixFound == false) {
                    break;
                }
                else {
                    addressRadix << m[1];
                }
            }
            else if (std::regex_match(line, m, dataRadixExp)) { // exact match
                // Flip the state
                dataRadixFound = !dataRadixFound;
                if (dataRadixFound == false) {
                    break;
                }
                else {
                    dataRadix << m[1];
                }
            }

            // If all fields are found, break the loop
            if (depthFound && widthFound && addressRadixFound && dataRadixFound) {
                break;
            }
        }

        // If any of the field is not found (or invalid)
        if (!(depthFound && widthFound && addressRadixFound && dataRadixFound)) {
            depth = 0;
            width = 0;
            addressRadix = radix_e::INVALID;
            dataRadix = radix_e::INVALID;
        }

        return MIFProperty{ depth,width,addressRadix,dataRadix };
    }
}
