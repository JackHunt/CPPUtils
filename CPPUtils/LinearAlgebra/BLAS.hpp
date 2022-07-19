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

#include <mkl.h>

#include <stdexcept>

namespace CPPUtils::LinearAlgebra::BLAS {
    /*
     * GEMM
     */
    struct GEMMCallConfig final {
        const size_t M, K, N;
        const CBLAS_TRANSPOSE transA, transB;
        const float alpha, beta;
        const size_t lda, ldb, ldc;

        GEMMCallConfig(size_t M, size_t K, size_t N,
                       bool transA = false, bool transB = false,
                       float alpha = 1.0, float beta = 0.0) : 
            M(M), K(K), N(N),
            transA(transA ? CblasTrans : CblasNoTrans),
            transB(transB ? CblasTrans : CblasNoTrans),
            alpha(alpha), beta(beta),
            lda(transA ? M : K),
            ldb(transB ? K : N),
            ldc(transA ? M : K) {
            //
        }

        GEMMCallConfig(size_t M, size_t K, size_t N,
                       CBLAS_TRANSPOSE transA, CBLAS_TRANSPOSE transB,
                       float alpha, float beta,
                       size_t lda, size_t ldb, size_t ldc) : 
            M(M), K(K), N(N),
            transA(transA), transB(transB),
            alpha(alpha), beta(beta),
            lda(lda), ldb(ldb), ldc(ldc) {
            //
        }
    };

    template<typename T>
    inline void gemm(const T* const A, const T* const B, T* const C,
                     const GEMMCallConfig& cfg) {
        throw std::logic_error("Unknown data type for GEMM.");
    }

    template<>
    inline void gemm(const float* const A, const float* const B, float* const C,
                     const GEMMCallConfig& cfg) {
        cblas_sgemm(CblasRowMajor, cfg.transA, cfg.transB, cfg.M, cfg.N, cfg.K,
                    cfg.alpha, A, cfg.lda, B, cfg.ldb, cfg.beta, C, cfg.ldc);
    }

    template<>
    inline void gemm(const double* const A, const double* const B, double* const C,
                     const GEMMCallConfig& cfg) {
        cblas_dgemm(CblasRowMajor, cfg.transA, cfg.transB, cfg.M, cfg.N, cfg.K,
                    cfg.alpha, A, cfg.lda, B, cfg.ldb, cfg.beta, C, cfg.ldc);
    }

    /*
     * AXPY
     */
    struct AXPYCallConfig final {
        const size_t N;
        const float alpha;
        const size_t incx, incy;

        AXPYCallConfig(size_t N, float alpha) :
            N(N), alpha(alpha), incx(1), incy(1) {
             //
        }

        AXPYCallConfig(size_t N, float alpha, size_t incx, size_t incy) :
            N(N), alpha(alpha), incx(incx), incy(incy) {
            //
        }
    };

    template<typename T>
    inline void axpy(T* const Y, const T* const X, const AXPYCallConfig& cfg) {
        throw std::logic_error("Unknown data type for AXPY.");
    }

    template<>
    inline void axpy(float* const Y, const float* const X, const AXPYCallConfig& cfg) {
        cblas_saxpy(cfg.N, cfg.alpha, X, cfg.incx, Y, cfg.incy);
    }

    template<>
    inline void axpy(double* const Y, const double* const X, const AXPYCallConfig& cfg) {
        cblas_daxpy(cfg.N, cfg.alpha, X, cfg.incx, Y, cfg.incy);
    }

    /*
     * SCAL
     */
    struct SCALCallConfig final {
        const size_t N;
        const float alpha;
        const size_t incx;

        SCALCallConfig(size_t N, float alpha) :
            N(N), alpha(alpha), incx(1) {
             //
        }

        SCALCallConfig(size_t N, float alpha, size_t incx) :
            N(N), alpha(alpha), incx(incx) {
            //
        }
    };

    template<typename T>
    inline void scal(T* const X, const SCALCallConfig& cfg) {
        throw std::logic_error("Unknown data type for SCAL.");
    }

    template<>
    inline void scal(float* const X, const SCALCallConfig& cfg) {
        cblas_sscal(cfg.N, cfg.alpha, X, cfg.incx);
    }

    template<>
    inline void scal(double* const X, const SCALCallConfig& cfg) {
        cblas_dscal(cfg.N, cfg.alpha, X, cfg.incx);
    }
}

#endif