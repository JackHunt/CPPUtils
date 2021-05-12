/*
BSD 3-Clause License

Copyright (c) 2021 Jack Miles Hunt
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

#define BOOST_TEST_MODULE CSVFileTests

#include <filesystem>

#include <boost/test/included/unit_test.hpp>

#include <CPPUtils/IO/CSVFile.hpp>

using namespace CPPUtils::IO;

BOOST_AUTO_TEST_SUITE(CSVFileTestSuite)

BOOST_AUTO_TEST_CASE(BasicCSVWriteTest) {
    // Test data.
    constexpr auto a = "3.14, True, 2, 6.28, abc";
    constexpr auto b = "6.28, False, -2, 3.14, cba";

    // Create a CSV file and append some data.
    CSVFile<float, int> csv;
    csv.appendRow(a);
    csv.appendRow(b);

    // Get temp directory path.
    const auto tmp_path = std::filesystem::temp_directory_path();
    const auto fname = tmp_path / "test.csv";

    // Write the CSV out to a file.
    csv.writeToDisk(fname.string());

    // Read the file back in.
    decltype(csv) csv2;
    csv2.readFromDisk(fname.string());

    // Verify that the types match.
    const auto types = csv.getDataTypes();
    const auto types2 = csv2.getDataTypes();
    BOOST_CHECK_EQUAL_COLLECTIONS(types.cbegin(), types.cend(),
                                  types2.cbegin(), types2.cend());

    // Verify the rows.
    const auto rows = csv.getData();
    const auto rows2 = csv2.getData();

    BOOST_CHECK_EQUAL(rows.size(), rows2.size());
    BOOST_CHECK_EQUAL(csv.getNumRows(), csv2.getNumRows());

    for (size_t i = 0; i < rows.size(); i++) {
        const auto rowA = rows.at(i);
        const auto rowB = rows2.at(i);

        BOOST_CHECK_EQUAL_COLLECTIONS(rowA.cbegin(), rowA.cend(),
                                      rowB.cbegin(), rowB.cend());
    }

    // Clear up.
    BOOST_CHECK(std::filesystem::remove(fname));
}

BOOST_AUTO_TEST_SUITE_END()