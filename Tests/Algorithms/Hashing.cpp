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

#include <tuple>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include <CPPUtils/Algorithms/Hashing.hpp>

using namespace CPPUtils::Algorithms;

using Case = std::tuple<int, int, int>;

class CantorHashingTestSuite : public testing::TestWithParam<Case> {
 protected:
    void SetUp() override {
        //
    }
};

TEST_P(CantorHashingTestSuite, CantorHashTest) {
    int a, b, c;
    std::tie(a, b, c) = GetParam();
    ASSERT_EQ(cantorHash(a, b), c);
}

TEST_P(CantorHashingTestSuite, InverseCantorHashTest) {
    int a, b, c;
    std::tie(a, b, c) = GetParam();
    ASSERT_EQ(inverseCantorHash(c), std::make_pair(a, b));
}

INSTANTIATE_TEST_SUITE_P(
    CantorTestCases,
    CantorHashingTestSuite,
    testing::Values(
        Case(0, 0, 0),
        Case(0, 1, 2),
        Case(0, 2, 5),
        Case(0, 3, 9),
        Case(1, 0, 1),
        Case(1, 1, 4),
        Case(1, 2, 8),
        Case(1, 3, 13),
        Case(2, 0, 3),
        Case(2, 1, 7),
        Case(2, 2, 12),
        Case(2, 3, 18),
        Case(3, 0, 6),
        Case(3, 1, 11),
        Case(3, 2, 17),
        Case(3, 3, 24)));
