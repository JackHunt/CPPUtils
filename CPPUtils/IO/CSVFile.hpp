/*
BSD 3-Clause License

Copyright (c) 2018,2019 Jack Miles Hunt
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

#include <CPPUtils/StringManipulation/Tokenizing.hpp>
#include <CPPUtils/Iterators/ZipIterator.hpp>

namespace CPPUtils::IO {
    template<typename R, typename I>
    class CSVFile {
    public:
        // Parseable token types.
        enum class ElementType : short {
            REAL,
            INTEGER,
            BOOLEAN,
            STRING
        };

        // Elements can be Real, Integer, Boolean or String.
        using CSVElement = std::variant<R, I, bool, std::string>; 
        using CSVRow = std::vector<CSVElement>;

        // Clean up stream ptrs.
        template<typename T>
        using StreamPtr = std::unique_ptr< T, std::function<void(T*)> >;

    protected:
        // Type of each column. Length determines number of columns.
        std::vector<ElementType> types;

        // CSV lines stored here.
        std::vector<CSVRow> data;

      protected:
          template<typename U>
          static U getRawFromElement(const CSVElement &element) {
              try {
                  return std::get<U>(element);
              }
              catch (const std::invalid_argument &e) {
                  std::cerr << "CSV: Error extracting element. Incorrect type." << std::endl;
                  throw e;
              }
          }

        CSVRow parseTokens(const std::vector<std::string> &tokens) {
            if (types.size() != 0 && types.size() != tokens.size()) {
                std::stringstream ss;
                ss << "CSV: Error parsing tokens. Found " << types.size()
                   << " per-column types, but " << tokens.size() << " tokens.";
                    throw std::runtime_error(ss.str());
            }

            // For each token, find it's type and add.
            CSVRow row;
            std::vector<ElementType> parsedTypes;
            for (const auto &token : tokens) {
                // First try integer if obviously not an int (containing a ',').
                if (token.find(".") == std::string::npos) {
                    try {
                        const I val = static_cast<I>(std::stoll(token));
                        row.push_back(CSVElement({ val }));
                        parsedTypes.push_back(ElementType::INTEGER);
                        continue;
                    }
                    catch (const std::invalid_argument &e) {}
                }

                // Next try floating point.
                try {
                    const R val = static_cast<R>(std::stold(token));
                    row.push_back(CSVElement({ val }));
                    parsedTypes.push_back(ElementType::REAL);
                    continue;
                }
                catch (const std::invalid_argument &e) {}

                // Then boolean.
                if (token == "True" || token == "true" || token == "T") {
                    row.push_back(CSVElement({true}));
                    parsedTypes.push_back(ElementType::BOOLEAN);
                    continue;
                }
                if (token == "False" || token == "false" || token == "F") {
                    row.push_back(CSVElement({false}));
                    parsedTypes.push_back(ElementType::BOOLEAN); 
                    continue;
                }

                // If we get here, it's not parsable as numeric or bool, so place it in verbatim.
                row.push_back(token);
                parsedTypes.push_back(ElementType::STRING);
            }

            // Verify the types and return.
            if (types.size() == 0) { // If first parse and types not set.
                types = parsedTypes;
            } 
            else {
                if (!std::equal(types.begin(), types.end(), parsedTypes.begin())) {
                    std::stringstream ss;
                    ss << "CSV: Error verifying types. Parsed types and known types "
                       << "do not match.";
                    throw std::runtime_error(ss.str());
                }
            }
            return row;
        }

        std::string getRowAsString(const CSVRow &row) const {
            // To zip elements and types.
            using CPPUtils::Iterators::ZipperFactory;

            std::ostringstream lineStream;
            const auto zipper = ZipperFactory<CSVRow, std::vector<ElementType>>()(row, types);
            for (const auto &[v, t] : zipper) {
                switch (*t) {
                case ElementType::REAL: {
                    R realVal = getRawFromElement<R>(*v);
                    lineStream << realVal << ", ";
                    break;
                }
                case ElementType::INTEGER: {
                    I intVal = getRawFromElement<I>(*v);
                    lineStream << intVal << ", ";
                    break;
                }
                case ElementType::BOOLEAN: {
                    bool boolVal = getRawFromElement<bool>(*v);
                    lineStream << ((boolVal) ? "True" : "False") << ", ";
                    break;
                }
                case ElementType::STRING: {
                    std::string stringVal = getRawFromElement<std::string>(*v);
                    lineStream << stringVal << ", ";
                    break;
                }
                default:
                    // Should never get here.
                    throw std::runtime_error("CSV: Unknown type.");
                }               
            }
            lineStream.flush();
            const auto outString = lineStream.str();
            return outString.substr(0, outString.size() - 2);
        }

        void verifyRow(const CSVRow &row) const {
            // First verify lengths.
            if (row.size() != types.size()) {
                std::stringstream ss;
                ss << "CSV: Error verifying row. Found " << types.size()
                   << " per-column types, but " << row.size() << " tokens "
                   << "in the provided row.";
                throw std::runtime_error(ss.str());
            }

            // To zip elements and types.
            using CPPUtils::Iterators::ZipperFactory;

            // Next verify types.
            const auto zipper = ZipperFactory<CSVRow, std::vector<ElementType>>()(row, types);
            for (const auto &&[v, t] : zipper) {
                switch (t) {
                case ElementType::REAL:
                    getRawFromElement<R>(*v);
                    break;
                case ElementType::INTEGER:
                    getRawFromElement<I>(*v);
                    break;
                case ElementType::BOOLEAN:
                    getRawFromElement<bool>(*v);
                    break;
                case ElementType::STRING:
                    getRawFromElement<std::string>(*v);
                    break;
                default:
                    // Should never get here.
                    throw std::runtime_error("CSV: Unknown type.");
                }
            }
        }

    public:
        CSVFile() {
            //
        }

        CSVFile(const std::vector<ElementType> &types) : types(types) {
            //
        }

        virtual ~CSVFile() {
            //
        }
        
        void readFromDisk(const std::string &fileName) {
            // Import delimiter tokenizing routine.
            using CPPUtils::StringManipulation::splitOnDelimiter;

            // Make input stream and attempt to open given file.
            try {
                StreamPtr<std::ifstream> inStr(new std::ifstream(fileName), 
                                               [](std::ifstream *s) { 
                                                   if (s->is_open()) {
                                                       s->close();
                                                   }
                                                   delete s; 
                                               });

                // Read each line.
                std::string line;
                while (std::getline(*inStr, line)) {
                    const auto tokens = splitOnDelimiter(line, ',');
                    const auto row = parseTokens(tokens);
                    data.push_back(row);
                }
            }
            catch (const std::ifstream::failure &e) {
                std::cerr << "CSV: Error opening input file: " << fileName << std::endl;
                throw e;
            }
        }

        void writeToDisk(const std::string &fileName) const {
            // To zip elements and types.
            using CPPUtils::Iterators::ZipperFactory;

            // If nothing to write, early out.
            if (data.size() == 0) {
                return;
            }

            // Make output stream.
            StreamPtr<std::ofstream> outStr(new std::ofstream(fileName),
                                            [](std::ofstream *s) { 
                                                if (s->is_open()) {
                                                    s->flush();
                                                    s->close();
                                                }
                                                delete s;
                                            });

            // Write out each row.
            for (const auto &row : data) {
                *outStr << getRowAsString(row) << std::endl;
            }
        }

        void appendRow(const std::string &line) {
            // Import delimiter tokenizing routine.
            using CPPUtils::StringManipulation::splitOnDelimiter;

            const auto tokens = splitOnDelimiter(line, ',');
            const auto row = parseTokens(tokens);
            data.push_back(row);
        }

        void appendRow(const CSVRow &row) {
            verifyRow(row);
            data.push_back(row);
        }

        void append(const CSVFile &csvFile) {
            for (const auto &row : csvFile.getData()) {
                verifyRow(row);
                data.push_back(row);
            }
        }

        const std::vector<CSVRow> &getData() const {
            return data;
        }

        std::vector< std::vector<R> > getDataNumeric() const {
            // To zip elements and types.
            using CPPUtils::Iterators::ZipperFactory;

            std::vector< std::vector<R> > outNumeric;
            for (const auto &row : data) {
                std::vector<R> numericRow;
                const auto zipper = ZipperFactory< CSVRow, std::vector<ElementType> >()(row, types);
                for (const auto &[v, t] : zipper) {
                    if (*t == ElementType::REAL) {
                        numericRow.push_back(getRawFromElement<R>(*v));
                    }

                    if (*t == ElementType::INTEGER) {
                        numericRow.push_back(static_cast<R>(getRawFromElement<I>(*v)));
                    }
                }
                outNumeric.push_back(numericRow);
            }
            return outNumeric;
        }

        std::vector<std::string> getDataString() const {
            std::vector<std::string> outStrings;
            for (const auto &row : data) {
                outStrings.push_back(getRowAsString(row));
            }
            return outStrings;
        }

        size_t getNumRows() const {
            return data.size();
        }

        const std::vector<ElementType> &getDataTypes() const {
            return types;
        }
    };
}
#endif