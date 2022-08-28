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

#ifndef CPP_UTILS_LINEAR_ALGEBRA_LAPACK_H
#define CPP_UTILS_LINEAR_ALGEBRA_LAPACK_H

#include <algorithm>
#include <limits>
#include <span>
#include <stdexcept>
#include <vector>

extern "C" {
    void sgetrf_(int*, int*, float*, int*, int*, int*);
    void dgetrf_(int*, int*, double*, int*, int*, int*);
}

namespace CPPUtils::LinearAlgebra::LAPACK {
    /*
     * GETRF - Recursive LU Factorization.
     */
    struct GETRFCallConfig final {
        const unsigned int M, N;
        const unsigned int lda;

        GETRFCallConfig() = delete;

        explicit GETRFCallConfig(
            unsigned int M, unsigned int N, unsigned int lda) :
            M(M), N(N), lda(lda) {
            // Check LDA >= max(1,M).
            if (lda < std::max(static_cast<unsigned int>(1), M)) {
                throw std::domain_error("LDA must be greater than or equal to max(1, M).");
            }
        }

        explicit GETRFCallConfig(unsigned int M, unsigned int N) :
            GETRFCallConfig(M, N, N) {
            //
        }
    };

    struct GETRFExecutionStatus final {
        const int status;
        const std::vector<unsigned int> ipiv;

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

        GETRFExecutionStatus() = delete;

        GETRFExecutionStatus(int status, const std::span<int> ipiv) :
            status(status), ipiv(process_ipiv(ipiv)) {
            //
        }

        bool success() const {
            return status == 0;
        }

        bool illegal_value() const {
            return status < 0;
        }

        unsigned int illegal_value_index() const {
            if (!illegal_value()) {
                return std::numeric_limits<unsigned int>::max();
            }

            return -1 * status;
        }

        bool singular_value() const {
            return status > 0;
        }

        unsigned int singular_value_diagonal_index() const {
            if (!singular_value()) {
                return std::numeric_limits<unsigned int>::max();
            }

            return status;
        }

        const std::vector<unsigned int> ipiv_if_success() const {
            if (!success()) {
                return {};
            }

            return ipiv;
        }
    };

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
}

#endif
