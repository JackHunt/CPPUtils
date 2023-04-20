/*
BSD 3-Clause License

Copyright (c) 2023 Jack Miles Hunt
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

template <typename T, typename U>
struct CSVTypes {
    using FloatType = T;
    using IntegerType = U;
};

template<typename T>
class CSVTestSuite : public ::testing::Test {
 public:
    using CSVTypes = T;

 protected:
    void SetUp() override {
        //
    }

    template<typename U>
    static void verifyEqual(const std::vector<U>& a, const std::vector<U>& b) {
        ASSERT_EQ(a.size(), b.size());

        for (size_t i = 0; i < a.size(); i++) {
            ASSERT_EQ(a.at(i), b.at(i));
        }
    }
};

using CSVTypeDefinitions = ::testing::Types<
    CSVTypes<float, short>,
    CSVTypes<float, int>,
    CSVTypes<float, long>,
    CSVTypes<double, short>,
    CSVTypes<double, int>,
    CSVTypes<double, long>>;

TYPED_TEST_SUITE(CSVTestSuite, CSVTypeDefinitions);

TYPED_TEST(CSVTestSuite, BasicCSVWriteReadTest) {
    using CSV = CSVFile<typename TypeParam::FloatType,
                        typename TypeParam::IntegerType>;

    // Test data.
    constexpr auto a = "3.14, True, 2, 6.28, abc";
    constexpr auto b = "6.28, False, -2, 3.14, cba";

    // Create a CSV file and append some data.
    CSV csv;
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
    this->verifyEqual(csv.getDataTypes(), csv2.getDataTypes());

    // Verify the rows.
    const auto rows = csv.getData();
    const auto rows2 = csv2.getData();

    ASSERT_EQ(rows.size(), rows2.size());
    ASSERT_EQ(csv.getNumRows(), csv2.getNumRows());

    for (size_t i = 0; i < rows.size(); i++) {
        this->verifyEqual(rows.at(i), rows2.at(i));
    }

    // Clear up.
    ASSERT_TRUE(std::filesystem::remove(fname));
}

TYPED_TEST(CSVTestSuite, CSVTypeParseTest) {
    using CSV = CSVFile<typename TypeParam::FloatType,
                        typename TypeParam::IntegerType>;

    using V = typename CSV::ElementType;

    constexpr auto vals = "3.14, True, 2, 6.28, abc, 6.28, False, -2, 3.14, cba";
    const std::vector<V> types = {
        V::REAL, V::BOOLEAN, V::INTEGER, V::REAL, V::STRING,
        V::REAL, V::BOOLEAN, V::INTEGER, V::REAL, V::STRING
    };

    CSV csv;
    csv.appendRow(vals);

    const auto types2 = csv.getDataTypes();
    this->verifyEqual(types, types2);
}
