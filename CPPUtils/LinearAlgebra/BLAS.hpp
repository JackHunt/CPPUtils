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

#ifndef CPP_UTILS_LINEAR_ALGEBRA_BLAS_H
#define CPP_UTILS_LINEAR_ALGEBRA_BLAS_H

#include <cblas.h>

#include <span>
#include <stdexcept>

namespace CPPUtils::LinearAlgebra::BLAS {
    /**
     * @brief A simple configuration struct that defines a matrix
     * multiplication via the BLAS GEMM operation.
     * 
     * Row-major ordering is assumed.
     * 
     */
    struct GEMMCallConfig final {
        const unsigned int M, K, N;
        const CBLAS_TRANSPOSE transA, transB;
        const float alpha, beta;
        const unsigned int lda, ldb, ldc;

        /**
         * @brief Construct a new GEMMCallConfig object.
         * 
         * Specifies a GEMM matrix multiplication between an MxK Matrix
         * and a KxN Matrix, yielding an MxN Matrix (assuming there are
         * no transpositions).
         * 
         * @param M The first dimension of the LHS Matrix.
         * @param K The second dimension of the LHS Matrix (and first of
         * the RHS Matrix).
         * @param N The second dimension of the RHS Matrix.
         * @param transA Whether to transpose the LHS Matrix.
         * @param transB Whether to transpose the RHS Matrix.
         * @param alpha Scalar multiplier for the product.
         * @param beta Scalar multiplier for addition of the output Matrix to
         * the product.
         */
        GEMMCallConfig(unsigned int M, unsigned int K, unsigned int N,
                       bool transA = false, bool transB = false,
                       float alpha = 1.0, float beta = 0.0) : 
            M(M), K(K), N(N),
            transA(transA ? CblasTrans : CblasNoTrans),
            transB(transB ? CblasTrans : CblasNoTrans),
            alpha(alpha), beta(beta),
            lda(transA ? M : K),
            ldb(transB ? K : N),
            ldc(N) {
            //
        }

        /**
         * @brief Construct a new GEMMCallConfig object.
         * 
         * Specifies a GEMM matrix multiplication between an MxK Matrix
         * and a KxN Matrix, yielding an MxN Matrix (assuming there are
         * no transpositions).
         * 
         * @param M The first dimension of the LHS Matrix.
         * @param K The second dimension of the LHS Matrix (and first of
         * the RHS Matrix).
         * @param N The second dimension of the RHS Matrix.
         * @param transA Whether to transpose the LHS Matrix.
         * @param transB Whether to transpose the RHS Matrix.
         * @param alpha Scalar multiplier for the product.
         * @param beta Scalar multiplier for addition of the output Matrix to
         * the product.
         * @param lda The leading dimension of the LHS Matrix A.
         * @param ldb The leading dimension of the RHS Matrix B.
         * @param ldc The leading dimension of the output Matrix C.
         */
        GEMMCallConfig(unsigned int M, unsigned int K, unsigned int N,
                       CBLAS_TRANSPOSE transA, CBLAS_TRANSPOSE transB,
                       float alpha, float beta,
                       unsigned int lda, unsigned int ldb, unsigned int ldc) :
            M(M), K(K), N(N),
            transA(transA), transB(transB),
            alpha(alpha), beta(beta),
            lda(lda), ldb(ldb), ldc(ldc) {
            //
        }
    };

    /**
     * @brief Executes a GEMM operation on A and B, writing
     * output to C.
     * 
     * @tparam T The element type of the A, B and C Matrices.
     * @param A The data buffer for the LHS input Matrix, A.
     * @param B The data buffer for the RHS input Matrix, B.
     * @param C The data buffer for the output Matrix, C.
     * @param cfg A `GEMMCallConfig` instance specifying the GEMM operation.
     */
    template<typename T>
    inline void gemm(const std::span<const T>& A,
                     const std::span<const T>& B,
                     const std::span<T>& C,
                     const GEMMCallConfig& cfg) {
        throw std::domain_error("Unknown data type for GEMM.");
    }

    template<>
    inline void gemm(const std::span<const float>& A,
                     const std::span<const float>& B,
                     const std::span<float>& C,
                     const GEMMCallConfig& cfg) {
        cblas_sgemm(CblasRowMajor, cfg.transA, cfg.transB, cfg.M, cfg.N, cfg.K,
                    cfg.alpha, A.data(), cfg.lda, B.data(), cfg.ldb, cfg.beta, C.data(), cfg.ldc);
    }

