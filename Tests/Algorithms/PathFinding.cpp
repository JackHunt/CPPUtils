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

#define BOOST_TEST_MODULE PathFindingTests

#include <map>
#include <vector>

#include <boost/test/included/unit_test.hpp>

#include <CPPUtils/Algorithms/PathFinding.hpp>

using namespace CPPUtils::Algorithms;
using namespace CPPUtils::DataStructures::Graphs;

BOOST_AUTO_TEST_SUITE(PathFindingTestSuite)

BOOST_AUTO_TEST_CASE(VertexCostPriorityTest) {
    RankedVertex<int> a(0.1, 1);
    RankedVertex<int> b(0.2, 1);

    BOOST_CHECK(VertexCostPriority<int>()(a, b));
    BOOST_CHECK(!VertexCostPriority<int>()(b, a));
}

BOOST_AUTO_TEST_CASE(GetPathTest) {
    const std::map<int, int> traversals = {
        {4, 3},
        {3, 2},
        {2, 1}
    };

    const auto path = getPath(traversals, 1, 4);
    const std::vector<int> true_path = { 1, 2, 3, 4 };
    BOOST_CHECK_EQUAL(path.size(), true_path.size());
    BOOST_CHECK_EQUAL_COLLECTIONS(path.cbegin(), path.cend(),
                                  true_path.cbegin(), true_path.cend());
}

BOOST_AUTO_TEST_CASE(GetPathTestEmpty) {
    const std::map<int, int> traversals = {
        {4, 3},
        {3, 3},
        {2, 1}
    };

    const auto path = getPath(traversals, 1, 4);
    BOOST_CHECK(path.empty());
}

BOOST_AUTO_TEST_CASE(GetPathInvalidSourceTest) {
    const std::map<int, int> traversals = {
        {4, 3},
        {3, 2},
        {2, 1}
    };

    const auto path = getPath(traversals, 5, 4);
    BOOST_CHECK(path.empty());
}

BOOST_AUTO_TEST_CASE(GetPathInvalidSinkTest) {
    const std::map<int, int> traversals = {
        {4, 3},
        {3, 2},
        {2, 1}
    };

    const auto path = getPath(traversals, 1, 5);
    BOOST_CHECK(path.empty());
}

BOOST_AUTO_TEST_CASE(AStarSearchTest) {
    DirectedGraph<int> G;

    constexpr double w = 0.1;
    G.addEdge(1, 2, w);
    G.addEdge(2, 3, w);
    G.addEdge(3, 4, w);
    G.addEdge(4, 5, w);

    G.addEdge(2, 4, w);

    auto heuristic = [](int a, int b) -> double {
        return a % b == 0 ? 0.0 : 1.0;
    };

    auto goal = [](int v) {
        return v == 5;
    };

    const auto path = AStarSearch<int, double, double>(G, 1, goal, heuristic);
    const std::vector<int> true_path = { 1, 2, 4, 5 };
    BOOST_CHECK_EQUAL(path.size(), true_path.size());

    BOOST_CHECK_EQUAL_COLLECTIONS(path.cbegin(), path.cend(),
                                  true_path.cbegin(), true_path.cend());
}

BOOST_AUTO_TEST_CASE(AStarSearchNeverReachGoalTest) {
    DirectedGraph<int> G;

    constexpr double w = 0.1;
    G.addEdge(1, 2, w);
    G.addEdge(2, 3, w);
    G.addEdge(3, 4, w);
    G.addEdge(4, 5, w);

    G.addEdge(2, 4, w);

    auto heuristic = [](int a, int b) -> double {
        return 0;
    };

    auto goal = [](int v) {
        return false;
    };

    const auto path = AStarSearch<int, double, double>(G, 1, goal, heuristic);
    BOOST_CHECK(path.empty());
}

BOOST_AUTO_TEST_CASE(AStarSearchInvalidStartTest) {
    DirectedGraph<int> G;

    constexpr double w = 0.1;
    G.addEdge(1, 2, w);
    G.addEdge(2, 3, w);
    G.addEdge(3, 4, w);
    G.addEdge(4, 5, w);

    G.addEdge(2, 4, w);

    auto heuristic = [](int a, int b) -> double {
        return a % b == 0 ? 0.0 : 1.0;
    };

    auto goal = [](int v) {
        return v == 5;
    };

    const auto path = AStarSearch<int, double, double>(G, 6, goal, heuristic);
    BOOST_CHECK(path.empty());
}

BOOST_AUTO_TEST_CASE(DijkstraTest) {
    DirectedGraph<int> G;

    G.addEdge(1, 2, 0.1);
    G.addEdge(2, 3, 0.1);
    G.addEdge(3, 4, 0.1);
    G.addEdge(4, 5, 0.1);

    G.addEdge(1, 4, 1.5); // Shorter, but higher cost.

    const auto path = dijkstra<int, double>(G, 1, 5);

    const std::vector<int> true_path = { 1, 2, 3, 4, 5 };
    BOOST_CHECK_EQUAL(path.size(), true_path.size());

    BOOST_CHECK_EQUAL_COLLECTIONS(path.cbegin(), path.cend(),
                                  true_path.cbegin(), true_path.cend());
}

BOOST_AUTO_TEST_CASE(DijkstraInvalidStartTest) {
    DirectedGraph<int> G;

    constexpr double w = 0.1;
    G.addEdge(1, 2, w);
    G.addEdge(2, 3, w);
    G.addEdge(3, 4, w);
    G.addEdge(4, 5, w);

    const auto path = dijkstra<int, double>(G, 6, 5);
    BOOST_CHECK(path.empty());
}

BOOST_AUTO_TEST_CASE(DijkstraInvalidEndTest) {
    DirectedGraph<int> G;

    constexpr double w = 0.1;
    G.addEdge(1, 2, w);
    G.addEdge(2, 3, w);
    G.addEdge(3, 4, w);
    G.addEdge(4, 5, w);

    const auto path = dijkstra<int, double>(G, 1, 6);
    BOOST_CHECK(path.empty());
}

BOOST_AUTO_TEST_SUITE_END()