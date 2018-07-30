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

#ifndef CPP_UTILS_COUNTING_ITERATOR
#define CPP_UTILS_COUNTING_ITERATOR

#include <iterator>
#include <ostream>

namespace CPPUtils::Iterators {
    template<typename T>
    class CountingIterator {
    private:
        T counter;

    public:
        using value_type = T;
        using reference = const T&;
        using pointer = const T*;
        using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
        using iterator_category = std::random_access_iterator_tag;

    public:
        CountingIterator() : counter(static_cast<value_type>(0)) {
            //
        }

        CountingIterator(value_type n) : counter(n) {
            //
        }

        CountingIterator(const CountingIterator &iter) : counter(iter.base()) {
            //
        }

        value_type const &base() const {
            return counter;
        }

        reference operator*() const {
            return counter;
        }

        CountingIterator &operator++() {
            ++counter;
            return *this;
        }

        CountingIterator &operator--() {
            --counter;
            return *this;
        }

        CountingIterator operator++(int) {
            CountingIterator tmp(*this);
            ++counter;
            return tmp;
        }

        CountingIterator operator--(int) {
            CountingIterator tmp(*this);
            --counter;
            return tmp;
        }

        CountingIterator &operator+=(difference_type n) {
            counter += n;
            return *this;
        }

        CountingIterator &operator-=(difference_type n) {
            counter -= n;
            return *this;
        }

        difference_type operator-(const CountingIterator &rhs) const {
            return counter - rhs.base();
        }

        CountingIterator operator+(difference_type rhs) const {
            return CountingIterator(counter + rhs);
        }

        CountingIterator operator-(difference_type rhs) const {
            return CountingIterator(counter - rhs);
        }

        friend CountingIterator operator+(difference_type lhs, const CountingIterator &rhs) {
            return CountingIterator(lhs + rhs.base());
        }

        friend CountingIterator operator-(difference_type lhs, const CountingIterator &rhs) {
            return CountingIterator(lhs - rhs.base());
        }

        bool operator==(const CountingIterator &rhs) const {
            return counter == rhs.base();
        }

        bool operator!=(const CountingIterator &rhs) const {
            return counter != rhs.base();
        }

        bool operator>(const CountingIterator &rhs) const {
            return counter > rhs.base();
        }

        bool operator<(const CountingIterator &rhs) const {
            return counter < rhs.base();
        }

        bool operator>=(const CountingIterator &rhs) const {
            return counter >= rhs.base();
        }

        bool operator<=(const CountingIterator &rhs) const {
            return counter <= rhs.base();
        }

        friend std::ostream &operator<<(std::ostream &lhs, const CountingIterator &rhs) {
            lhs << *rhs;
            return lhs;
        }
    };
}

#endif