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

#ifndef CPP_UTILS_LINEAR_ALGEBRA_MATRIX_H
#define CPP_UTILS_LINEAR_ALGEBRA_MATRIX_H

#include <memory>
#include <span>
#include <stdexcept>

#include <CPPUtils/DataStructures/Buffers.hpp>
#include <CPPUtils/LinearAlgebra/BLAS.hpp>

using namespace CPPUtils::DataStructures::Buffers;

namespace CPPUtils::LinearAlgebra {

    namespace Util {
        enum DeviceType {
            CPU,
            CUDA
        };

        template<typename T, DeviceType SD, DeviceType TD>
        inline Matrix<T, TD>& copy(const Matrix<T, SD>& M) {
            throw std::logic_error("Unknown device type.")
        }

        template<typename T, DeviceType TD>
        inline Matrix<T, TD> copy(const Matrix<T, CPU>& M) {
            if constexpr (TD == CPU) {
                return Matrix<T, CPU>(M);
            }

            if constexpr (TD == CUDA) {
                //
            }

            throw std::runtime_error("Unknown device copy type")
        }

        template<typename T, DeviceType TD>
        inline Matrix<T, TD> copy(const Matrix<T, CUDA>& M) {
            if constexpr (TD == CUDA) {
                return Matrix<T, CUDA>(M);
            }

            if constexpr (TD == CPU) {
                //
            }

            throw std::runtime_error("Unknown device copy type")
        }

        template<typename T, DeviceType D>
        inline Matrix<T, D> ones(size_t rows, size_t columns) {
            Matrix<T, D> A(rows, columns);
            A->setAllToValue(1.0);
            return A;
        }

        template<typename T, DeviceType D>
        inline Matrix<T, D> zeros(size_t rows, size_t columns) {
            Matrix<T, D> A(rows, columns);
            A->setAllToValue(0.0);
            return A;
        }
    }

    template<typename T = float, Util::DeviceType D = Util::DeviceType::CPU>
    class Matrix {
    protected:
        std::shared_ptr<Buffer<T>> elements;

        const size_t rows;
        const size_t columns;
        bool is_transposed;
        bool is_triangular;

    public:
        virtual Matrix(size_t rows, size_t columns) :
            rows(rows),
            columns(columns),
            is_transpose(false),
            is_triangular(false) {
            // Allocate the buffer based on the device.
            const auto N = rows() * columns();
            switch (D) {
                case Util::DeviceType::CPU: {
                    elements = std::make_shared<CPUBuffer<T>>(N);
                    break;
                }
                case Util::DeviceType::CUDA: {
                    throw std::runtime_error("CUDA is not supported night now.");
                    break;
                }
                default: {
                    throw std::runtime_error("Unknown device type.");
                }
            }
        }

        virtual ~Matrix() {
            //
        }

        virtual const T* data() const {
            return elements->ptr();
        }

        virtual T* data() {
            return elements->ptr();
        }

        virtual std::shared_ptr<Buffer<T>> getElementBuffer() const {
            return elements;
        }

        virtual Matrix<T, D>& t() {
            //
        }
        
        virtual Matrix<T, D>& upperTriangular() const {
            //
        }
        
        virtual Matrix<T, D>& lowerTriangular() const {
            //
        };
        
        virtual T det() const {
            //
        }


        void t() {
            is_transposed = !is_transposed;
        }

        size_t rows() const {
            return rows;
        }

        size_t columns() const {
            return columns;
        }

        bool is_transposed() const {
            return is_transposed;
        }

        bool is_triangular() const {
            return is_triangular;
        }

        void setAllToValue(T val) {
            elements->setAllToValue(val);
        }

        void setContents(const std::span<T>& vals) {
            elements->setContents(vals);
        }

        std::shared_ptr<Buffer<T>> getBuffer() {
            return elements;
        }
    };

