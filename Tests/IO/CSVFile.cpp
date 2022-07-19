/*
BSD 3-Clause License

Copyright (c) 2022 Jack Miles Hunt
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

#include <filesystem>
#include <vector>

#include <gtest/gtest.h>

#include <CPPUtils/IO/CSVFile.hpp>

using namespace CPPUtils::IO;

template<typename T>
static void verifyEqual(const std::vector<T>& a, const std::vector<T>& b) {
    EXPECT_EQ(a.size(), b.size());

    for (size_t i = 0; i < a.size(); i++) {
        EXPECT_EQ(a.at(i), b.at(i));
    }
}

TEST(CSVTestSuite, BasicCSVWriteReadTest) {
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
    verifyEqual(csv.getDataTypes(), csv2.getDataTypes());

    // Verify the rows.
    const auto rows = csv.getData();
    const auto rows2 = csv2.getData();

    EXPECT_EQ(rows.size(), rows2.size());
    EXPECT_EQ(csv.getNumRows(), csv2.getNumRows());

    for (size_t i = 0; i < rows.size(); i++) {
        verifyEqual(rows.at(i), rows2.at(i));
    }

    // Clear up.
    EXPECT_TRUE(std::filesystem::remove(fname));
}

template<typename T, typename U>
static void typeParseTestImpl() {
    using CSV = CSVFile<T, U>;
    using V = typename CSV::ElementType;

    constexpr auto vals = "3.14, True, 2, 6.28, abc, 6.28, False, -2, 3.14, cba";
    const std::vector<V> types = {
        V::REAL, V::BOOLEAN, V::INTEGER, V::REAL, V::STRING,
        V::REAL, V::BOOLEAN, V::INTEGER, V::REAL, V::STRING
    };

    CSV csv;
    csv.appendRow(vals);

    const auto types2 = csv.getDataTypes();
    verifyEqual(types, types2);
}

TEST(CSVTestSuite, CSVTypeParseTest) {
    typeParseTestImpl<float, short>();
    typeParseTestImpl<float, int>();
    typeParseTestImpl<float, long>();
    
    typeParseTestImpl<double, short>();
    typeParseTestImpl<double, int>();
    typeParseTestImpl<double, long>();
}
