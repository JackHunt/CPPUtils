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

#ifndef CPP_UTILS_LINEAR_ALGEBRA_BLAS_H
#define CPP_UTILS_LINEAR_ALGEBRA_BLAS_H

#include <stdexcept>

namespace CPPUtils::LinearAlgebra::BLAS {
    /*
     * GEMM
     */
    template<typename T>
    inline void gemm(const T* const A, const T* const B, T* const C,
                         size_t M, size_t K, size_t N) {
        throw std::logic_error("Unknown data type for GEMM.")
    }

    template<>
    inline void gemm(const float* const A, const float* const B, float* const C,
                         size_t M, size_t K, size_t N) {
        // Do SGEMM
    }

    template<>
    inline void gemm(const double* const A, const double* const B, double* const C,
                         size_t M, size_t K, size_t N) {
        // Do DGEMM
    }

    /*
     * AXPY
     */
    template<typename T>
    inline void axpy(T* const Y, const T* const X, T alpha, size_t N) {
        throw std::logic_error("Unknown data type for AXPY.")
    }

    template<>
    inline void axpy(float* const Y, const float* const X, float alpha, size_t N) {
        // Do SAXPY
    }

    template<>
    inline void axpy(double* const Y, const double* const X, double alpha, size_t N) {
        // Do DAXPY
    }
}

#endif