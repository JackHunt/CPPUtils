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
#include <fstream>
#include <sstream>

namespace CPPUtils::IO {
    template<typename R, typename I>
    class CSVFile {
    public:
        // Parseable token types.
        enum class TokenType : short {
            REAL,
            INTEGER,
            BOOLEAN,
            STRING
        }

        // Row type.
        using CSVRow = std::variant<R, I, bool, std::string>;

    private:
        // Type of each column. Length determines number of columns.
        std::vector<TokenTypes> types;

        // CSV lines stored here.
        std::vector<CSVRow> data;

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
            // Make input stream.
            std::unique_ptr<std::ifstream> inStr(new std::ifstream(), 
                                                 [](std::ifstream *s) { s->close(); });
        }

        void writeFile(const std::string &fileName) const {
            // Make output stream.
            std::unique_ptr<std::ofstream> inStr(new std::ofstream(),
                                                 [](std::ifstream *s) { s->close(); });
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

        size_t getNumRows() const {
            return data.size();
        }
    };
}

#endif