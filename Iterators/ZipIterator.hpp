/*
BSD 3-Clause License

Copyright (c) 2018, Jack Miles Hunt
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

#ifndef CPP_UTILS_ZIP_ITERATOR
#define CPP_UTILS_ZIP_ITERATOR

#include <iterator>
#include <tuple>
#include <ostream>
#include <utility>
#include <algorithm>

#include "../ContainerTools/TupleTools.hpp"

namespace CPPUtils::Iterators {
    // Pull in tupleFor to apply per-element lambda's to a tuple.
    using CPPUtils::ContainerTools::Tuple::tupleFor;

    template<typename T, typename... U>
    class ZipIterator {
    public:
        using value_type = std::tuple<T, U...>;
        using reference = const value_type&;
        using pointer = const value_type*;
        using difference_type = typename std::iterator<std::random_access_iterator_tag, value_type>::difference_type;
        using iterator_category = std::random_access_iterator_tag;

    private:
        value_type val;

    public:
        ZipIterator() = delete;
            
        ZipIterator(value_type val) : val(val) {
            //
        }

        ZipIterator(const ZipIterator &iter) : val(iter.base()) {
            //
        }

        value_type const &base() const {
            return val;
        }

        reference operator*() const {
            return val;
        }

        ZipIterator &operator++() {
            tupleFor(val, [](size_t idx, auto &elem) { return ++elem; });
            return *this;
        }

        ZipIterator &operator--() {
            tupleFor(val, [](size_t idx, auto &elem) { return --elem; });
            return *this;
        }

        ZipIterator operator++(int) {
            ZipIterator tmp(*this);
            tupleFor(val, [](size_t idx, auto &elem) { return ++elem; });
            return tmp;
        }

        ZipIterator operator--(int) {
            ZipIterator tmp(*this);
            tupleFor(val, [](size_t idx, auto &elem) { return --elem; });
            return tmp;
        }

        ZipIterator &operator+=(difference_type t) {
            tupleFor(val, [&rhs](size_t idx, auto &elem) { elem += std::get<idx>(rhs); });
            return *this;
        }

        ZipIterator &operator-=(difference_type rhs) {
            tupleFor(val, [&rhs](size_t idx, auto &elem) { elem -= std::get<idx>(rhs); });
            return *this;
        }

        difference_type operator-(const ZipIterator &rhs) const {
            auto rhsVal = rhs.base();
            value_type res;
            tupleFor(res, [&rhsVal](size_t idx, auto &elem) { elem = std::get<idx>(val) - std::get<idx>(rhsVal); });
            return res;
        }

        ZipIterator operator+(difference_type rhs) const {
            value_type res;
            tupleFor(res, [&rhs](size_t idx, auto &elem) { elem = std::get<idx>(val) + std::get<idx>(rhs); });
            return ZipIterator(res);
        }

        ZipIterator operator-(difference_type rhs) const {
            value_type res;
            tupleFor(res, [&rhs](size_t idx, auto &elem) { elem = std::get<idx>(val) - std::get<idx>(rhs); });
            return ZipIterator(res);
        }

        friend ZipIterator operator+(difference_type lhs, const ZipIterator &rhs) {
            return ZipIterator(lhs + rhs);
        }

        friend ZipIterator operator-(difference_type lhs, const ZipIterator &rhs) {
            return ZipIterator(lhs - rhs);
        }

        bool operator==(const ZipIterator &rhs) const {
            return val == rhs.base();
        }

        bool operator!=(const ZipIterator &rhs) const {
            return val != rhs.base();
        }

        bool operator>(const ZipIterator &rhs) const {
            return val > rhs.base();
        }

        bool operator<(const ZipIterator &rhs) const {
            return val < rhs.base();
        }

        bool operator>=(const ZipIterator &rhs) const {
            return val >= rhs.base();
        }

        bool operator<=(const ZipIterator &rhs) const {
            return val <= rhs.base();
        }
    };
    /*
    template<typename... T>
    class Zipper {
    private:
        template<typename F>
        static void doVariadic(const F &func) {
            return;
        }

        template<typename F, typename U, typename... V>
        static void doVariadic(const F &func, const U &head, const V& ...tail) {
            func(head);
            doVariadic(func, tail...);
        }

    public:
        Zipper(const T&... containers) {
            // Get container lengths and min length.
            std::vector<size_t> lengths;
            doVariadic([&lengths, &containers...](const auto &c) { lengths.push_back(c.size()); }, containers...);
            const size_t minLength = *std::min_element(lengths.begin(), lengths.end());

            // Get begin and end iterators.
            std::tuple<> begin;
            std::tuple<> end;
            doVariadic([&](const auto &c) {
                std::tuple_cat(begin, std::tuple<c.iterator>(c.begin()));
                std::tuple_cat(end, std::advance(c.begin(), std::tuple<c.iterator>(minLength)));
            }, containers...);
        }

        virtual ~Zipper() {
            //
        }

        auto begin() {
            //
        }

        auto end() {
            //
        }
    };
    */
}

#endif