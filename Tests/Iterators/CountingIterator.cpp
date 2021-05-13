/*
BSD 3-Clause License

Copyright (c) 2021 Jack Miles Hunt
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

#define BOOST_TEST_MODULE CountingIteratorTests

#include <vector>

#include <boost/test/included/unit_test.hpp>

#include <CPPUtils/Iterators/CountingIterator.hpp>

using namespace CPPUtils::Iterators;

BOOST_AUTO_TEST_SUITE(CountingIteratorTestSuite)

template<typename T>
void counterTestImpl(T a, T b) {
    // Generate some expected values.
    const T inc = a >= b ? -1 : 1;
    std::vector<T> true_vals;
    for (T i = a; i < b; i+=inc) {
        true_vals.emplace_back(i);
    }

    // Compare with using Counter.
    Counter<T> c(a, b);
    size_t idx = 0;
    for (auto iter = c.begin(); iter != c.end(); iter++) {
        BOOST_CHECK_LT(idx, true_vals.size());
        BOOST_CHECK_EQUAL(iter, true_vals.at(idx));
        idx++;
    }

    BOOST_CHECK_EQUAL(idx, true_vals.size());
}

BOOST_AUTO_TEST_CASE(SignedCounterTest) {
    counterTestImpl<short>(-127, 127);
    counterTestImpl<int>(-1270, 1270);
    counterTestImpl<long>(-1270, 1270);
}

/*
BOOST_AUTO_TEST_CASE(SignedCounterReverseTest) {
    counterTestImpl<short>(127, -127);
    counterTestImpl<int>(1270, -1270);
    counterTestImpl<long>(1270, -1270);
}
*/

BOOST_AUTO_TEST_CASE(UnsignedCounterTest) {
    counterTestImpl<unsigned short>(0, 127);
    counterTestImpl<unsigned int>(0, 1270);
    counterTestImpl<unsigned long>(0, 1270);
}

/*
BOOST_AUTO_TEST_CASE(UnsignedCounterReverseTest) {
    counterTestImpl<unsigned short>(127, 0);
    counterTestImpl<unsigned int>(1270, 0);
    counterTestImpl<unsigned long>(1270, 0);
}
*/

BOOST_AUTO_TEST_SUITE_END()