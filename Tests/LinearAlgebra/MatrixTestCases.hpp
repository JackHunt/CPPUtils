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

#ifndef CPP_UTILS_TESTS_LINEAR_ALGEBRA_MATRIX_EXAMPLES_H
#define CPP_UTILS_TESTS_LINEAR_ALGEBRA_MATRIX_EXAMPLES_H

#include <array>
#include <tuple>

#include <gtest/gtest.h>

#include <CPPUtils/LinearAlgebra/Matrix.hpp>

using CPPUtils::LinearAlgebra::Matrix;
using CPPUtils::LinearAlgebra::Util::DeviceType;

namespace TestUtils::LinearAlgebra {

    template<typename T, size_t M, size_t N, size_t K>
    struct MatmulTestCase {
        const std::array<T, M * N> A;
        const std::array<T, N * K> B;
        const std::array<T, M * K> C;

        explicit MatmulTestCase(const std::array<T, M * N> A,
                                const std::array<T, N * K> B,
                                const std::array<T, M * K> C) :
            A(A), B(B), C(C) {
            static_assert(M >= 1);
            static_assert(N >= 1);
            static_assert(K >= 1);
        }
        
        template<DeviceType D>
        using ABCMatrices = std::tuple<Matrix<T, D>,
                                       Matrix<T, D>,
                                       Matrix<T, D>>;
        
        template<DeviceType D = DeviceType::CPU>
        ABCMatrices<D> asMatrices() const {
            //return std::make_tuple();
        }
    };

    namespace TestMatrices {
        template<typename T, size_t M, size_t N>
        inline constexpr std::array<T, M * N> eye() {
            std::array<T, M * N> I;
            for (size_t m = 0; m < M; m++) {
                for (size_t n = 0; n < N; n++) {
                    constexpr size_t idx = m * N + n;
                    I[idx] = m == n ? 1 : 0;
                }
            }

            return I;
        }

        template<typename T>
        inline constexpr std::array<T, 16> A() {
            //
        }

        template<typename T>
        inline constexpr std::array<T, 16> B() {
            //
        }

        template<typename T>
        inline constexpr std::array<T, 16> C() {
            //
        }
    }

    template<typename T>
    struct MatmulTestCase0 final : public MatmulTestCase<T, 4, 4, 4> {
        MatmulTestCase0() :
            MatmulTestCase<T, 4, 4, 4>({1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1},
                                       {1,1,1,1},
                                       {1,1,1,1}) {
            //
        }
    };

    using MatmulCases = ::testing::Types<>;

}



#endif
