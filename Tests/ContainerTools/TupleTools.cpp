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

#include <utility>

#include <gtest/gtest.h>

#include <CPPUtils/ContainerTools/TupleTools.hpp>

using namespace CPPUtils::ContainerTools::Tuple;

class TupleToolsTestSuite : public ::testing::Test {
 protected:
    void SetUp() override {
        //
    }
};

TEST_F(TupleToolsTestSuite, TupleForTest) {
    auto t = std::make_tuple(static_cast<int>(1), 
                             static_cast<float>(2.0), 
                             static_cast<long>(-3),
                             static_cast<double>(-2.5));
    
    constexpr auto a = -5.0;
    
    tupleFor(t, [&a](size_t idx, auto& elem) {
        elem += a;
    });

    ASSERT_EQ(std::get<0>(t), -4);
    ASSERT_EQ(std::get<1>(t), -3.0);
    ASSERT_EQ(std::get<2>(t), -8.0);
    ASSERT_EQ(std::get<3>(t), -7.5);
}
