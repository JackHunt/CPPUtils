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

#define BOOST_TEST_MODULE HashingTests

#include <utility>

#include <boost/test/included/unit_test.hpp>

#include <CPPUtils/Algorithms/Hashing.hpp>

using namespace CPPUtils::Algorithms;

BOOST_AUTO_TEST_SUITE(HashingTestSuite)

BOOST_AUTO_TEST_CASE(CantorHashTest) {
    BOOST_CHECK_EQUAL(cantorHash(0, 0), 0);
    BOOST_CHECK_EQUAL(cantorHash(0, 1), 2);
    BOOST_CHECK_EQUAL(cantorHash(0, 2), 5);
    BOOST_CHECK_EQUAL(cantorHash(0, 3), 9);

    BOOST_CHECK_EQUAL(cantorHash(1, 0), 1);
    BOOST_CHECK_EQUAL(cantorHash(1, 1), 4);
    BOOST_CHECK_EQUAL(cantorHash(1, 2), 8);
    BOOST_CHECK_EQUAL(cantorHash(1, 3), 13);

    BOOST_CHECK_EQUAL(cantorHash(2, 0), 3);
    BOOST_CHECK_EQUAL(cantorHash(2, 1), 7);
    BOOST_CHECK_EQUAL(cantorHash(2, 2), 12);
    BOOST_CHECK_EQUAL(cantorHash(2, 3), 18);

    BOOST_CHECK_EQUAL(cantorHash(3, 0), 6);
    BOOST_CHECK_EQUAL(cantorHash(3, 1), 11);
    BOOST_CHECK_EQUAL(cantorHash(3, 2), 17);
    BOOST_CHECK_EQUAL(cantorHash(3, 3), 24);
}

BOOST_AUTO_TEST_CASE(InverseCantorHashTest) {
    BOOST_CHECK(inverseCantorHash(0) == std::make_pair<int>(0, 0));
    BOOST_CHECK(inverseCantorHash(2) == std::make_pair<int>(0, 1));
    BOOST_CHECK(inverseCantorHash(5) == std::make_pair<int>(0, 2));
    BOOST_CHECK(inverseCantorHash(9) == std::make_pair<int>(0, 3));

    BOOST_CHECK(inverseCantorHash(1) == std::make_pair<int>(1, 0));
    BOOST_CHECK(inverseCantorHash(4) == std::make_pair<int>(1, 1));
    BOOST_CHECK(inverseCantorHash(8) == std::make_pair<int>(1, 2));
    BOOST_CHECK(inverseCantorHash(13) == std::make_pair<int>(1, 3));

    BOOST_CHECK(inverseCantorHash(3) == std::make_pair<int>(2, 0));
    BOOST_CHECK(inverseCantorHash(7) == std::make_pair<int>(2, 1));
    BOOST_CHECK(inverseCantorHash(12) == std::make_pair<int>(2, 2));
    BOOST_CHECK(inverseCantorHash(18) == std::make_pair<int>(2, 3));

    BOOST_CHECK(inverseCantorHash(6) == std::make_pair<int>(3, 0));
    BOOST_CHECK(inverseCantorHash(11) == std::make_pair<int>(3, 1));
    BOOST_CHECK(inverseCantorHash(17) == std::make_pair<int>(3, 2));
    BOOST_CHECK(inverseCantorHash(24) == std::make_pair<int>(3, 3));
}

BOOST_AUTO_TEST_SUITE_END()