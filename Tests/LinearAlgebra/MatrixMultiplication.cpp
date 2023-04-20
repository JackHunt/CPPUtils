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

#include <gtest/gtest.h>

#include <CPPUtils/LinearAlgebra/BLAS.hpp>
#include "MatrixTestCases.hpp"

using namespace CPPUtils::LinearAlgebra;
using namespace CPPUtils::LinearAlgebra::BLAS;
using namespace TestUtils::LinearAlgebra;

template <typename T>
class MatrixMultiplicationTestSuite : public ::testing::Test {
 public:
    using TestCase = T;

 protected:
    void SetUp() override {
        //
    }
};

TYPED_TEST_SUITE(MatrixMultiplicationTestSuite, MatmulCases<float>);

TYPED_TEST(MatrixMultiplicationTestSuite, GEMMTest) {
    const auto A = typename TypeParam::A();
    const auto B = typename TypeParam::B();
    const auto C = typename TypeParam::C();

    const auto M = A.Rows;
    const auto K = A.Cols;
    const auto N = B.Cols;

    auto C_out = decltype(C.elems)();

    GEMMCallConfig cfg(M, K, N);
    gemm<float>(A.elems, B.elems, C_out, cfg);

    for (size_t n = 0; n < M * N; n++) {
      EXPECT_FLOAT_EQ(C.elems[n], C_out[n]);
    }
}

TYPED_TEST(MatrixMultiplicationTestSuite, MatrixMultiplyTest) {
    const auto A = typename TypeParam::A().asMatrix();
    const auto B = typename TypeParam::B().asMatrix();
    const auto C = typename TypeParam::C().asMatrix();

    const auto D = A * B;

    const auto C_elems = C.data();
    const auto D_elems = D.data();

    for (size_t n = 0; n < C.num_rows() * C.num_columns(); n++) {
      EXPECT_FLOAT_EQ(C_elems[n], D_elems[n]);
    }
}
