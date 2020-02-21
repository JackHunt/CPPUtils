/*
BSD 3-Clause License

Copyright (c) 2020 Jack Miles Hunt
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

#include <string>
#include <CPPUtils/IO/CSVFile.hpp>

using CPPUtils::IO::CSVFile;
using CSV = CSVFile<float, int>;

int main() {
    // Make two empty CSV files.
    CSV csvA, csvB;

    // Make a string of parseable types and add to the file.
    const auto a = "3.14, True, 2, 6.28, abc";
    csvA.appendRow(a);

    // Same again.
    const auto b = "6.28, False, -2, 3.14, cba";
    csvB.appendRow(b);

    // Write files out.
    csvA.writeToDisk("a.csv");
    csvB.writeToDisk("b.csv");

    // Create new CSVFile and read in the files.
    CSV c;
    c.readFromDisk("a.csv");
    c.readFromDisk("b.csv");

    // Write out new combined CSV.
    const auto lines = c.getDataString();
    for (const auto &line : lines) {
        std::cout << line << std::endl;
    }
    c.writeToDisk("c.csv");

    // Get numeric types only and print.
    const auto numericRows = c.getDataNumeric();
    for (const auto &row : numericRows) {
        for (auto v : row) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    std::getchar();
    return 0;
}