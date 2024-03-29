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

#ifndef CPP_UTILS_TUPLE_TOOLS
#define CPP_UTILS_TUPLE_TOOLS

#include <tuple>
#include <functional>
#include <cstddef>

namespace CPPUtils::ContainerTools::Tuple {
    /**
     * @brief Applies a lambda to each element of a given tuple.
     * 
     * Example of usage.
     * 
     *     auto tuple = std::make_tuple(1, 2.0, -3, -2.5);
     *     const auto a = -5.0;
     *     tupleFor(tuple, [&a](size_t idx, auto &elem) {
     *         elem *= 2 + a;
     *     });
     * 
     * @tparam T Type of the element to apply the lambda to.
     * @tparam F Type of the lambda to apply to the element of type `T`.
     * @tparam S Tuple indices.
     * @param tuple The tuple to apply the lambda to.
     * @param func The lambda to apply.
     */
    template<typename T, typename F, std::size_t ...S>
    constexpr void tupleFor(T &tuple, const F &func, std::index_sequence<S...>) {
        (func(std::integral_constant<size_t, S>{}, std::get<S>(tuple)),...);
    }

    /**
     * @brief Applies a lambda to each element of a given tuple.
     * 
     * Example of usage.
     * 
     *     auto tuple = std::make_tuple(1, 2.0, -3, -2.5);
     *     const auto a = -5.0;
     *     tupleFor(tuple, [&a](size_t idx, auto &elem) {
     *         elem *= 2 + a;
     *     });
     * 
     * @tparam T Type of the element to apply the lambda to.
     * @tparam F Type of the lambda to apply to the element of type `T`
     * @param tuple The tuple to apply the lambda to.
     * @param func The lambda to apply.
     */
    template<typename ...T, typename F>
    constexpr void tupleFor(std::tuple<T...> &tuple, const F &func) {
        tupleFor(tuple, std::forward<const F>(func), std::make_index_sequence<sizeof...(T)>{});
    }
}

#endif