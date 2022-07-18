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
#include <stdexcept>

namespace CPPUtils::DataStructures::Buffers {

    template<typename T>
    class Buffer {
    protected:
        const size_t buffer_size;
        T* data;

    public:
        virtual Buffer(size_t size) : buffer_size(size), data(nullptr) {
            //
        }

        virtual Buffer(const Buffer<T>& buffer) = 0;

        virtual ~Buffer() = 0;

        virtual T operator[](size_t idx) = 0;

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
    class CPUBuffer : public Buffer<T> final {
    public:
        CPUBuffer(size_t size) : Buffer<T>(size) {
            data = new T[size];
        }

        CPUBuffer(const CPUBuffer<T>& buffer) : Buffer<T>(buffer.size()) {
            const auto N = size() * sizeof(T);
            std::memcpy(data, buffer.ptr(), N);
        }

        virtual ~CPUBuffer() {
            delete[] data;
        }

        virtual T operator[](size_t idx) const {
            return data[idx];
        }
    };

}

#endif