    /*
     * Matrix-Matrix operators.
     */
    template<typename T, Util::DeviceType D>
    Matrix<T, D> operator*(const Matrix<T, D>& lhs, const Matrix<T, D>& rhs) {
        const auto M = lhs.rows();
        const auto K = lhs.columns();
        const auto N = rhs.columns();

        if (K != rhs.rows()) {
            throw std::runtime_error(
                "Matrix inner dimensions must match.");
        }

        Matrix<T, D> A(M, N);
        BLAS::gemm(lhs.ptr(), rhs.ptr(), A.ptr(),
                   BLAS::GEMMCallConfig(M, K, N,
                                        lhs.is_transposed(),
                                        rhs.is_transposed()));
        return A;
    }

    template<typename T, Util::DeviceType D>
    Matrix<T, D> operator+(const Matrix<T, D>& lhs, const Matrix<T, D>& rhs) {
        const auto N = lhs.rows() * lhs.columns();
        const auto M = rhs.rows() * rhs.columns();

        if (M != N) {
            throw std::runtime_error(
                "Expected equal element count.");
        }

        Matrix<T, D> A(lhs);
        BLAS::axpy(A.ptr(), rhs.ptr(), BLAS::AXPYCallConfig(1.0, N));

        return A;
    }

    template<typename T, Util::DeviceType D>
    Matrix<T, D> operator-(const Matrix<T, D>& lhs, const Matrix<T, D>& rhs) {
        const auto N = lhs.rows() * lhs.columns();
        const auto M = rhs.rows() * rhs.columns();

        if (M != N) {
            throw std::runtime_error(
                "Expected equal element count.");
        }

        Matrix<T, D> A(lhs);
        BLAS::axpy(A.ptr(), rhs.ptr(), BLAS::AXPYCallConfig(-1.0, N));

        return A;
    }

    /*
     * Inplace Matrix-Matrix operators.
     */
    template<typename T, Util::DeviceType D>
    Matrix<T, D>& operator*=(Matrix<T, D>& lhs, const Matrix<T, D>& rhs) {
        const auto A = lhs * rhs;
        return std::move(A);
    }

    template<typename T, Util::DeviceType D>
    Matrix<T, D>& operator+=(Matrix<T, D>& lhs, const Matrix<T, D>& rhs) {
        const auto A = lhs + rhs;
        return std::move(A);
    }

    template<typename T, Util::DeviceType D>
    Matrix<T, D>& operator-=(Matrix<T, D>& lhs, const Matrix<T, D>& rhs) {
        const auto A = lhs - rhs;
        return std::move(A);
    }

    /*
     * Matrix-Scalar operators.
     */
    template<typename T, Util::DeviceType D>
    Matrix<T, D> operator*(const Matrix<T, D>& lhs, T rhs) {
        Matrix<T, D> A(lhs);

        const auto N = lhs.rows() * lhs.columns();
        BLAS::scal(A.data(), BLAS::SCALCallConfig(rhs, N))

        return A;
    }

    template<typename T, Util::DeviceType D>
    Matrix<T, D> operator/(const Matrix<T, D>& lhs, T rhs) {
        return lhs * (1.0 / rhs);
    }

    template<typename T, Util::DeviceType D>
    Matrix<T, D> operator+(const Matrix<T, D>& lhs, T rhs) {
        Matrix<T, D> A(lhs.rows(), lhs.columns());
        A->setAllToValue(rhs);
        return lhs + A;
    }

    template<typename T, Util::DeviceType D>
    Matrix<T, D> operator-(const Matrix<T, D>& lhs, T rhs) {
        return lhs + (-1.0 * rhs);
    }

    /*
     * Inplace Matrix-Scalar operators.
     */
    template<typename T, Util::DeviceType D>
    Matrix<T, D>& operator*=(Matrix<T, D>& lhs, T rhs) {
        const auto A = lhs * rhs;
        return std::move(A);
    }

    template<typename T, Util::DeviceType D>
    Matrix<T, D>& operator/=(Matrix<T, D>& lhs, T rhs) {
        const auto A = lhs / rhs;
        return std::move(A);
    }

    template<typename T, Util::DeviceType D>
    Matrix<T, D>& operator+=(Matrix<T, D>& lhs, T rhs) {
         const auto A = lhs + rhs;
        return std::move(A);
    }

    template<typename T, Util::DeviceType D>
    Matrix<T, D>& operator-=(Matrix<T, D>& lhs, T rhs) {
        const auto A = lhs - rhs;
        return std::move(A);
    }
}

#endif