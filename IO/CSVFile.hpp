/*
BSD 3-Clause License

Copyright (c) 2018, Jack Miles Hunt
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef CPP_UTILS_CSV_FILE
#define CPP_UTILS_CSV_FILE

#include <string>
#include <variant>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "../StringManipulation/Tokenizing.hpp"

namespace CPPUtils::IO {
    template<typename R, typename I>
    class CSVFile {
    protected:
        // Type of each column. Length determines number of columns.
        std::vector<TokenTypes> types;

        // CSV lines stored here.
        std::vector<CSVRow> data;

    public:
        // Parseable token types.
        enum class TokenType : short {
            REAL,
            INTEGER,
            BOOLEAN,
            STRING
        };

        // Elements can be Real, Integer, Boolean or String.
        using CSVElement = std::variant<R, I, bool, std::string>; 
        using CSVRow = std::vector<CSVElement>;

      protected:
        CSVRow parseTokens(const std::vector<std::string> &tokens) {
            if (types.size() != 0) {
                assert(tokens.size() == types.size());
            }

            // For each token, find it's type and add.
            CSVRow row;
            std::vector<TokenTypes> parsedTypes;
            for (const auto &token : tokens) {
                // First try floating point.
                try {
                    const R val = static_cast<R>(std::stold(token));
                    row.push_back(CSVElement({val}));
                    parsedTypes.push_back(TokenType::REAL);
                    continue;
                } catch(const std::invalid_argument &e) {}

                // Next try integer.
                try {
                    const I val = static_cast<I>(std::stoll(token));
                    row.push_back(CSVElement({val}));
                    parsedTypes.push_back(TokenType::INTEGER);
                    continue;
                } catch (const std::invalid_argument &e) {}

                // Then boolean.
                if (token == "True" || token == "true" || token == "T") {
                    row.push_back(CSVElement({true}));
                    parsedTypes.push_back(TokenType::BOOLEAN);
                    continue;
                }
                if (token == "False" || token == "false" || token == "F") {
                    row.push_back(CSVElement({false}));
                    parsedTypes.push_back(TokenType::BOOLEAN); 
                    continue;
                }

                // If we get here, it's not parsable, so place it in verbatim.
                row.push_back(token);
                parsedTypes.push_back(TokenType::STRING);
            }

            // Verify the types and return.
            if (types.size() == 0) { // If first parse and types not set.
                types = parsedTypes;
            } 
            else {
                assert(std::equal(types.begin(), types.end(), parsedTypes.begin()));
            }
            return row;
        }

    public:
        CSVFile() {
            //
        }

        CSVFile(const std::vector<TokenType> &types) : types(types) {
            //
        }

        virtual ~CSVFile() {
            //
        }
        
        void readFile(const std::string &fileName) {
            // Import delimiter tokenizing routine.
            using CPPUtils::StringManipulation::splitOnDelimiter();

            // Make input stream and attempt to open given file.
            try {
                std::unique_ptr<std::ifstream> inStr(new std::ifstream(fileName), 
                                                     [](std::ifstream *s) { 
                                                         if (s->is_open()) {
                                                             s->close();
                                                         }
                                                         delete s; 
                                                     });
            }
            catch (const std::ifstream::failure &e) {
                std::cerr << "CSV: Error opening input file: " << fileName << std::endl;
                throw e;
            }

            // Read each line.
            std::string line;
            while (std::getline(*inStr.get(), line)) {
                // Split the line and verify correct size.
                const auto tokens = splitOnDelimiter(line, ',');
                const auto row = parseTokens(tokens);
                data.push_back(row);
            }
        }

        void writeFile(const std::string &fileName) const {
            // If nothing to write, early out.
            if (data.size() == 0) {
                return;
            }

            // Make output stream.
            std::unique_ptr<std::ofstream> outStr(new std::ofstream(fileName),
                                                  [](std::ofstream *s) { 
                                                      if (s->is_open()) {
                                                          s->close();
                                                      }
                                                      delete s;
                                                  });

            // Write out each row.
            for (const auto &row : data) {
                std::string line;
                std::stringstream lineStream(outString);
                for (const auto &elem : row) {
                    //lineStream << elem.
                }
            }
        }

        void appendRow(const std::string &row) {
            //
        }

        void appendRow(const CSVRow &row) {
            //
        }

        void append(const CSVFile &csvFile) {
            // Iterate over csvFile
        }

        const std::vector<CSVRow> &getData() const {
            //
        }

        std::vector< std::vector<R> > getDataNumeric() const {
            //
        }

        std::vector<std::string> getDataString() const {
            //
        }

        size_t getNumRows() const {
            return data.size();
        }
    };
}

#endif