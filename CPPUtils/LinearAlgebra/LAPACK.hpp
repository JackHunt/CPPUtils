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

#ifndef CPP_UTILS_LINEAR_ALGEBRA_LAPACK_H
#define CPP_UTILS_LINEAR_ALGEBRA_LAPACK_H

#include <algorithm>
#include <limits>
#include <span>
#include <stdexcept>
#include <vector>

extern "C" {
    // LU factorization.
    void sgetrf_(int*, int*, float*, int*, int*, int*);
    void dgetrf_(int*, int*, double*, int*, int*, int*);

    // System solve via LU factorizaion.
    void sgesv_(int*, int*, float*, int*, int*, float*, int*, int*);
    void dgesv_(int*, int*, double*, int*, int*, double*, int*, int*);
}

namespace CPPUtils::LinearAlgebra::LAPACK {
    /**
     * @brief A simple configuration struct that defines an LU factorization
     * of a matrix using the LAPACK GETRF routine.
     * 
     */
    struct GETRFCallConfig final {
        const unsigned int M, N;
        const unsigned int lda;

        /**
         * @brief Construct a new GETRFCallConfig object.
         * 
         * Specifies an LU factorization of an MxN matrix.
         * 
         * @param M The first dimension of the matrix.
         * @param N The second dimension of the matrix.
         */
        GETRFCallConfig(unsigned int M, unsigned int N) :
            GETRFCallConfig(M, N, N) {
            //
        }

        /**
         * @brief Construct a new GETRFCallConfig object.
         * 
         * Specifies an LU factorization of an MxN matrix.
         * 
         * @param M The first dimension of the matrix.
         * @param N The second dimension of the matrix.
         * @param lda The leading dimension of the matrix.
         */
        GETRFCallConfig(unsigned int M, unsigned int N, unsigned int lda) :
            M(M), N(N), lda(lda) {
            // Check LDA >= max(1,M).
            if (lda < std::max(static_cast<unsigned int>(1), M)) {
                throw std::domain_error("LDA must be greater than or equal to max(1, M).");
            }
        }
    };

    /**
     * @brief A simple struct describing the ececution status of a LAPACK
     * GETRF operation.
     * 
     */
    struct GETRFExecutionStatus final {
        const int status;
        const std::vector<unsigned int> ipiv;

        /**
         * @brief 
         * 
         * @param _ipiv 
         * @return std::vector<unsigned int> 
         */
        static std::vector<unsigned int> process_ipiv(const std::span<int> _ipiv) {
            if (_ipiv.size() == 0) {
                return {};
            }

            std::vector<unsigned int> new_ipiv;
            std::transform(
                _ipiv.begin(), _ipiv.end(), std::back_inserter(new_ipiv),
                [](int i) -> unsigned int {
                    if (i < 0) {
                        throw std::domain_error(
                            "Negative IPIV value encountered.");
                    }

                    return static_cast<unsigned int>(i);
                });

            return std::move(new_ipiv);
        }

        /**
         * @brief Construct a new GETRFExecutionStatus object.
         * 
         * @param status 
         * @param ipiv 
         */
        GETRFExecutionStatus(int status, const std::span<int> ipiv) :
            status(status), ipiv(process_ipiv(ipiv)) {
            //
        }

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool success() const {
            return status == 0;
        }

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool illegal_value() const {
            return status < 0;
        }

        /**
         * @brief 
         * 
         * @return unsigned int 
         */
        unsigned int illegal_value_index() const {
            if (!illegal_value()) {
                return std::numeric_limits<unsigned int>::max();
            }

            return -1 * status;
        }

        /**
         * @brief 
         * 
         * @return true 
         * @return false 
         */
        bool singular_value() const {
            return status > 0;
        }

        /**
         * @brief 
         * 
         * @return unsigned int 
         */
        unsigned int singular_value_diagonal_index() const {
            if (!singular_value()) {
                return std::numeric_limits<unsigned int>::max();
            }

            return status;
        }

        /**
         * @brief 
         * 
         * @return const std::vector<unsigned int> 
         */
        const std::vector<unsigned int> ipiv_if_success() const {
            if (!success()) {
                return {};
            }

            return ipiv;
        }
    };

