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

#include <map>
#include <vector>

#include <gtest/gtest.h>

#include <CPPUtils/Iterators/ZipIterator.hpp>

using namespace CPPUtils::Iterators;

class ZipIteratorTestSuite : public ::testing::Test {
 protected:
    void SetUp() override {
      //
    }
};

TEST_F(ZipIteratorTestSuite, ReadOnlyTwoWayZipTest) {
    const std::vector<int> a = { 0, 1, 2, 3, 4, 5 };
    const std::vector<bool> b = { true, false, true, true };

    auto zipper = ZipperFactory<decltype(a), decltype(b)>()(a, b);

    const auto max = b.size();
    size_t idx = 0;
    for (const auto [x, y] : zipper) {
        ASSERT_LT(idx, max);
        ASSERT_EQ(*x, a.at(idx));
        ASSERT_EQ(*y, b.at(idx));
        idx++;
    }

    ASSERT_EQ(idx, max);
}

TEST_F(ZipIteratorTestSuite, ReadOnlyThreeWayZipTest) {
    const std::vector<int> a = { 0, 1, 2, 3, 4, 5 };
    const std::vector<bool> b = { true, false, true, true };
    const std::map<char, float> m = {{'a', 0}, {'b', 1}, {'c', 2}};

    auto zipper = ZipperFactory<decltype(a), decltype(b), decltype(m)>()(a, b, m);

    const auto max = m.size();
    size_t idx = 0;
    for (const auto [x, y, z] : zipper) {
        ASSERT_LT(idx, max);
        ASSERT_EQ(*x, a.at(idx));
        ASSERT_EQ(*y, b.at(idx));
        ASSERT_EQ(z->second, m.at(z->first));
        idx++;
    }

    ASSERT_EQ(idx, max);
}
