/*
BSD 3-Clause License

Copyright (c) 2018,2019 Jack Miles Hunt
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

#include <CPPUtils/ContainerTools/TupleTools.hpp>

namespace CPPUtils::Iterators {
    // Pull in tupleFor to apply per-element lambda's to a tuple.
    using CPPUtils::ContainerTools::Tuple::tupleFor;

    template<typename... T>
    class ZipIterator {
    public:
        using value_type = std::tuple<T...>;
        using reference = const value_type&;
        using pointer = const value_type*;
        using difference_type = typename std::iterator<std::random_access_iterator_tag, value_type>::difference_type;
        using iterator_category = std::random_access_iterator_tag;

    protected:
        value_type val;

    public:
        ZipIterator() = delete;
            
        ZipIterator(value_type val) : val(val) {
            //
        }

        ZipIterator(const ZipIterator &iter) : val(iter.base()) {
            //
        }

        virtual ~ZipIterator() {
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

        ZipIterator &operator+=(difference_type rhs) {
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
            tupleFor(res, [this, &rhsVal](size_t idx, auto &elem) { elem = std::get<idx>(val) - std::get<idx>(rhsVal); });
            return res;
        }

        ZipIterator operator+(difference_type rhs) const {
            value_type res;
            tupleFor(res, [this, &rhs](size_t idx, auto &elem) { elem = std::get<idx>(val) + std::get<idx>(rhs); });
            return ZipIterator(res);
        }

        ZipIterator operator-(difference_type rhs) const {
            value_type res;
            tupleFor(res, [this, &rhs](size_t idx, auto &elem) { elem = std::get<idx>(val) - std::get<idx>(rhs); });
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

    template<typename T>
    class Zipper {
    protected:
        T beginIter, endIter;

    public:
        Zipper() = delete;

        Zipper(T beginIter, T endIter) :
            beginIter(beginIter),
            endIter(endIter) {
            //
        }

        virtual ~Zipper(){
            //
        }

        const T &begin() const {
            return beginIter;
        }

        const T &end() const {
            return endIter;
        }

        T &begin() {
            return beginIter;
        }

        T &end() {
            return endIter;
        }
    };

    template<typename... T>
    class ZipperFactory {
    protected:
        template<typename U, typename... V>
        static std::vector<size_t> getLengths(std::vector<size_t> lengths, const U &head, const V& ...tail) {
            lengths.push_back(head.size());
            return getLengths(lengths, tail...);
        }

        static std::vector<size_t> getLengths(std::vector<size_t> lengths) {
            return lengths;
        }

        template<typename W, typename U, typename... V>
        static auto getIterators(W tuplePair, size_t maxLen, const U& head, const V& ...tail) {
            // Get begin iterator.
            auto iter = head.begin();
            auto beginIter = std::tuple_cat(tuplePair.first, std::make_tuple(iter));
            
            // Get truncated end iterator.
            std::advance(iter, maxLen);
            auto endIter = std::tuple_cat(tuplePair.second, std::make_tuple(iter));
            
            return getIterators(std::make_pair(beginIter, endIter), maxLen, tail...);
        }

        template<typename W>
        static auto getIterators(W tuplePair, size_t maxLen) {
            return tuplePair;
        }

    public:
        auto operator()(const T&... containers) const {
            // Get container lengths and min length.
            const auto lengths = getLengths(std::vector<size_t>(), containers...);
            const size_t minLength = *std::min_element(lengths.begin(), lengths.end());

            // Get iterators.
            auto emptyPair = std::make_pair(std::tuple<>(), std::tuple<>());
            auto iterators = getIterators(emptyPair, minLength, containers...);

            // Get begin and end iterators.
            return Zipper(ZipIterator(iterators.first), ZipIterator(iterators.second));
        }
    };
}

#endif