    /**
     * @brief 
     * 
     * @tparam T 
     * @param A 
     * @param cfg 
     * @return GETRFExecutionStatus 
     */
    template<typename T>
    inline GETRFExecutionStatus getrf(std::span<T> A,
                                      const GETRFCallConfig& cfg) {
        throw std::domain_error("Unknown data type for GETRF.");
    }

    template<>
    inline GETRFExecutionStatus getrf(std::span<float> A,
                                      const GETRFCallConfig& cfg) {
        std::vector<int> ipiv(std::min(cfg.M, cfg.N));
        int M = cfg.M;
        int N = cfg.N;
        int LDA = cfg.lda;
        int status = 0;
        sgetrf_(&M, &N, A.data(), &LDA, ipiv.data(), &status);

        return GETRFExecutionStatus(status, ipiv);
    }

    template<>
    inline GETRFExecutionStatus getrf(std::span<double> A,
                                      const GETRFCallConfig& cfg) {
        std::vector<int> ipiv(std::min(cfg.M, cfg.N));
        int M = cfg.M;
        int N = cfg.N;
        int LDA = cfg.lda;
        int status = 0;
        dgetrf_(&M, &N, A.data(), &LDA, ipiv.data(), &status);

        return GETRFExecutionStatus(status, ipiv);
    }

    /**
     * @brief 
     * 
     */
    struct GESVCallConfig final {
        const unsigned int N, NRHS;
        const unsigned int lda, ldb;

        /**
         * @brief Construct a new GESVCallConfig object
         * 
         * @param N 
         */
        GESVCallConfig(unsigned int N) :
            GESVCallConfig(N, 1, N, N) {
            //
        }

        /**
         * @brief Construct a new GESVCallConfig object
         * 
         * @param N 
         * @param NRHS 
         * @param lda 
         * @param ldb 
         */
        GESVCallConfig(unsigned int N, unsigned int NRHS,
                       unsigned int lda, unsigned int ldb) :
            N(N), NRHS(NRHS), lda(lda), ldb(ldb) {
            // Check N >= 0.
            if (N < 0) {
                throw std::domain_error("N must be greater than 0.");
            }

            // Check NRHS >= 0.
            if (NRHS < 0) {
                throw std::domain_error("NRHS must be greater than 0.");
            }

            // Check LDA >= max(1,N).
            if (lda < std::max(static_cast<unsigned int>(1), N)) {
                throw std::domain_error("LDA must be greater than or equal to max(1, M).");
            }

            // Check LDB >= max(1,N).
            if (ldb < std::max(static_cast<unsigned int>(1), N)) {
                throw std::domain_error("LDB must be greater than or equal to max(1, M).");
            }
        }
    };

    /**
     * @brief 
     * 
     */
    using GESVExecutionStatus = GETRFExecutionStatus;

    /**
     * @brief 
     * 
     * @tparam T 
     * @param A 
     * @param B 
     * @param cfg 
     * @return GESVExecutionStatus 
     */
    template<typename T>
    inline GESVExecutionStatus gesv(std::span<T> A, std::span<T> B,
                                    const GESVCallConfig cfg) {
        throw std::domain_error("Unknown data type for GESV.");
    }

    template<>
    inline GESVExecutionStatus gesv(std::span<float> A, std::span<float> B,
                                    const GESVCallConfig cfg) {
        std::vector<int> ipiv(cfg.N);
        int N = cfg.N;
        int NRHS = cfg.NRHS;
        int lda = cfg.lda;
        int ldb = cfg.ldb;
        int status = 0;
        sgesv_(&N, &NRHS, A.data(), &lda, ipiv.data(), B.data(), &ldb, &status);

        return GESVExecutionStatus(status, ipiv);
    }

    template<>
    inline GESVExecutionStatus gesv(std::span<double> A, std::span<double> B,
                                    const GESVCallConfig cfg) {
        std::vector<int> ipiv(cfg.N);
        int N = cfg.N;
        int NRHS = cfg.NRHS;
        int lda = cfg.lda;
        int ldb = cfg.ldb;
        int status = 0;
        dgesv_(&N, &NRHS, A.data(), &lda, ipiv.data(), B.data(), &ldb, &status);

        return GESVExecutionStatus(status, ipiv);
    }
}

#endif