    template<>
    inline void gemm(const std::span<const double>& A,
                     const std::span<const double>& B,
                     const std::span<double>& C,
                     const GEMMCallConfig& cfg) {
        cblas_dgemm(CblasRowMajor, cfg.transA, cfg.transB, cfg.M, cfg.N, cfg.K,
                    cfg.alpha, A.data(), cfg.lda, B.data(), cfg.ldb, cfg.beta, C.data(), cfg.ldc);
    }

    /**
     * @brief A simple configuration struct that defines an scalar-vector product
     * via the BLAS AXPY operation.
     * 
     */
    struct AXPYCallConfig final {
        const unsigned int N;
        const float alpha;
        const unsigned int incx, incy;

        /**
         * @brief Construct a new AXPYCallConfig object.
         * 
         * Specifies an AXPY scalar-vector product on an N-vector with coefficient
         * alpha.
         * 
         * @param N The length of the vector.
         * @param alpha The coefficient to multiply with the vector.
         */
        AXPYCallConfig(unsigned int N, float alpha) :
            N(N), alpha(alpha), incx(1), incy(1) {
             //
        }

        /**
         * @brief Construct a new AXPYCallConfig object
         * 
         * Specifies an AXPY scalar-vector product on an N-vector with coefficient
         * alpha.
         * 
         * @param N The length of the vector.
         * @param alpha The coefficient to multiply with the vector.
         * @param incx Input vector increment.
         * @param incy Output vector increment.
         */
        AXPYCallConfig(unsigned int N, float alpha, unsigned int incx, unsigned int incy) :
            N(N), alpha(alpha), incx(incx), incy(incy) {
            //
        }
    };

    /**
     * @brief Executes an AXPY operation on X, writing the result to Y.
     * 
     * @tparam T The element type of the Y and X vectors.
     * @param Y The data buffer of the output vector.
     * @param X The data buffer of the input vector.
     * @param cfg An `AXPYCallConfig` instance specifying the AXPY operation.
     */
    template<typename T>
    inline void axpy(const std::span<T>& Y,
                     const std::span<const T>& X,
                     const AXPYCallConfig& cfg) {
        throw std::domain_error("Unknown data type for AXPY.");
    }

    template<>
    inline void axpy(const std::span<float>& Y,
                     const std::span<const float>& X,
                     const AXPYCallConfig& cfg) {
        cblas_saxpy(cfg.N, cfg.alpha, X.data(), cfg.incx, Y.data(), cfg.incy);
    }

    template<>
    inline void axpy(const std::span<double>& Y,
                     const std::span<const double>& X,
                     const AXPYCallConfig& cfg) {
        cblas_daxpy(cfg.N, cfg.alpha, X.data(), cfg.incx, Y.data(), cfg.incy);
    }

    /**
     * @brief A simple configuration struct that defines an inplace
     * scalar-vector product via the BLAS SCAL operation.
     * 
     */
    struct SCALCallConfig final {
        const unsigned int N;
        const float alpha;
        const unsigned int incx;

        /**
         * @brief Construct a new SCALCallConfig object.
         * 
         * Specifies an inplace SCAL scalar-vector product on an N-vector
         * with coefficient alpha.
         * 
         * @param N Length of the vector.
         * @param alpha Coefficient to multiply with the vector.
         */
        SCALCallConfig(unsigned int N, float alpha) :
            N(N), alpha(alpha), incx(1) {
             //
        }

        /**
         * @brief Construct a new SCALCallConfig object.
         * 
         * Specifies an inplace SCAL scalar-vector product on an N-vector
         * with coefficient alpha.
         * 
         * @param N Length of the vector.
         * @param alpha Coefficient to multiply with the vector.
         * @param incx Index increment.
         */
        SCALCallConfig(unsigned int N, float alpha, unsigned int incx) :
            N(N), alpha(alpha), incx(incx) {
            //
        }
    };

    /**
     * @brief Executes a SCAL operation on X.
     * 
     * @tparam T The element type of X.
     * @param X The vector to inplace scalar multiply.
     * @param cfg A `SCALCallConfig` instance specifying the SCAL operation.
     */
    template<typename T>
    inline void scal(const std::span<T>& X, const SCALCallConfig& cfg) {
        throw std::domain_error("Unknown data type for SCAL.");
    }

    template<>
    inline void scal(const std::span<float>& X, const SCALCallConfig& cfg) {
        cblas_sscal(cfg.N, cfg.alpha, X.data(), cfg.incx);
    }

    template<>
    inline void scal(const std::span<double>& X, const SCALCallConfig& cfg) {
        cblas_dscal(cfg.N, cfg.alpha, X.data(), cfg.incx);
    }
}

#endif