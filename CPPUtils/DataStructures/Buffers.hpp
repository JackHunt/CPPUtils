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

#ifndef CPP_UTILS_DATA_STRUCTURES_BUFFERS_H
#define CPP_UTILS_DATA_STRUCTURES_BUFFERS_H

#include <cstring>
#include <span>
#include <stdexcept>

namespace CPPUtils::DataStructures::Buffers {

    template<typename T>
    class Buffer {
    protected:
        const size_t buffer_size;
        T* data;

    public:
        Buffer(size_t size) : buffer_size(size), data(nullptr) {
            //
        }

        Buffer(const Buffer<T>& buffer) = 0;

        virtual ~Buffer() = 0;

        virtual T operator[](size_t idx) = 0;

        virtual void setAllToValue(T) = 0;

        virtual void setContents(const std::span<T>& vals) {
            if (vals.size() != buffer_size) {
                throw std::length_error("Incorrect value count.");
            }
        }

        const T* ptr() const {
            return data;
        }

        T* ptr() {
            return data;
        }

        virtual size_t size() const {
            return buffer_size;
        }
    };

    template<typename T>
    class CPUBuffer final : public Buffer<T> {
    public:
        CPUBuffer(size_t size) : Buffer<T>(size) {
            this->data = new T[size];
        }

        CPUBuffer(const CPUBuffer<T>& buffer) : Buffer<T>(buffer.size()) {
            const auto N = this->size() * sizeof(T);
            std::memcpy(&this->data[0], buffer.ptr(), N);
        }

        virtual ~CPUBuffer() {
            delete[] this->data;
        }

        virtual T operator[](size_t idx) const override {
            return this->data[idx];
        }

        virtual void setAllToValue(T val) override {
            std::memset(&this->data[0], val, this->size() * sizeof(T));
        }

        virtual void setContents(const std::span<T>& vals) override {
            Buffer<T>::setContents(vals);
            std::memcpy(this->data, vals.data(), vals.size() * sizeof(T));
        }
    };

}

#endif